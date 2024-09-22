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
 * mes_tcp.h
 *
 *
 * IDENTIFICATION
 * src/mec/mes_tcp.h
 *
 * -------------------------------------------------------------------------
 */

#ifndef MES_TCP_H__
#define MES_TCP_H__

#include "cm_defs.h"
#include "cm_thread.h"
#include "cs_pipe.h"
#include "mes_func.h"

#ifdef __cplusplus
extern "C" {
#endif

status_t mes_init_tcp(void);
void mes_destroy_tcp(void);
status_t mes_tcp_connect(uint32 inst_id);
void mes_tcp_disconnect(uint32 inst_id);
void mes_tcp_disconnect_async(uint32 inst_id);
status_t mes_tcp_send_data(const void *msg_data);
status_t mes_cms_tcp_send_data(const void *msg_data);
status_t mes_tcp_send_bufflist(mes_bufflist_t *buff_list);
bool32 mes_tcp_connection_ready(uint32 inst_id);
mes_channel_stat_t mes_tcp_get_channel_state(uint32 inst_id);
bool32 mes_ssl_connection_ready(uint32 inst_id);

#ifdef __cplusplus
}
#endif

#endif
