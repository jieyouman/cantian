/******************************************************************************

                  ��Ȩ���� (C), 2009-2009, ��Ϊ�������˿Ƽ����޹�˾

 ******************************************************************************
  �� �� ��   : lvos_wait.h
  �� �� ��   : ����

  ��������   : 2009��5��12��
  ����޸�   :
  ��������   : ��ȴ�������ص�ͨ�ù��ܽӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2009��5��12��

    �޸�����   : �����ļ�

******************************************************************************/
/**
    \file  lvos_wait.h
    \brief �ȴ����й��ܣ�����linux�ں�̬�µĵȴ����нӿ�
    \note  ֧��windows/linux_kernel���ȴ������п��ܵ��µ�������������˲������ڲ����������ĵ���������
    \date 2009��5��12��
*/

/** \addtogroup VOS_WAIT �ȴ����й���
    @{
*/

#ifndef __LVOS_WAIT_H__
#define __LVOS_WAIT_H__

#if defined(WIN32) || defined(__KERNEL__)
/********************** ����windowsƽ̨��ʹ�õĵȴ��������ݽṹ begin ************************/
#ifdef WIN32
/** \brief �ȴ����У���װlinux�µ�struct wait_queue_head_t */
typedef struct
{
    CRITICAL_SECTION CriticalSection;
    HANDLE hEvent;
}LVOS_WAIT_QUEUE_S;

/**
    \brief Linux�ں�̬�µȴ��¼�����
    \param[in] wq      �ȴ�����ָ��
    \param[in] condition       ��������
    \retval    void
*/

#define LVOS_WaitEvent(wq,condition) \
do {\
    LVOS_MightSleep(); \
    while (!(condition))\
    {\
        DWORD dwRet;\
        dwRet = WaitForSingleObject((wq).hEvent,(OSP_ULONG)INFINITE); \
        if (WAIT_OBJECT_0 != dwRet)\
        {\
            DBG_ASSERT_EXPR(0, "WaitForSingleObject return an unexpected error :0x%x, LastError: %u", dwRet, GetLastError()); \
            break;\
        }\
    }\
}while (0)

/**
    \brief Linux�ں�̬�µȴ��¼�����
    \param[in] wq      �ȴ�����ָ��
    \param[in] condition       ��������
    \param[in] timeout         ��ʱʱ��
    \retval    void
*/
#define LVOS_WaitEventTimeout(wq,condition,timeout) \
do {\
    LVOS_MightSleep();\
    if (!(condition))\
    {\
        (void)WaitForSingleObject((wq).hEvent,(timeout));\
    }\
}while (0)

/**
    \brief �������еȴ��¼��Ľ���
    \note  �������еȴ������ϵȴ��¼��Ľ���
    \param[in] wq        �ȴ�����ָ��
    \retval    void
*/
#define LVOS_WakeUp(wq)\
do {\
    (void)SetEvent((wq)->hEvent);\
}while (0)

/**
    \brief Windows�³�ʼ���ȴ�����
    \param[in] v_pstWQ        �ȴ�����ָ��
    \retval    void
*/
static inline void LVOS_InitWaitQueue( LVOS_WAIT_QUEUE_S *v_pstWQ )
{
    _ASSERT(NULL != v_pstWQ);

    InitializeCriticalSection(&(v_pstWQ->CriticalSection));

    v_pstWQ->hEvent = CreateEvent( NULL,               /* default security attributes*/
                                    FALSE,               /* manual-reset event*/
                                    FALSE,              /* initial state is nonsignaled*/
                                    NULL
                                    );

    return;
}

/**
    \brief Windows������ָ���ĵȴ�����
    \param[in] v_pstWQ       �ȴ�����ָ��
    \retval    void
*/
static inline void LVOS_DestroyWaitQueue( LVOS_WAIT_QUEUE_S *v_pstWQ )
{

    _ASSERT(NULL != v_pstWQ);

    DeleteCriticalSection(&(v_pstWQ->CriticalSection));
    CloseHandle(v_pstWQ->hEvent);
    return;
}


#elif defined(__KERNEL__)
#include <linux/wait.h>

typedef wait_queue_head_t LVOS_WAIT_QUEUE_S;

/**
    \brief Linux�ں�̬�µȴ��¼�����
    \param[in] v_pstWQ      �ȴ�����ָ��
    \param[in] condition       ��������
    \retval    void
*/
#define LVOS_WaitEvent(wq,condition) wait_event(wq, condition)

/**
    \brief Linux�ں�̬�µȴ��¼�����
    \param[in] v_pstWQ      �ȴ�����ָ��
    \param[in] condition       ��������
    \param[in] timeout         ��ʱʱ��
    \retval    void
*/
#define LVOS_WaitEventTimeout(wq, condition, timeout) wait_event_timeout(wq, condition, timeout)

/**
    \brief Linux�ں�̬�³�ʼ���ȴ���
    \param[in] v_pstWQ        �ȴ�����ָ��
    \retval    void
*/
#define LVOS_InitWaitQueue(wq) init_waitqueue_head(wq)

/**
    \brief Linux�ں�̬������ָ���ĵȴ�����
    \note  �ú�����Linux�ں�̬��Ϊ��
    \param[in] v_pstWQ        �ȴ�����ͷָ��
    \retval    void
*/
#define LVOS_DestroyWaitQueue(pstWQHead)

/**
    \brief ����һ���ȴ��¼��Ľ���
    \note  ����һ���ȴ������ϵȴ��¼� �Ľ���
    \param[in] v_pstWQ        �ȴ�����ָ��
    \retval    void
*/
#define LVOS_WakeUp(v_pstWQ) wake_up_all(v_pstWQ)
#endif
#endif

#endif /* __LVOS_WATI_H__ */

/** @} */

