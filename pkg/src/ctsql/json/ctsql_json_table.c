/* -------------------------------------------------------------------------
 *  This file is part of the Cantian project.
 * Copyright (c) 2024 Huawei Technologies Co.,Ltd.
 *
 * Cantian is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *
 *          http://license.coscl.org.cn/MulanPSL2
 *
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v2 for more details.
 * -------------------------------------------------------------------------
 *
 * ctsql_json_table.c
 *
 *
 * IDENTIFICATION
 * src/ctsql/json/ctsql_json_table.c
 *
 * -------------------------------------------------------------------------
 */
#include "ctsql_json_table.h"

typedef status_t (*json_column_parse_func_t)(sql_stmt_t *stmt, word_t *word, rs_column_t *new_col);
typedef status_t (*json_attr_match_func_t)(text_t *text, json_func_attr_t *json_func);

typedef struct st_json_column_parse_attr {
    char *start_word;
    uint32 start_len;
    char *func_name;
    uint32 func_len;
    json_column_parse_func_t json_column_parse_func;
} json_col_parse_attr_t;

static status_t sql_set_json_table_column_path(sql_stmt_t *stmt, word_t *word, text_t *path_text)
{
    if (word->type != WORD_TYPE_STRING) {
        CT_SRC_THROW_ERROR(word->loc, ERR_SQL_SYNTAX_ERROR, "json path expression must be string");
        return CT_ERROR;
    }
    text_t const_text = word->text.value;
    CM_REMOVE_ENCLOSED_CHAR(&const_text);
    if (const_text.len > CT_SHARED_PAGE_SIZE) {
        CT_SRC_THROW_ERROR_EX(word->loc, ERR_SQL_SYNTAX_ERROR,
            "current json table column path is %d, longer than the maximum %d", const_text.len, CT_SHARED_PAGE_SIZE);
        return CT_ERROR;
    } else if (const_text.len == 0) {
        CT_SRC_THROW_ERROR(word->loc, ERR_SQL_SYNTAX_ERROR, "json table column path cannot be empty");
        return CT_ERROR;
    }
    CT_RETURN_IFERR(sql_alloc_mem(stmt->context, const_text.len, (void **)&path_text->str));
    MEMS_RETURN_IFERR(memcpy_s(path_text->str, const_text.len, const_text.str, const_text.len));
    path_text->len = const_text.len;
    return CT_SUCCESS;
}

static status_t sql_create_json_func_path_node(sql_stmt_t *stmt, word_t *word, rs_column_t *new_col)
{
    expr_node_t *func_node = new_col->expr->root;
    expr_node_t *path_node = NULL;
    lex_t *lex = stmt->session->lex;

    CT_RETURN_IFERR(sql_create_expr(stmt, &func_node->argument));
    CT_RETURN_IFERR(sql_alloc_mem(stmt->context, sizeof(expr_node_t), (void **)&func_node->argument->root));
    func_node->argument->root->value.type = CT_TYPE_INTEGER;
    func_node->argument->root->value.v_int = 0;
    func_node->argument->root->value.is_null = CT_FALSE;
    func_node->argument->root->type = EXPR_NODE_CONST;
    CT_RETURN_IFERR(sql_create_expr(stmt, &func_node->argument->next));
    CT_RETURN_IFERR(
        sql_alloc_mem(stmt->context, sizeof(expr_node_t), (void **)&new_col->expr->root->argument->next->root));
    path_node = new_col->expr->root->argument->next->root;
    path_node->type = EXPR_NODE_CONST;
    path_node->value.type = CT_TYPE_STRING;
    CT_RETURN_IFERR(lex_fetch(lex, word));
    return sql_set_json_table_column_path(stmt, word, &path_node->value.v_text);
}

