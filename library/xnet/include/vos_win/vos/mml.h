/******************************************************************************

                  ��Ȩ���� (C), 2008-2010, ��Ϊ�������˿Ƽ����޹�˾

 ******************************************************************************
  �� �� ��   : mml.h
  �� �� ��   : ����

  ��������   : 2008��12��19��
  ����޸�   :
  ��������   : mml�Ķ���ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2008��12��19��

    �޸�����   : �����ļ�

******************************************************************************/
/**
    \file  mml.h
    \brief ���������ж���ӿ�����
    \date 2008-12-19
*/

/** \addtogroup MML  ����������MML
    ע��: MML���ܵ���0�Ժ��ȡ�������Ҳ�Ҫ��ʹ��
    @{ 
*/

#ifndef __MML_H__
#define __MML_H__

/** \brief ע���������󳤶�(����������) */
#define MML_MAX_CMD_LEN 7       /* ע���������󳤶�(����������) */

/** \brief ע������Ľṹ�� */
typedef struct stDebugMML
{
    OSP_S32     iPid;/**< ģ���PID */

    /* MML�������û�����ĵ�һ�����ʣ������achNameƥ�䣬����ñ�ģ���DoMML���� */
    OSP_CHAR    achName[MML_MAX_CMD_LEN + 1];   /**< ��ģ�������ʡ����8 ���ַ��������пո� */
    
    OSP_S32     iNameNChar;                     /**< ����� ���ַ����� */

    OSP_CHAR    *pchModuleName;                 /**< ��ģ������� */

    /* ����MML����ĺ�����������һ���ַ����������û�������ַ���
       ��ͷ��iNameNChar + 1���ַ��Ѿ���������
       �����û�����trgt xx������ô˺���ʱ��xx���������
       ������������棬���Ҫ��ӡ����������MML_Print()
     */
    void (*DoMML)(OSP_CHAR * v_pchInStr);   /**< ����MML����ĺ��� */
} MML_REG_S;


/** \brief ע��MML�����д���ӿ�
    \param[in] v_arg  ע��ṹָ��
    \return ��
*/
#ifdef WIN32
__declspec(deprecated("This function will be deleted for future, please use 'DBG_RegCmd' instead."))
#endif
void MML_Register(MML_REG_S *v_arg);

/** \brief ��ע��MML�����д���ӿ�
    \param[in] v_uiPid  ģ��PID
    \return ��
*/
void MML_UnRegister(OSP_U32 v_uiPid);

/** \brief MML�ĵ�����Ϣ����ӿ�
    \param[in] pcfmt  ������ʽ��printfһ��
    \param[in] ...  ������ʽ��printfһ��
    \return ��
*/
void MML_Print(OSP_CHAR * pcfmt, ...);

#endif  /* __MML_H__ */
/** @} */

