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
 * tms_sig_calltrace.h
 *
 *
 * IDENTIFICATION
 * src/tms/tms_sig_calltrace.h
 *
 * -------------------------------------------------------------------------
 */
#ifndef TMS_SIG_CALLTRANCE_H
#define TMS_SIG_CALLTRANCE_H

#include <signal.h>
#include <pthread.h>
#include "cm_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SIGTIMEOUT        62 // SIGRTMAX-2

status_t tms_dump_thread_stack_sig(pid_t dwPid, pid_t dwTid);

status_t tms_sigcap_reg_proc(int32 sig_num);

#ifdef __cplusplus
}
#endif

#endif