static status_t sql_set_json_func_attr(sql_stmt_t *stmt, text_t *attr_text, json_func_attr_t *json_func,
    json_attr_match_func_t json_attr_match_func)
{
    text_t temp = { NULL, 0 };
    status_t status = CT_ERROR;

    CTSQL_SAVE_STACK(stmt);
    do {
        cm_trim_text(attr_text);
        CT_BREAK_IF_ERROR(sql_push(stmt, attr_text->len, (void **)&temp.str));
        temp.len = attr_text->len;
        CT_BREAK_IF_ERROR(cm_text_copy(&temp, attr_text->len, attr_text));
        cm_text_upper(&temp);
        CT_BREAK_IF_ERROR(json_attr_match_func(&temp, json_func));
        attr_text->str += (attr_text->len - temp.len);
        attr_text->len = temp.len;
        status = CT_SUCCESS;
    } while (0);
    CTSQL_RESTORE_STACK(stmt);
    return status;
}

static status_t sql_parse_json_exists_column(sql_stmt_t *stmt, word_t *word, rs_column_t *new_col)
{
    lex_t *lex = stmt->session->lex;

    CT_RETURN_IFERR(lex_expected_fetch_word(lex, "path"));
    return sql_create_json_func_path_node(stmt, word, new_col);
}

static status_t sql_parse_json_query_column(sql_stmt_t *stmt, word_t *word, rs_column_t *new_col)
{
    lex_t *lex = stmt->session->lex;

    CT_RETURN_IFERR(lex_expected_fetch_word(lex, "json"));
    CT_RETURN_IFERR(sql_set_json_func_attr(stmt, &lex->curr_text->value, &new_col->expr->root->json_func_attr,
        json_func_att_match_wrapper));
    CT_RETURN_IFERR(lex_expected_fetch_word(lex, "path"));
    return sql_create_json_func_path_node(stmt, word, new_col);
}

static status_t sql_parse_json_value_column(sql_stmt_t *stmt, word_t *word, rs_column_t *new_col)
{
    return sql_create_json_func_path_node(stmt, word, new_col);
}

static json_col_parse_attr_t g_json_column_parse_attr[] = {
    { "EXISTS", 6, "JSON_EXISTS", 11, sql_parse_json_exists_column },
    { "FORMAT", 6, "JSON_QUERY", 10, sql_parse_json_query_column },
    { "PATH", 4, "JSON_VALUE", 10, sql_parse_json_value_column },
};

static status_t sql_create_json_column(sql_stmt_t *stmt, sql_table_t *table, word_t *word)
{
    lex_t *lex = stmt->session->lex;
    rs_column_t *new_col = NULL;

    CT_RETURN_IFERR(cm_galist_new(&table->json_table_info->columns, sizeof(rs_column_t), (void **)&new_col));
    CT_RETURN_IFERR(sql_create_expr(stmt, &new_col->expr));
    CT_RETURN_IFERR(sql_alloc_mem(stmt->context, sizeof(expr_node_t), (void **)&new_col->expr->root));
    CT_RETURN_IFERR(lex_fetch(lex, word));
    if (!word->namable) {
        CT_SRC_THROW_ERROR(word->loc, ERR_SQL_SYNTAX_ERROR, "json_table column expected");
        return CT_ERROR;
    }
    CT_RETURN_IFERR(sql_word_as_column(stmt, word, &new_col->expr->root->word));

    new_col->name = new_col->expr->root->word.column.name.value;
    new_col->type = RS_COL_CALC;
    CT_BIT_SET(new_col->rs_flag, RS_NULLABLE);

    new_col->expr->loc = word->loc;
    new_col->expr->root->owner = new_col->expr;
    new_col->expr->root->loc = word->loc;
    new_col->expr->root->dis_info.need_distinct = CT_FALSE;
    new_col->expr->root->dis_info.idx = CT_INVALID_ID32;
    new_col->expr->root->format_json = CT_FALSE;
    new_col->expr->root->json_func_attr = (json_func_attr_t) { 0, 0 };
    new_col->expr->root->typmod.is_array = CT_FALSE;
    return CT_SUCCESS;
}

