#ifndef _LVOS_PUB_H_
#define _LVOS_PUB_H_

/* �������ϵͳ��غ�, Ĭ��ΪLINUX�û�̬����  */
#if defined(WIN32) || defined(_PCLINT_)

#ifndef DESC
#define DESC(x) 1 /* �ļ��ֶ�������  */
#endif

#ifndef _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE
#endif

#ifdef _PCLINT_
#undef _DEBUG   /* PC-Lint����Release�汾��׼���� */
#endif

#ifndef BUILD_WITH_ACE
#define _CRTDBG_MAP_ALLOC
#endif

#define _WIN32_WINNT 0x0600
#define WIN32_LEAN_AND_MEAN /* windows.h�в�����winsock.h, ���浥��ʹ��winsock2.h */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winsock2.h>
#include <stddef.h>
#include <io.h>
#include <crtdbg.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <share.h>

/* �Զ���ͷ�ļ�  */
#include "vos_win/vos/lvos_version.h"
#include "vos_win/vos/lvos_type.h"          /* �������Ͷ���  */
#include "vos_win/vos/return.h"             /* ���������붨��  */
#include "vos_win/vos/pid.h"                /* ����ϵͳ������PID */
#include "vos_win/vos/lvos_macro.h"         /* ȫ�ֺ궨�� */
#include "vos_win/vos/lvos_atomic.h"        /* Linux�ں˵�atomic���ܷ��� */
#include "vos_win/vos/lvos_bitops.h"        /* λ����ͷ�ļ� */
#include "vos_win/vos/lvos_list.h"          /* ��������궨�� */
#include "vos_win/vos/lvos_hash.h"          /* ��ֲ��linux/hash.h, ����HASH��ת�� */
#include "vos_win/vos/lvos_mb.h"            /* �ڴ����� */
#include "vos_win/vos/lvos_lock.h"          /* �ź�����������ض���  */
#include "vos_win/vos/lvos_byteorder.h"     /* �����ֽ���ת���Ĺ��� */
#include "vos_win/vos/lvos_sched.h"         /* �̵߳���ͷ�ļ� */
#include "vos_win/vos/lvos_debug.h"         /* ����ģ��ͷ�ļ� */
#include "vos_win/vos/lvos_diag.h"
#include "vos_win/vos/lvos_mem.h"           /* �ڴ����ͷ�ļ� */
#include "vos_win/vos/lvos_tracepoint.h"
#include "vos_win/vos/lvos_lib.h"           /* ��׼��ķ�װ */
#include "vos_win/vos/lvos_time.h"          /* ʱ�书�� */
#include "vos_win/vos/lvos_thread.h"        /* �̹߳�����ض���  */
#include "vos_win/vos/lvos_socket.h"        /* socket���� */
#include "vos_win/vos/lvos_file.h"          /* �����ļ���ز��� */
#include "vos_win/vos/lvos_shm.h"           /* �ڴ湲��ͷ�ļ� */
#include "vos_win/vos/lvos_wait.h"          /* �ȴ�����ͷ�ļ� */
#include "vos_win/vos/lvos_completion.h"    /* ��ɱ���ͷ�ļ� */
#include "vos_win/vos/lvos_sysinfo.h"       /* ϵͳ������Ϣ��ѯ */
#include "vos_win/vos/lvos_timer.h"         /* ��ʱ�� */
#include "vos_win/vos/lvos_timer2.h"
#include "vos_win/vos/lvos_sched_work.h"    /* �첽����ִ�нӿ� */
#include "vos_win/vos/lvos_syscall.h"       /* VOS���ṩ��ϵͳ���û��ƽӿ� */
#include "vos_win/vos/os_intf.h"            /* OS�ṩ�ĺ�Ӳ��ǿ��صĽӿ� */
#include "vos_win/vos/lvos_stub.h"

/* �ϲ�ҵ��ķ����룬Ϊ����ʹ����������� */
#include "return.h"

/* LINUX_KERNEL  */
#elif defined(__KERNEL__)  
#include <vos/lvos.h>
#include <vos/lvos_callback.h>
#include <vos/lvos_crypt.h>
#include <vos/lvos_file.h>
#include <vos/lvos_hash.h>
#include <vos/lvos_hrtimer.h>
#include <vos/lvos_lib.h>
#include <vos/lvos_list.h>
#include <vos/lvos_lock.h>
#include <vos/lvos_logid.h>
#include <vos/lvos_mem.h>
#include <vos/lvos_sched.h>
#include <vos/lvos_shm.h>
#include <vos/lvos_socket.h>
#include <vos/lvos_syscall.h>
#include <vos/lvos_sysinfo.h>
#include <vos/lvos_thread.h>
#include <vos/lvos_time.h>
#include <vos/lvos_timer.h>
#include <vos/lvos_tracepoint.h>
#include <vos/lvos_version.h>
#include <vos/lvos_wait.h>
#include <vos/lvos_aio.h>
#include <vos/lvos_blk.h>
#include <vos/lvos_zlib.h>
#include <vos/lvos_reboot.h>
#include <vos/os_intf.h>
#include "return.h"

#elif defined(__DPAX_LINUX_USR__) || defined(__DPAX_LINUX__) 
#include "dpax_lvos.h"
#include "return.h"


/* LINUX_USER  */
#else
#if !defined(__KAPI__) && !defined(__KAPI_USR__)
//#define __LINUX_USR__
#endif
//#include <vos/lvos.h>
#endif 
 
#endif /* _LVOS_PUB_H_ */
