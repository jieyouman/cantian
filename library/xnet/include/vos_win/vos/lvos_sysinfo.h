/******************************************************************************

                  ��Ȩ���� (C) 2008-2008 ��Ϊ�������˿Ƽ����޹�˾

 ******************************************************************************
  �� �� ��   : lvos_lib.h
  �� �� ��   : ����
  
  ��������   : 2008��8��19��
  ����޸�   :
  ��������   : ϵͳ������Ϣ
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2008��8��19��
    
    �޸�����   : �����ļ�

******************************************************************************/
/** \addtogroup VOS_SYSINFO  ϵͳ������Ϣ
  @{
*/

#ifndef _VOS_SYSINFO_H_
#define _VOS_SYSINFO_H_


/** \brief ��ǰϵͳ��CPU������
    \note  ֧��windows��linux�û�̬��linux�ں�̬
    \note  ͬ���ӿڣ��ú������ᵼ�µ��ý���˯��Ƭ��(500ms)���Լ���CPU������
    \retval OSP_S32         ��ȡ�ɹ������ص�ǰϵͳ��CPU�����ʰٷֱ�
    \retval RETURN_ERROR    ��ȡʧ��
*/
OSP_S32 LVOS_GetCpuUsage(void);

/** \brief ��ǰϵͳ���ڴ�������
    \note  ֧��windows��linux�û�̬��linux�ں�̬
    \note  ͬ���ӿڣ����ܵ��µ���������
    \retval OSP_S32         ��ȡ�ɹ������ص�ǰϵͳ���ڴ������ʰٷֱ�
    \retval RETURN_ERROR    ��ȡʧ��
*/
OSP_S32 LVOS_GetMemUsage(void);

/** \brief ��ȡ��ǰϵͳCPU����
    \return ����CPU����
    \note   Linux�ں�̬��Windows����
*/
OSP_S32 LVOS_GetCpuNumber(void);

OSP_S32 LVOS_SysInfoInit(void);


#define CPU_MIN_NUM_ALLOW_BIND0 8
#define LVOS_IS_CPU_ALLOW_BIND_CPU0  (LVOS_GetCpuNumber() > CPU_MIN_NUM_ALLOW_BIND0)


#endif

/** @} */