static void create_ordinality_for_json_table(sql_table_t *table)
{
    rs_column_t *new_col =
        (rs_column_t *)cm_galist_get(&table->json_table_info->columns, table->json_table_info->columns.count - 1);
    new_col->expr->root->type = EXPR_NODE_CONST;
    new_col->expr->root->value.type = CT_TYPE_BIGINT;
    new_col->expr->root->value.v_bigint = 0;
    new_col->expr->root->value.is_null = CT_FALSE;
}

static void set_json_func_default_error_type(expr_node_t *func_node, json_error_type_t default_type)
{
    json_func_attr_t *json_func = &func_node->json_func_attr;
    if (default_type == JSON_RETURN_NULL) {
        if (cm_compare_text_str(&func_node->word.func.name.value, "JSON_EXISTS") == 0) {
            json_func->ids |= JSON_FUNC_ATT_FALSE_ON_ERROR;
        } else {
            json_func->ids |= JSON_FUNC_ATT_NULL_ON_ERROR;
        }
    } else {
        json_func->ids |= JSON_FUNC_ATT_ERROR_ON_ERROR;
    }
}

static status_t sql_create_json_func_column(sql_stmt_t *stmt, word_t *word, sql_table_t *table)
{
    bool32 result = CT_FALSE;
    uint32 column_type_count = sizeof(g_json_column_parse_attr) / sizeof(json_col_parse_attr_t);
    lex_t *lex = stmt->session->lex;
    rs_column_t *new_col =
        (rs_column_t *)cm_galist_get(&table->json_table_info->columns, table->json_table_info->columns.count - 1);
    expr_node_t *func_node = new_col->expr->root;
    text_t temp = { NULL, 0 };
    uint32 i;

    json_func_att_init(&func_node->json_func_attr);
    func_node->json_func_attr.ignore_returning = CT_TRUE;
    CT_RETURN_IFERR(sql_set_json_func_attr(stmt, &lex->curr_text->value, &func_node->json_func_attr,
        json_func_att_match_returning));
    func_node->type = EXPR_NODE_FUNC;

    for (i = 0; i < column_type_count; i++) {
        CT_RETURN_IFERR(lex_try_fetch(lex, g_json_column_parse_attr[i].start_word, &result));
        if (!result) {
            continue;
        }
        temp.str = g_json_column_parse_attr[i].func_name;
        temp.len = g_json_column_parse_attr[i].func_len;
        CT_RETURN_IFERR(sql_copy_text(stmt->context, &temp, &func_node->word.func.name.value));
        CT_RETURN_IFERR(g_json_column_parse_attr[i].json_column_parse_func(stmt, word, new_col));
        CT_RETURN_IFERR(sql_set_json_func_attr(stmt, &lex->curr_text->value, &func_node->json_func_attr,
            json_func_att_match_on_error));
        if (!JSON_FUNC_ATT_HAS_ON_ERROR(func_node->json_func_attr.ids)) {
            set_json_func_default_error_type(func_node, table->json_table_info->json_error_info.type);
        }
        return CT_SUCCESS;
    }
    CT_SRC_THROW_ERROR(lex->loc, ERR_SQL_SYNTAX_ERROR, "unsupported json table column type");
    return CT_ERROR;
}

