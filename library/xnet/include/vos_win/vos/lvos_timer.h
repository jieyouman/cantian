/******************************************************************************

                  ��Ȩ���� (C), 2008-2008, ��Ϊ�������˿Ƽ����޹�˾

 ******************************************************************************
  �� �� ��   : lvos_timer.h
  �� �� ��   : ����

  ��������   : 2009��5��24��
  ����޸�   :
  ��������   : ��ʱ��������ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2009��5��24��

    �޸�����   : �����ļ�

******************************************************************************/
/** \addtogroup LIB    Hima������
    @{ 
*/
/**
    \file  lvos_timer.h
    \brief ϵͳ��ʱ�����ܣ�����linux�ں�̬�µĶ�ʱ���ӿ�
    \note  ֧��windows/linux_kernel
    \date 2009��5��24��
*/

#ifndef __LVOS_TIMER_H__
#define __LVOS_TIMER_H__

#define LVOS_MAX_TIMER_TIMEOUT  ((long)(~0UL>>1))

#if defined WIN32 || defined __KERNEL__
/********************** ����windowsƽ̨��ʹ�õ����ݽṹ ����������begin ************************/
#ifdef WIN32
/** \brief ��ȡϵͳ����������32λ��������ֻ������windows��linux�ں�̬�� */
#define jiffies GetTickCount()
#define HZ 1000     /**< windows�¶���HZΪ1000����ΪGetTickCount()���غ���ƵĿ���ʱ�� */
#define LVOS_TIMER_STATUS_EMPTY 1      /* ����Win32�¶�ʱ��״̬ */
#define LVOS_TIMER_STATUS_WAITING 2    /* ����Win32�¶�ʱ��״̬ */
#define LVOS_TIMER_THREAD_STATUS_RUNNING 1 /* �̱߳�־λ:1-����,����-�˳� */

static inline OSP_S32 time_after(OSP_ULONG v_ulA,OSP_ULONG v_ulB)
{
    OSP_LONG vlTemp = (OSP_LONG)(v_ulB - v_ulA);
    return (vlTemp < 0);
}

static inline OSP_S32 time_after_eq(OSP_ULONG v_ulA,OSP_ULONG v_ulB)
{
    OSP_LONG vlTemp = (OSP_LONG)(v_ulB - v_ulA);
    return (vlTemp <= 0);
}
#define LVOS_TIME_AFTER(a,b) time_after(a,b)
#define LVOS_TIME_AFTER_EQ(a,b) time_after_eq(a,b)
#define LVOS_TIME_BEFORE(a,b) time_after(b,a)

#ifdef ESTOR_X64
typedef OSP_VOID (*LVOS_TIMER_FUNC_PFN)(OSP_U64 v_ulData);    /**��64λ�������Ϊ8�ֽ�ָ�룬����޸Ĳ������� */
#else
typedef OSP_VOID (*LVOS_TIMER_FUNC_PFN)(OSP_ULONG v_ulData);    /**< ��ʱ������������ */
#endif
#define TIMER_NAME_LEN (50)

typedef struct tagLVOS_TIMER_LIST_S
{
    int expires;
    struct list_head stTimerList;
#ifdef ESTOR_X64
	unsigned long long data;	/*��64λ�������Ϊ8�ֽ�ָ�룬����޸Ĳ�������*/
#else
    unsigned long data;
#endif
    int iTimeMicroSec;
    char szName[TIMER_NAME_LEN];
#ifdef ESTOR_X64
	void  (*function)(unsigned long long);	/*��64λ�������Ϊ8�ֽ�ָ�룬����޸Ĳ�������*/
#else
    void  (*function)(unsigned long);
#endif
} LVOS_TIMER_LIST_S;

int TIMER_InitTimer(LVOS_TIMER_LIST_S *my_timer);
int TIMER_AddTimer(LVOS_TIMER_LIST_S *v_pstTimer);
int TIMER_ModTimer(LVOS_TIMER_LIST_S *my_timer,unsigned long new_delay);
int TIMER_DelTimer(LVOS_TIMER_LIST_S *my_timer);
int TIMER_Pending(LVOS_TIMER_LIST_S *my_timer);

#ifdef ESTOR_X64
/*��64λ�������v_ulDataΪ8�ֽ�ָ�룬����޸Ĳ�������*/
OSP_S32 TIMER_NEX_InitTimer(LVOS_TIMER_LIST_S *v_pstTimer, OSP_ULONG v_ulExpires, 
                           OSP_U64 v_ulData, 
                           LVOS_TIMER_FUNC_PFN v_pfnTimerHandler);
#else
OSP_S32 TIMER_NEX_InitTimer(LVOS_TIMER_LIST_S *v_pstTimer, OSP_ULONG v_ulExpires, 
                           OSP_ULONG v_ulData, 
                           LVOS_TIMER_FUNC_PFN v_pfnTimerHandler);
#endif

