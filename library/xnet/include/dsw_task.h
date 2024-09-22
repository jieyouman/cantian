/**
 *          Copyright 2011 - 2015, Huawei Tech. Co., Ltd.
 *                      ALL RIGHTS RESERVED
 *
 * dsw_task.h
 *

 * @create: 2012-04-23
 *
 */

#ifndef __DSW_TASK_H__
#define __DSW_TASK_H__

#include <pthread.h>
#ifdef __cplusplus
extern "C" {
#endif /* __cpluscplus */

#define DSW_TASK_NAME_BUF_LEN       (32)
#define DSW_TASK_NAME_LEN_MAX       (DSW_TASK_NAME_BUF_LEN - 1)

#define DSW_MODULE_TASK_NUM_MAX     (32) /*vbs���̲߳�ֺ󣬵�mid֧�ֶ���߳�*/
#define DSW_SYSTEM_TASK_NUM_MAX     (DSW_MID_NR * DSW_MODULE_TASK_NUM_MAX)

#define DSW_TASK_PRIORITY_HIGH      0
#define DSW_TASK_PRIORITY_MIDDLE    1
#define DSW_TASK_PRIORITY_LOW       2
#define DSW_TASK_PRIORITY_DEFAULT   -1

#define DSW_TASK_BIND_CPU_MASK_DEFAULT  0xFFFFFFFFFFFFFFFF

#define DSW_TASK_IN_WAIT            1
#define DSW_TASK_NOT_IN_WAIT        0

typedef enum
{
    DSW_TASK_SUSPENDING,
    DSW_TASK_ACTIVE,
    DSW_TASK_CANCELLED,
    
    DSW_TASK_STATE_COUNT
} dsw_task_run_state_t;

/*
 * Definition of Module Task
 *
 * Each module has at most DSW_MODULE_TASK_NUM_MAX tasks, and each task
 * corresponds to a thread.
 *
 * Creation of thread is completed with call back function supplied by user and
 * the thread of module must wait for the unified start message from DSWare.
 *
 * Data introduced by user at the time of creating thread must be stored in
 * user data collection first, and then be got out in the thread function.
 */
typedef dsw_int (*dsw_task_routine_t) (void *arg);

typedef struct dsw_task_s
{
    dsw_module_t               *module;
    char                        name[DSW_TASK_NAME_BUF_LEN];

    pthread_t                   tid;
    pid_t                       pid;
    dsw_int                     priority;
    dsw_u64                     run_cpu_mask;
    dsw_task_routine_t          routine_func;           /* thread function */
    void                       *arg;                    /* user data */

    pthread_cond_t              cond;
    pthread_mutex_t             mutex;
    volatile dsw_task_run_state_t  task_state;
    dsw_u32                     task_in_wait;   /*DSW_TASK_IN_WAIT��ʾ�̴߳��ڵȴ�����״̬*/
} dsw_task_t;

// extern dsw_int g_bind_task_to_cpu;
// extern dsw_u64 g_bind_cpu;
DECLARE_OSD_VAR(dsw_u64, g_bind_cpus);
#define g_bind_cpu OSD_VAR(g_bind_cpus)

dsw_int dsw_task_init();
dsw_int dsw_task_register_info(dsw_u8, char *, dsw_int, dsw_u64, dsw_task_routine_t, void *);
dsw_int dsw_task_create(dsw_task_t *);
dsw_int dsw_task_run(dsw_task_t *);
dsw_int dsw_task_cancel(dsw_task_t *);
dsw_int dsw_task_wait_exit(dsw_task_t *);
dsw_int dsw_task_wait_all_exit(int max_wait_seconds);
dsw_int dsw_set_thread_name(char* thread_name);
dsw_int dsw_get_thread_name(char* thread_name);

/*
 * - ��֧�ֽ����ڶ�ʵ���ĳ����£�һ��ʵ���˳�ʱ�����̲����˳���������ʵ������Ҫ����
 *
 * - ������������ʵ���˳�ʱ��ʵ���еĸ���ģ����̶߳���Ҫ�˳��������˳�ǰ�����������Դ
 *   ���ڴ桢�����������ӡ��ļ��ȵ�
 *
 * - ������ģ����߳��˳���ʱ�䲢����ȫͬ�����Ӷ�������: Aģ���߳����˳���������Aģ�����Դ;
 *   ��Bģ����δ�����꣬����ʹ��Aģ�����Դ���ͻ������Դʹ�ô�������⡣
 *
 * - �������һ��ͬ���㣬�ڸ�ģ����߳������꣬������Դ֮ǰ��Ҫ�ȴ�����ģ����̶߳������ͬ��
 *   ����ܼ���ִ�У�������Դ����
 *
 * - ģ���̺߳���ʾ���������:
 *   void module_a_task(void *task)
 *   {
 *       while (shoule_be_running())
 *       {
 *           process_a();
 *       }
 *
 *       XXXX                  <--- synchronize point(ͬ����)
 *
 *       destroy_resources_a();
 *   }
 *
 * - ���巽���ǽ�� Java �е� CountDownLatch �ĸ���ü�����ʾ��ǰδִ�е�ͬ������߳�����ÿ����
 *   ��ִ�е�ͬ�����ʱ�򣬾ͽ���������1��Ȼ��������ȴ�����������0����������ִ��������Դ�Ĳ���
 */

/**
 * ��ʼ����ʵ���� CountDownLatch
 */
dsw_int dsw_init_count_down_latch(void);

/**
 * �� CountDownLatch ����������1����ʾ����һ��ģ���߳���ִ��
 */
dsw_int dsw_increase_count_down_latch(void);

/**
 * �� CountDownLatch ����������1����ʾ��һ��ģ���߳����е���ͬ����
 */
dsw_int dsw_decrease_count_down_latch(void);

/**
 * �ȴ���������0�������������߳�
 */
void dsw_count_down_latch_wait(void);

#ifdef __cplusplus
}
#endif /* __cpluscplus */

#endif /* __DSW_TASK_H__ */