static status_t sql_parse_json_column(sql_stmt_t *stmt, sql_table_t *table, word_t *word)
{
    bool32 result = CT_FALSE;
    lex_t *lex = stmt->session->lex;

    for (;;) {
        CT_RETURN_IFERR(lex_try_fetch(lex, "nested", &result));
        if (result) {
            CT_SRC_THROW_ERROR(lex->loc, ERR_SQL_SYNTAX_ERROR, "json_table nested path column not supported");
            return CT_ERROR;
        } else {
            CT_RETURN_IFERR(sql_create_json_column(stmt, table, word));
            CT_RETURN_IFERR(lex_try_fetch(lex, "for", &result));
            if (result) {
                CT_RETURN_IFERR(lex_expected_fetch_word(lex, "ordinality"));
                create_ordinality_for_json_table(table);
            } else {
                CT_RETURN_IFERR(sql_create_json_func_column(stmt, word, table));
            }
        }
        CT_RETURN_IFERR(lex_fetch(lex, word));
        if (!IS_SPEC_CHAR(word, ',')) {
            break;
        }
    }

    if (word->type != WORD_TYPE_EOF) {
        CT_SRC_THROW_ERROR_EX(word->loc, ERR_SQL_SYNTAX_ERROR, "unexpected word '%s' found", W2S(word));
        return CT_ERROR;
    }
    return CT_SUCCESS;
}

static status_t sql_parse_json_table_on_error_clause(sql_stmt_t *stmt, lex_t *lex, sql_table_t *table, word_t *word)
{
    uint32 match_id = CT_INVALID_ID32;

    CT_RETURN_IFERR(lex_try_fetch_1of3(lex, "error", "null", "default", &match_id));
    switch (match_id) {
        case JSON_RETURN_ERROR:
            table->json_table_info->json_error_info.type = JSON_RETURN_ERROR;
            break;
        case JSON_RETURN_NULL:
            table->json_table_info->json_error_info.type = JSON_RETURN_NULL;
            break;
        case JSON_RETURN_DEFAULT:
            table->json_table_info->json_error_info.type = JSON_RETURN_DEFAULT;
            CT_RETURN_IFERR(sql_create_expr_until(stmt, &table->json_table_info->json_error_info.default_value, word));
            lex_back(lex, word);
            break;
        default:
            return CT_SUCCESS;
    }
    return lex_expected_fetch_word2(lex, "on", "error");
}

status_t sql_parse_json_table(sql_stmt_t *stmt, sql_table_t *table, word_t *word)
{
    status_t status = CT_ERROR;
    lex_t *lex = stmt->session->lex;
    var_word_t var_word;

    CTSQL_SAVE_STACK(stmt);
    do {
        CT_BREAK_IF_ERROR(sql_word_as_table(stmt, word, &var_word));
        table->user = var_word.table.user;
        table->name = var_word.table.name;

        CT_BREAK_IF_ERROR(sql_create_expr_until(stmt, &table->json_table_info->data_expr, word));
        if (IS_KEY_WORD(word, KEY_WORD_FORMAT)) {
            CT_RETURN_IFERR(lex_expected_fetch_word(lex, "json"));
            table->json_table_info->data_expr->root->format_json = CT_TRUE;
            CT_BREAK_IF_ERROR(lex_fetch(lex, word));
        }
        if (!IS_SPEC_CHAR(word, ',')) {
            CT_SRC_THROW_ERROR(word->loc, ERR_SQL_SYNTAX_ERROR, "',' expected");
            return CT_ERROR;
        }
        CT_BREAK_IF_ERROR(lex_fetch(lex, word));
        table->json_table_info->basic_path_loc = word->loc;
        CT_BREAK_IF_ERROR(sql_set_json_table_column_path(stmt, word, &table->json_table_info->basic_path_txt));

        CT_BREAK_IF_ERROR(sql_parse_json_table_on_error_clause(stmt, lex, table, word));

        CT_BREAK_IF_ERROR(lex_expected_fetch_word(lex, "columns"));
        CT_BREAK_IF_ERROR(lex_expected_fetch_bracket(lex, word));
        CT_BREAK_IF_ERROR(lex_push(lex, &word->text));
        CT_BREAK_IF_ERROR(sql_parse_json_column(stmt, table, word));
        if (lex->curr_text->value.len > 0) {
            CT_SRC_THROW_ERROR(lex->loc, ERR_SQL_SYNTAX_ERROR, "unexpected string");
            return CT_ERROR;
        }
        lex_pop(lex);
        CT_BREAK_IF_ERROR(lex_expected_end(lex));

        status = CT_SUCCESS;
    } while (0);

    CTSQL_RESTORE_STACK(stmt);
    return status;
}