/* VOS�ṩ�Ķ��⹫���ӿ�begin */
#define LVOS_InitTimer                      TIMER_NEX_InitTimer
#define LVOS_AddTimer(v_timer)              TIMER_AddTimer(v_timer)
#define LVOS_ModTimer(v_timer, v_delay)     TIMER_ModTimer(v_timer, v_delay)
#define LVOS_DelTimer(v_timer)              TIMER_DelTimer(v_timer)
#define LVOS_DelTimerSync(v_timer)          TIMER_DelTimer(v_timer)
#define LVOS_IsTimerActivated(v_timer)		TIMER_Pending(v_timer)
/* VOS�ṩ�Ķ��⹫���ӿ�end */

/* Ϊ����ISCSIģ�鶨��ķ���ӿڣ���Щ�ӿ�ֻ�ڷ���ƽ̨��ʹ��begin */
#define LVOS_mod_timer(v_timer, v_delay)    TIMER_ModTimer(v_timer, v_delay)
#define LVOS_del_timer_sync(v_timer)        TIMER_DelTimer(v_timer)
#define LVOS_timer_pending(v_timer)         TIMER_Pending(v_timer)

#define init_timer      TIMER_InitTimer
#define add_timer       ISCSI_AddTimer
#define mod_timer       LVOS_mod_timer
#define del_timer       LVOS_DelTimer
#define del_timer_sync  LVOS_del_timer_sync
#define timer_pending   LVOS_timer_pending
/* Ϊ����ISCSIģ�鶨��ķ���ӿڣ���Щ�ӿ�ֻ�ڷ���ƽ̨��ʹ��end */
/********************** ����windowsƽ̨��ʹ�õ����ݽṹ ����������end ************************/

/********************** ����linuxƽ̨���ں�̬ʹ�õ����ݽṹ ����������begin ************************/
#else
#include <linux/timer.h>

typedef OSP_VOID (*LVOS_TIMER_FUNC_PFN)(OSP_ULONG v_ulData);
typedef struct tagLVOS_TIMER_LIST_S
{
    struct timer_list stTimer;
    OSP_ULONG ulExpireTime;
    OSP_CHAR * pFunc;
    OSP_ULONG uiLine;
}LVOS_TIMER_LIST_S;

/********************** ����linuxƽ̨���ں�̬ʹ�õ����ݽṹ end ************************/
/********************** ����linuxƽ̨���ں�̬ʹ�õĺ�begin ************************/
#define LVOS_TIME_AFTER(a,b) time_after(a,b)
#define LVOS_TIME_AFTER_EQ(a,b) time_after_eq(a,b)
#define LVOS_TIME_BEFORE(a,b) time_before(a,b)

/********************** ����linuxƽ̨���ں�̬ʹ�õĺ�end ************************/

/*****************************************************************************
 �� �� ��  : LVOS_InitTimer
 ��������  : ��ʼ����ʱ��
 �������  : LVOS_TIMER_LIST_S *v_pstTimer
             OSP_U64 v_ullExpires
             OSP_ULONG v_ulData
             LVOS_TIMER_FUNC_PFN
 �������  : ��
 �� �� ֵ  : OSP_S32
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2009��5��25��

    �޸�����   : �����ɺ���

*****************************************************************************/
/**
    \brief ��ʼ����ʱ��
    \note ֧��windows/linux_kernel    
    \note ��������/�޸�/ɾ����ʱ��ʱ������Ҫʹ�ô˶�ʱ���ṹ�壬�����ò�Ҫʹ�þֲ�������ʹ������Ҫ��֤��һ��
    \note ��ͬ��linux_kernel�µĳ�ʱʱ��Ϊ����ʱ�䣬����ĳ�ʱʱ��Ϊ���ʱ�䣬���Ӷ�ʱ�������v_uiExpires����󣬶�ʱ��������������
    \param[in] v_pstTimer           ��ʱ���ṹ��
    \param[in] v_ulExpires          �Ժ���Ƶĳ�ʱʱ��
    \param[in] v_ulData             ��ʱ�����������������
    \param[in] v_pfnTimerHandler    ��ʱ��������
    \retval RETURN_OK               ��ʼ����ʱ���ɹ�
    \retval RETURN_ERROR            ��ʼ����ʱ��ʧ��
*/
OSP_S32 LVOS_DbgInitTimer(LVOS_TIMER_LIST_S *v_pstTimer, OSP_ULONG v_ulExpires, 
                       OSP_ULONG v_ulData, 
                       LVOS_TIMER_FUNC_PFN v_pfnTimerHandler, const OSP_CHAR * v_pFunc, OSP_U32 v_uiLine);

#define LVOS_InitTimer( v_pstTimer, v_ulExpires, v_ulData, v_pfnTimerHandler)\
            LVOS_DbgInitTimer(v_pstTimer, v_ulExpires, v_ulData, v_pfnTimerHandler, __FUNCTION__, __LINE__)


