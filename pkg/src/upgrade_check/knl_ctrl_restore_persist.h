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
 * knl_ctrl_restore_persist.h
 *
 *
 * IDENTIFICATION
 * src/upgrade_check/knl_ctrl_restore_persist.h
 *
 * -------------------------------------------------------------------------
 */
#ifndef __KNL_CTRL_RESTORE_PERSIST_H__
#define __KNL_CTRL_RESTORE_PERSIST_H__
 
#ifdef __cplusplus
extern "C" {
#endif

#define BACKUP_NODE_COUNT 2
#define NODE_SPACE_COUNT 6
typedef struct st_static_core_ctrl_items {
    char name[CT_DB_NAME_LEN];
    time_t init_time;
}static_core_ctrl_items_t;

typedef struct st_sys_table_entries {
    page_id_t sys_table_entry;
    page_id_t ix_sys_table1_entry;
    page_id_t ix_sys_table2_entry;
    page_id_t sys_column_entry;
    page_id_t ix_sys_column_entry;
    page_id_t sys_index_entry;
    page_id_t ix_sys_index1_entry;
    page_id_t ix_sys_index2_entry;
    page_id_t ix_sys_user1_entry;
    page_id_t ix_sys_user2_entry;
    page_id_t sys_user_entry;
}sys_table_entries_t;

typedef struct st_core_ctrl_log_info {
    uint64 lsn;
    uint64 lfn;
    log_point_t rcy_point;
    log_point_t lrp_point;
    knl_scn_t scn;
} core_ctrl_log_info_t;

typedef struct st_log_file_ctrl_bk {
    uint32 version;
    log_file_ctrl_t log_ctrl_bk;
} log_file_ctrl_bk_t;

typedef struct st_datafile_ctrl_bk {
    uint32 version;
    datafile_ctrl_t df_ctrl;
    uint32 file_no;
    uint32 space_id;
} datafile_ctrl_bk_t;

typedef struct st_space_ctrl_bk {
    uint32 id;
    bool32 used;
    char name[CT_NAME_BUFFER_SIZE];
    uint16 flg;
    uint16 block_size;
    uint32 extent_size;  // extent pages count
    uint32 file_hwm;     // max allocated datafile count
    uint32 type;
    knl_scn_t org_scn;
    uint8 encrypt_version;
    uint8 cipher_reserve_size;
    uint8 is_for_create_db;
    uint8 unused[CT_SPACE_CTRL_RESERVED_BYTES_13];
} space_ctrl_bk_t;

typedef struct st_backup_ctrl_bk {
    page_head_t page_head;
    datafile_header_t df_head;
    datafile_ctrl_bk_t df_ctrl;
    space_ctrl_bk_t space_ctrl;
    static_core_ctrl_items_t static_ctrl;
    sys_table_entries_t sys_entries;
    core_ctrl_log_info_t core_ctrl[BACKUP_NODE_COUNT];
    log_file_ctrl_bk_t log_ctrl[BACKUP_NODE_COUNT];
    reset_log_t reset_log;
    uint32 dbid;
} backup_ctrl_bk_t;
#ifdef __cplusplus
}
#endif

#endif