static status_t sql_set_depend_table_of_json_table(sql_verifier_t *verf, sql_query_t *query, sql_table_t *table)
{
    uint32 i;
    biqueue_t *cols_que = NULL;
    biqueue_node_t *curr = NULL;
    biqueue_node_t *end = NULL;
    json_table_info_t *json_info = table->json_table_info;
    uint32 *depend_tables = NULL;
    expr_node_t *col = NULL;
    cols_used_t cols_used;

    CT_RETURN_IFERR(sql_push(verf->stmt, table->id * sizeof(uint32), (void **)&depend_tables));
    init_cols_used(&cols_used);
    sql_collect_cols_in_expr_node(table->json_table_info->data_expr->root, &cols_used);
    cols_que = &cols_used.cols_que[SELF_IDX];
    curr = biqueue_first(cols_que);
    end = biqueue_end(cols_que);
    while (curr != end) {
        col = OBJECT_OF(expr_node_t, curr);
        for (i = 0; i < json_info->depend_table_count; i++) {
            if (depend_tables[i] == TAB_OF_NODE(col)) {
                break;
            }
        }
        if (i == json_info->depend_table_count) {
            depend_tables[table->json_table_info->depend_table_count] = TAB_OF_NODE(col);
            table->json_table_info->depend_table_count++;
        }
        curr = curr->next;
    }
    if (json_info->depend_table_count > 0) {
        uint32 alloc_size = json_info->depend_table_count * sizeof(uint32);
        CT_RETURN_IFERR(sql_alloc_mem(verf->stmt->context, alloc_size, (void **)&json_info->depend_tables));
        MEMS_RETURN_IFERR(memcpy_s(json_info->depend_tables, alloc_size, depend_tables, alloc_size));
    }

    return CT_SUCCESS;
}

static status_t sql_verify_json_table_data_info(sql_verifier_t *verf, sql_query_t *query, sql_table_t *table,
    json_assist_t *ja)
{
    uint32 table_count = query->tables.count;
    uint32 excl_flag = verf->excl_flags;
    json_table_info_t *json_info = table->json_table_info;

    CT_RETURN_IFERR(sql_alloc_mem(verf->stmt->context, sizeof(json_path_t), (void **)&json_info->basic_path));
    CT_RETURN_IFERR(
        json_path_compile(ja, &json_info->basic_path_txt, json_info->basic_path, json_info->basic_path_loc));
    if (json_info->basic_path->count == 0) {
        CT_SRC_THROW_ERROR(json_info->data_expr->loc, ERR_SQL_SYNTAX_ERROR, "wrong json path expr");
        return CT_ERROR;
    }
    verf->tables = &query->tables;
    verf->tables->count = table->id;
    verf->excl_flags |= SQL_JSON_TABLE_EXCL;
    CT_RETURN_IFERR(sql_verify_expr(verf, json_info->data_expr));
    verf->excl_flags = excl_flag;
    query->tables.count = table_count;
    verf->tables = NULL;

    if (table->id == 0 || json_info->data_expr->root->type == EXPR_NODE_CONST) {
        return CT_SUCCESS;
    }
    return sql_set_depend_table_of_json_table(verf, query, table);
}

static status_t inline sql_verify_json_table_error_clause(sql_verifier_t *verf, json_error_info_t *json_error_info)
{
    if (json_error_info->type == JSON_RETURN_DEFAULT) {
        CT_RETURN_IFERR(sql_verify_expr(verf, json_error_info->default_value));
        if (json_error_info->default_value->root->type != EXPR_NODE_CONST) {
            CT_SRC_THROW_ERROR(json_error_info->default_value->loc, ERR_SQL_SYNTAX_ERROR,
                "default value must be const");
            return CT_ERROR;
        }
    }
    return CT_SUCCESS;
}

