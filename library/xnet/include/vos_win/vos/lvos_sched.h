/******************************************************************************

                  ��Ȩ���� (C), 2008-2008, ��Ϊ�������˿Ƽ����޹�˾

 ******************************************************************************
  �� �� ��   : lvos_sched.h
  �� �� ��   : ����

  ��������   : 2009��5��11��
  ����޸�   :
  ��������   : �̵߳��ȵ�ͨ�ù��ܽӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2009��5��11��

    �޸�����   : �����ļ�

******************************************************************************/

/**
    \file  lvos_sched.h
    \brief �̵߳��ȵ�ͨ�ù��ܽӿ�ͷ�ļ�
    \note  �жϴ������Ȳ�������̵��ȵ��������в�Ҫʹ�ñ��ļ��еĺ���

    \date 2009��5��11��
*/

/** \addtogroup VOS_SCHED ��ʱ������ӿ�
    @{ 
*/

#ifndef __LVOS_SCHED_H__
#define __LVOS_SCHED_H__

/** \brief �����ӳٵĺ�����
    \param[in] x  �ӳ�����
    \return ������
*/
#define DELAY_SEC(x)    ((x) * 100)

/** \brief �����ӳ�����
    \param[in] x  �ӳٶ���ʮ����
    \return ������
*/
#define DELAY_10MS(x)   ((x))

/** \brief      ��΢��Ϊ��λ����ʱ����
    \param[in]  us ��usΪ��λ��˯��ʱ��
    \retval     void
*/
void LVOS_usleep(unsigned int us);

/** \brief      ����˯�ߺ�������������ĵ�λΪ10ms
    \note       ֧��windows/linux_kernel/linux_user
    \param[in]  ten_ms ��10msΪ��λ��˯��ʱ��
    \retval     void
    \attention  lvos_sleep�ɱ��ź���ǰ����
*/
void LVOS_sleep(unsigned int ten_ms);

/** \brief      ����˯�ߺ�������������ĵ�λΪ1ms
    \note       ֧��windows/linux_kernel/linux_user
    \param[in]  ms ��msΪ��λ��˯��ʱ��
    \retval     void
    \attention  lvos_sleep�ɱ��ź���ǰ����
*/
void LVOS_msleep(unsigned int ms);

/** \brief      ���̵��Ⱥ������������������������
    \note       ֧��windows����ƽ̨��linux�ں�̬
*/
void LVOS_Schedule(void);

/** \brief      ������������CPU
    \note       ֧��windows����ƽ̨��linux�ں�̬
*/
void LVOS_Yield(void);

/** \brief  �߳̿���sleep�ĵ��Թ��ܣ�����̲߳��������ߵ��øú�����ᱨ�����
    \note  ���Թ���
*/
#ifdef WIN32
void LVOS_MightSleep(void);
#elif defined(__KERNEL__)
#define LVOS_MightSleep might_sleep
#else
#define LVOS_MightSleep()
#endif

#ifdef WIN32

/** \brief �����߳����ж������ı�־
    \note  ���Թ���
*/
void LVOS_SetThreadInterruptFlag(OSP_S32 v_iFlag);

/** \brief �����߳���IOD�����ı�־
    \note  ���Թ���
*/
void LVOS_SetThreadIodFlag(OSP_S32 v_iFlag);

/** \brief spinlock��������g_iThreadInterruptFlag
    \note  ���Թ���
*/
void LVOS_IncThreadSpinCount(void);

/** \brief spinlock������һ
    \note  ���Թ���
*/
void LVOS_DecThreadSpinCount(void);

/** \brief ���Դ�ӡר��
    \note ���Թ���
*/
void LVOS_SetDebugPrintFlag(OSP_S32 v_iFlag);

#else
#define LVOS_SetThreadInterruptFlag(v_iFlag)
#define LVOS_SetThreadIodFlag(v_iFlag)
#define LVOS_IncThreadSpinCount()
#define LVOS_DecThreadSpinCount()
#define LVOS_SetDebugPrintFlag(v_iFlag)
#endif

#endif /* __LVOS_SHCED_H__ */

/** @} */