/*****************************************************************************
 �� �� ��  : LVOS_AddTimer
 ��������  : ���ʱ�����ö�ʱ����ֻ����һ�Σ���ʱ���Զ�����
 �������  : LVOS_TIMER_LIST_S *v_pstTimer
 �������  : ��
 �� �� ֵ  : OSP_VOID
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2009��5��25��

    �޸�����   : �����ɺ���

*****************************************************************************/
/**
    \brief ���ʱ�����ö�ʱ����ֻ����һ�Σ���ʱ���Զ�����
    \note ֧��windows/linux_kernel
    \param[in] v_pstTimer   ��ʱ���ṹ��
    \retval RETURN_OK       ���ʱ���ɹ�
    \retval RETURN_ERROR    ���ʱ��ʧ��
*/
OSP_S32 LVOS_DbgAddTimer( LVOS_TIMER_LIST_S *v_pstTimer, 
                                                        const OSP_CHAR * v_pFunc, OSP_U32 v_uiLine);
#define LVOS_AddTimer(v_pstTimer)\
    LVOS_DbgAddTimer(v_pstTimer,__FUNCTION__,__LINE__)

/*****************************************************************************
 �� �� ��  : LVOS_ModTimer
 ��������  : �޸Ķ�ʱ����ʱʱ�䣬�����ʱ��ʱ����û�м�������Ѿ����٣��˽ӿڽ�����
             ���ʱ��������������һ����ʱ��������
 �������  : LVOS_TIMER_LIST_S *v_pstTimer
             OSP_ULONG v_ulExpires
 �������  : ��
 �� �� ֵ  : OSP_S32
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2009��5��25��

    �޸�����   : �����ɺ���

*****************************************************************************/
/**
    \brief �޸Ķ�ʱ����ʱʱ��
    \note ֧��windows/linux_kernel
    \note �����ʱ��ʱ����û�м�������Ѿ����٣��˽ӿڽ����¼��ʱ��������������һ����ʱ��������
    \param[in] v_pstTimer    ��ʱ���ṹ��
    \param[in] v_ulExpires   �µĶ�ʱ����ʱʱ��
    \retval RETURN_OK        �޸Ķ�ʱ���ɹ�
    \retval RETURN_ERROR     �޸Ķ�ʱ��ʧ��
*/
OSP_S32 LVOS_ModTimer( LVOS_TIMER_LIST_S *v_pstTimer, OSP_ULONG v_ulExpires );

/**
    \brief ɾ����ʱ��
    \note ֧��windows/linux_kernel
    \param[in] v_pstTimer    ��ʱ���ṹ��
    \retval RETURN_OK        ɾ����ʱ���ɹ�
    \retval RETURN_ERROR     ɾ����ʱ��ʧ��
*/
OSP_S32 LVOS_DelTimer( LVOS_TIMER_LIST_S *v_pstTimer );

/*****************************************************************************
 �� �� ��  : LVOS_DelTimer
 ��������  : ͬ�� ɾ����ʱ��
 �������  : LVOS_TIMER_LIST_S *v_pstTimer
 �������  : ��
 �� �� ֵ  : OSP_S32
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2009��11��17��

    �޸�����   : �����ɺ���

*****************************************************************************/
/**
    \brief ͬ�� ɾ����ʱ��
    \note �ڶദ������ʹ��
    \param[in] v_pstTimer    ��ʱ���ṹ��
    \retval RETURN_OK        ɾ����ʱ���ɹ�
    \retval RETURN_ERROR     ɾ����ʱ��ʧ��
*/
OSP_S32 LVOS_DelTimerSync( LVOS_TIMER_LIST_S *v_pstTimer );

/*****************************************************************************
 �� �� ��  : LVOS_IsTimerActivated
 ��������  :  �ж϶�ʱ���Ƿ��Ѿ�����
 �������  : LVOS_TIMER_LIST_S *v_pstTimer
 �������  : 
 �� �� ֵ  : OSP_BOOL  TRUE �Ѽ���
                                        FALSE δ����
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2009��12��2��

    �޸�����   : �����ɺ���
*****************************************************************************/
/**
    \brief �ж϶�ʱ���Ƿ��Ѿ�����
    \note 
    \param[in] v_pstTimer    ��ʱ���ṹ��   
    \retval TRUE      �Ѽ���
    \retval FALSE     δ����
*/
OSP_BOOL LVOS_IsTimerActivated( LVOS_TIMER_LIST_S *v_pstTimer );

#endif
/********************** ����linuxƽ̨���ں�̬ʹ�õ����ݽṹ ����������end ************************/

/*********************************** ��ƽ̨��ʹ�õĺ��������� begin ************************************/
/*****************************************************************************
 �� �� ��  : LVOS_DestroyTimer
 ��������  :  ���ٶ�ʱ��
 �������  : LVOS_TIMER_LIST_S *v_pstTimer
 �������  : ��
 �� �� ֵ  : OSP_VOID
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2009��12��2��

    �޸�����   : �����ɺ���

*****************************************************************************/
/**
    \brief ���ٶ�ʱ��
    \note ��alps��ֲ���� 
    \param[in] v_pstTimer    ��ʱ���ṹ��   
*/
static inline OSP_VOID LVOS_DestroyTimer( LVOS_TIMER_LIST_S *v_pstTimer )
{
    if (NULL != v_pstTimer)
    {
        (OSP_VOID)LVOS_DelTimerSync(v_pstTimer);
    }
    return;
}

#endif

/*********************************** ��ƽ̨��ʹ�õĺ��������� end ************************************/

#endif  /* __LVOS_TIMER_LIST_H__ */