status_t sql_verify_json_table(sql_verifier_t *verf, sql_query_t *query, sql_table_t *table)
{
    uint32 incl_flags = verf->incl_flags;
    uint32 i = 0;
    rs_column_t *column = NULL;
    expr_tree_t *path_expr = NULL;
    json_path_t *path = NULL;
    json_assist_t ja;

    verf->curr_query = query;
    verf->stmt->context->opt_by_rbo = CT_TRUE;
    verf->incl_flags |= SQL_INCL_JSON_TABLE;
    table->cbo_attr.type |= SELTION_NO_HASH_JOIN;

    CTSQL_SAVE_STACK(verf->stmt);
    CT_RETURN_IFERR(sql_verify_json_table_error_clause(verf, &table->json_table_info->json_error_info));
    JSON_ASSIST_INIT(&ja, verf->stmt);
    do {
        CT_BREAK_IF_ERROR(sql_verify_json_table_data_info(verf, query, table, &ja));

        for (; i < table->json_table_info->columns.count; i++) {
            column = (rs_column_t *)cm_galist_get(&table->json_table_info->columns, i);
            CT_BREAK_IF_ERROR(sql_verify_expr(verf, column->expr));
            column->typmod = column->expr->root->typmod;
            if (column->expr->root->type != EXPR_NODE_FUNC) {
                continue;
            }
            *column->expr->root->argument->root = *table->json_table_info->data_expr->root;
            path_expr = column->expr->root->argument->next;
            if (path_expr->root->type != EXPR_NODE_CONST || !CT_IS_STRING_TYPE(path_expr->root->value.type)) {
                CT_SRC_THROW_ERROR(path_expr->loc, ERR_SQL_SYNTAX_ERROR,
                    "json column path expression must be a const text literal");
                break;
            }
            CT_BREAK_IF_ERROR(sql_alloc_mem(verf->stmt->context, sizeof(json_path_t), (void **)&path));
            CT_BREAK_IF_ERROR(json_path_compile(&ja, &path_expr->root->value.v_text, path, path_expr->loc));
            if (path->count + table->json_table_info->basic_path->count > JSON_PATH_MAX_LEVEL + 1) {
                CT_THROW_ERROR_EX(ERR_JSON_PATH_SYNTAX_ERROR, "exceed max path nest level(maximum: %u)",
                    JSON_PATH_MAX_LEVEL);
                break;
            }
            path_expr->root->value.v_json_path = path;
            CTSQL_RESTORE_STACK(verf->stmt);
        }
    } while (0);
    JSON_ASSIST_DESTORY(&ja);
    CTSQL_RESTORE_STACK(verf->stmt);
    verf->incl_flags = incl_flags;
    return (i == table->json_table_info->columns.count) ? CT_SUCCESS : CT_ERROR;
}

status_t handle_json_table_data_error(json_assist_t *ja, json_error_type_t err_type, bool8 *eof)
{
    int32 err_code;
    const char *err_msg = NULL;
    cm_get_error(&err_code, &err_msg, NULL);
    if (!IS_JSON_ERR(err_code)) {
        return CT_ERROR;
    }
    CT_LOG_DEBUG_INF("[JSON] CT-%05d, %s", err_code, err_msg);
    if (ja->is_overflow || err_type == JSON_RETURN_ERROR) {
        return CT_ERROR;
    }
    cm_reset_error();
    *eof = CT_TRUE;
    return CT_SUCCESS;
}

