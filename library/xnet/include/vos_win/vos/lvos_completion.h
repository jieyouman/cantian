/******************************************************************************

                  ��Ȩ���� (C), 2008-2008, ��Ϊ�������˿Ƽ����޹�˾

 ******************************************************************************
  �� �� ��   : lvos_completion.h
  �� �� ��   : ����

  ��������   : 2009��5��19��
  ����޸�   :
  ��������   : ��ɱ�������ӿڣ�������windows�����linux�ں�̬
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2009��5��19��

    �޸�����   : �����ļ�

******************************************************************************/
/**
    \file  lvos_completion.h
    \brief ��ɱ�������ӿڣ�������windows�����linux�ں�̬����֧��linux�û�̬

    \date 2009��5��19��
*/

/** \addtogroup VOS_COMPLETION  ��ɱ���
    ��ɱ�������ӿڣ�������windows�����linux�ں�̬����֧��linux�û�̬\n
    ��ɱ��������������ź�����ʹ�ù������п��ܵ��µ��ý�����������ˣ����ڲ��������ĵ���\n
    ������(���жϵ�)����Ҫʹ����ɱ�����
    @{ 
*/

#ifndef __LVOS_COMPLETION_H__
#define __LVOS_COMPLETION_H__
#if 0
#if defined(WIN32) || defined(_PCLINT_)

/** \brief ��ɱ����ṹ�� */
typedef struct
{
    LVOS_SEMAPHORE_S stDone;
} LVOS_COMPLETION_S;

/**
    \brief ��ʼ����ɱ���
    \param[in] v_pstCompletion    ��ɱ���ָ��
    \retval    void
*/
void LVOS_InitCompletion(LVOS_COMPLETION_S *v_pstCompletion);

/**
    \brief ������ɱ���
    \note  ��Ҫ������ɱ�������Ϊ��Ҫ����windows�µ��ź������
    \param[in] v_pstCompletion    ��ɱ���ָ��
    \retval    ��
*/
void LVOS_DestroyCompletion(LVOS_COMPLETION_S *v_pstCompletion);

/**
    \brief �ȴ���ȡ��ɱ���
    \note  ����������ʹ�ù������п��ܵ��µ��ý�������
    \param[in] v_pstCompletion    ��ɱ���ָ��
    \retval    ��
*/
void LVOS_WaitForCompletion(LVOS_COMPLETION_S *v_pstCompletion);

/**
    \brief ������ɱ���
    \param[in] v_pstCompletion    ��ɱ���ָ��
    \retval    ��
*/
void LVOS_Complete(LVOS_COMPLETION_S *v_pstCompletion);

/**
    \brief ������ɱ������˳��߳�
    \param[in] v_pstCompletion    ��ɱ���ָ��    
    \param[in] lExitCode          �˳���
    \retval    ��
*/
void LVOS_CompleteAndExit(LVOS_COMPLETION_S *v_pstCompletion, OSP_LONG lExitCode);

#elif defined (__KERNEL__)
#include <linux/completion.h>

/* linux�ں�̬�µ���ɱ����ṹ��  */
typedef struct completion LVOS_COMPLETION_S;
#define LVOS_InitCompletion(cmp)             init_completion(cmp)
#define LVOS_WaitForCompletion(cmp)          wait_for_completion(cmp)
#define LVOS_Complete(cmp)                   complete(cmp)
#define LVOS_CompleteAndExit(cmp, exitcode)  complete_and_exit(cmp, exitcode)
#define LVOS_DestroyCompletion(cmp)    /* �ú�������������windows��ģ����ɱ����õľ���ģ�linux��Ϊ�� */

#endif
#endif

#endif

/** @} */

