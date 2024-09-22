 /******************************************************************************

                  ��Ȩ���� (C), 2008-2008, ��Ϊ�������˿Ƽ����޹�˾

 ******************************************************************************
  �� �� ��   : lvos_thread.h
  �� �� ��   : ����

  ��������   : 2008��6��3��
  ����޸�   :
  ��������   : �̹߳����ܷ�װ
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2008��6��3��

    �޸�����   : �����ļ�

******************************************************************************/
/**
    \file  lvos_thread.h
    \brief �̹߳������ӿ�
    \date 2009��5��19��
*/

/** \addtogroup VOS_THREAD �߳̽ӿ�
    @{ 
*/

#ifndef __LVOS_THREAD_H__
#define __LVOS_THREAD_H__

#include "dpax_thrd.h"

/** \brief �߳����ȼ�ö�٣�ʹ��ʱ��ֱ��ʹ�ú꣬��Ҫֱ��ʹ�ú�ֵ */
typedef enum tagLVOS_THRD_PRI_E
{
    LVOS_THRD_PRI_HIGHEST = 0,        /**< ��߼� */
    LVOS_THRD_PRI_HIGH,               /**< �߼� */
    LVOS_THRD_PRI_SUBHIGH,            /**< �θ� */
    LVOS_THRD_PRI_MIDDLE,             /**< �м伶 */
    LVOS_THRD_PRI_LOW,                /**< �ͼ� */
    LVOS_THRD_PRI_BUTT
} LVOS_THRD_PRI_E;

#ifndef WIN32
#define WINAPI /* Ϊ����WINDOWS������  */
#endif

/** \brief �̴߳�����ԭ��
    \sa LVOS_CreateThread
*/
typedef OSP_S32 (WINAPI *PLVOSTHREAD_START_ROUTINE)(void *);

/** \brief �����߳�
    \param[in] v_pfnStartRoutine �̴߳�����
    \param[in] v_pArg ����v_pfnStartRoutine�����Ĳ���
    \param[out] v_pulThreadId �����ɹ��������߳�ID
    \retval RETURN_OK �����ɹ�
    \retval RETURN_ERROR ����ʧ��
    \attention �̴߳�����Ϊ�˼���WIN32������Ҫ����WINAPI��Ϊ����call����
    \sa LVOS_SetThreadName
*/
/*lint -sem(LVOS_CreateThread, custodial(2)) */
OSP_S32 LVOS_CreateThread(PLVOSTHREAD_START_ROUTINE v_pfnStartRoutine, void *v_pArg, OSP_ULONG *v_pulThreadId);

/** \brief �����߳��������߳��Ƶ���ִ̨��(�ں�̬��daemonize������װ)
    \param[in] ... ��printfһ���ĸ�ʽ���ַ����Ͳ���
    \note  �ú�ֻ��Linux�ں�̬���ã��û�̬��WIN32�¶���Ϊ�ա�ͬ���ӿڣ����ܻᵼ�µ���������
    \note  �ں�̬ʵ������:
    \code  
    #define LVOS_SetThreadName(...) \
    do                          \
    {                           \
        daemonize(__VA_ARGS__); \
    }while(0)
    \endcode
    \note ʹ�þ���:
    \code
    LVOS_SetThreadName("function1");
    LVOS_SetThreadName("func_%s", "name1");
    \endcode
    \sa LVOS_CreateThread
*/
#define LVOS_SetThreadName(...) 

#if defined(__KERNEL__) && !defined(_PCLINT_)
#undef LVOS_SetThreadName
#define LVOS_SetThreadName(...) \
do                          \
{                           \
    daemonize(__VA_ARGS__); \
}while(0)

#endif


/** \brief �����߳����ȼ�
    \param[in] v_uiThrdPri �߳����ȼ�:�Ϸ�ֵ��ο�������\ref LVOS_THRD_PRI_E
*/
void LVOS_SetCurThrdPriority(dpax_thrd_prio_e v_uiThrdPri);

/** \brief ��õ�ǰ���̵�PID
    \retval ��ǰ���̵�PID
    \note windows�µĻ�ý���id 
*/
OSP_S32 LVOS_GetPid(void);

/** \brief ��õ�ǰ�߳�ID
      \retval ��ǰ�߳�ID
      \note windows�µĻ���߳�id 
*/
dpax_pthread_t LVOS_GetTid(void);

#endif
/** @} */