void sql_try_switch_json_array_element(json_value_t *jv, json_path_step_t *step, json_step_loc_t *loc, bool32 *switched)
{
    uint32 index = step->index_pairs_list[loc->pair_idx].from_index + loc->pair_offset;
    if (step->index_pairs_count == 0) {
        if (index + 1 < JSON_ARRAY_SIZE(jv)) {
            loc->pair_offset++;
            *switched = CT_TRUE;
        } else {
            loc->pair_offset = 0;
        }
    } else {
        if (loc->pair_offset + step->index_pairs_list[loc->pair_idx].from_index <
            step->index_pairs_list[loc->pair_idx].to_index) {
            loc->pair_offset++;
            *switched = CT_TRUE;
        } else if (loc->pair_idx + 1 < step->index_pairs_count) {
            loc->pair_offset = 0;
            loc->pair_idx++;
            *switched = CT_TRUE;
        } else {
            loc->pair_idx = 0;
            loc->pair_offset = 0;
        }
    }
}

static status_t verify_json_array_element_exists(sql_stmt_t *stmt, json_value_t *jv, json_table_exec_t *exec,
    uint32 level, bool32 *result);
static status_t verify_json_array_element_exists(sql_stmt_t *stmt, json_value_t *jv, json_table_exec_t *exec,
    uint32 level, bool32 *result)
{
    json_step_loc_t *loc = &exec->loc[level];
    json_path_step_t *step = &exec->basic_path->steps[level];
    uint32 index = step->index_pairs_list[loc->pair_idx].from_index + loc->pair_offset;

    if (level == exec->basic_path->count - 1) {
        if (JSON_ARRAY_SIZE(jv) != 0) {
            exec->exists = CT_TRUE;
        }
    } else if (JSON_ARRAY_SIZE(jv) > index) {
        CT_RETURN_IFERR(sql_visit_json_value(stmt, JSON_ARRAY_ITEM(jv, index), exec, level, result,
            verify_json_array_element_exists));
    }
    return CT_SUCCESS;
}

status_t sql_try_switch_json_array_loc(sql_stmt_t *stmt, json_value_t *jv, json_table_exec_t *exec, uint32 temp_level,
    bool32 *switched)
{
    uint32 level = temp_level;
    json_path_t *basic_path = exec->basic_path;
    json_path_step_t *step = &basic_path->steps[level];
    json_step_loc_t *loc = &exec->loc[level];
    json_value_t *element = NULL;
    uint32 index = step->index_pairs_list[loc->pair_idx].from_index + loc->pair_offset;
    bool32 is_last = CT_FALSE;

    if (level == basic_path->count - 1) {
        if (!exec->table_ready) {
            if (JSON_ARRAY_SIZE(jv) != 0) {
                *switched = CT_TRUE;
            }
        } else if (exec->last_extend) {
            sql_try_switch_json_array_element(jv, step, loc, switched);
        }
    } else if (index < JSON_ARRAY_SIZE(jv)) {
        element = JSON_ARRAY_ITEM(jv, index);
        if (element->type != JSON_VAL_OBJECT) {
            level++;
        }
        CT_RETURN_IFERR(sql_visit_json_value(stmt, JSON_ARRAY_ITEM(jv, index), exec, level, switched,
            sql_try_switch_json_array_loc));
        while (!(*switched) && !is_last) {
            sql_try_switch_json_array_element(jv, step, loc, switched);
            index = step->index_pairs_list[loc->pair_idx].from_index + loc->pair_offset;
            if (*switched) {
                exec->exists = CT_FALSE;
                CT_RETURN_IFERR(sql_visit_json_value(stmt, JSON_ARRAY_ITEM(jv, index), exec, level, switched,
                    verify_json_array_element_exists));
                is_last = (step->index_pairs_count > 0) ? (loc->pair_idx == step->index_pairs_count - 1 &&
                    index == step->index_pairs_list[loc->pair_idx].to_index) :
                                                          (index == JSON_ARRAY_SIZE(jv));
                *switched = (bool32)exec->exists;
            } else {
                is_last = CT_TRUE;
            }
        }
    }
    return CT_SUCCESS;
}

