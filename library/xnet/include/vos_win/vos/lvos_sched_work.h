#ifndef _LVOS_SCHED_WORK_H
#define _LVOS_SCHED_WORK_H

/** \brief �������нṹ�壬��װlinux�µ�struct work_struct����ͬ��linuxԭ���壬��Ϊ��Щ�ֶ�û�õ� */
typedef struct tagLVOS_SCHED_WORK_S
{
    OSP_U32 uiPid;
    struct list_head stNode;
    OSP_VOID *pData;                /**< �û��Լ���������� */
    void (*pfnWorkHandler)(void *); /**< �������д������������������������нṹ��ָ�� */
} LVOS_SCHED_WORK_S;

/** \brief �����������ʼ���� */
#define LVOS_INIT_WORK(work, func, pdata)       \
    do                                          \
    {                                           \
        (work)->uiPid = MY_PID;                 \
        INIT_LIST_NODE(&((work)->stNode));    \
        (work)->pData = pdata;                  \
        (work)->pfnWorkHandler = func;          \
    } while(0)

/** \brief �������е��Ⱥ���
    \param[in] v_pstWork    �������нṹ��
*/
/*lint -sem(LVOS_SchedWork, custodial(1)) */
void LVOS_SchedWork(LVOS_SCHED_WORK_S *v_pstWork);

/* ��ʼ����ģ�飬���� Linux�û�̬��Ҫʹ�ø�ģ���ʱ�򵥶���ʼ�� */
OSP_S32 LVOS_SchedWorkInit(void);

#endif