status_t sql_visit_json_value(sql_stmt_t *stmt, json_value_t *jv, json_table_exec_t *exec, uint32 temp_level,
    bool32 *switched, json_value_visit_func visit_func)
{
    CT_RETURN_IFERR(sql_stack_safe(stmt));
    uint32 level = temp_level;
    uint32 index;
    json_path_t *basic_path = exec->basic_path;
    json_path_step_t *step = NULL;
    json_pair_t *pair = NULL;

    switch (jv->type) {
        case JSON_VAL_ARRAY:
            return visit_func(stmt, jv, exec, level, switched);
        case JSON_VAL_OBJECT:
            if (level == basic_path->count) {
                return CT_SUCCESS;
            }
            step = &basic_path->steps[++level];
            for (index = 0; index < JSON_OBJECT_SIZE(jv); index++) {
                pair = JSON_OBJECT_ITEM(jv, index);
                if (pair->key.string.len != step->keyname_length ||
                    cm_compare_text_str(&pair->key.string, step->keyname) != 0) {
                    continue;
                }
                if (step->index_pairs_count != 0 && step->index_pairs_list[0].from_index != 0 &&
                    JSON_OBJECT_ITEM(jv, index)->val.type != JSON_VAL_ARRAY) {
                    CT_THROW_ERROR(ERR_JSON_VALUE_MISMATCHED, "JSON_VALUE", "no");
                    return CT_ERROR;
                }
                return sql_visit_json_value(stmt, &JSON_OBJECT_ITEM(jv, index)->val, exec, level, switched, visit_func);
            }
            // fall through
        default:
            if ((!exec->table_ready) && level >= basic_path->count - 1) {
                *switched = CT_TRUE;
            } else if (level >= basic_path->count - 1) {
                exec->exists = CT_TRUE;
            }
            break;
    }
    return CT_SUCCESS;
}

void sql_get_json_table_curr_path(json_table_exec_t *exec, json_path_t *ori_path, json_path_t *json_curr_path)
{
    uint32 i;
    json_path_step_t *json_curr_step = NULL;
    json_step_loc_t step_loc;

    for (i = 0; i < json_curr_path->count; i++) {
        json_curr_step = &json_curr_path->steps[i];
        json_curr_step->index_flag = 0;
        step_loc = exec->loc[i];
        json_curr_step->index_pairs_count = 1;
        if (json_curr_step->index_pairs_count > 0) {
            json_curr_step->index_pairs_list[0].from_index =
                json_curr_step->index_pairs_list[step_loc.pair_idx].from_index + step_loc.pair_offset;
        } else {
            json_curr_step->index_pairs_list[0].from_index = step_loc.pair_offset;
        }
        json_curr_step->index_pairs_list[0].to_index = json_curr_step->index_pairs_list[0].from_index;
    }

    if (!exec->last_extend) {
        json_curr_path->steps[json_curr_path->count - 1].index_pairs_count = 0;
    }

    for (i = 1; i < ori_path->count; i++) {
        json_curr_path->steps[json_curr_path->count] = ori_path->steps[i];
        json_curr_path->steps[json_curr_path->count].index_flag = 0;
        json_curr_path->count++;
    }
    return;
}

status_t sql_calc_json_table_column_result(json_assist_t *ja, rs_column_t *col, json_table_exec_t *exec,
    variant_t *result)
{
    json_value_t *jv_expr = exec->json_value;
    if (col->expr->root->type != EXPR_NODE_FUNC) {
        result->is_null = CT_FALSE;
        result->type = CT_TYPE_BIGINT;
        result->v_bigint = exec->ordinality;
        return CT_SUCCESS;
    } else {
        json_path_t *ori_path = (json_path_t *)col->expr->root->argument->next->root->value.v_json_path;
        // json_curr_path is a temp variant, use stack memory
        json_path_t json_curr_path = *exec->basic_path;
        sql_get_json_table_curr_path(exec, ori_path, &json_curr_path);
        return json_func_get_result(ja, col->expr->root, result, &json_curr_path, jv_expr);
    }
}
