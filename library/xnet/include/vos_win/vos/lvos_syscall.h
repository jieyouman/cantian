#ifndef _LVOS_SYSCALL_H
#define _LVOS_SYSCALL_H

#define LVOS_SYSCALL_GROUP_CUSTOMIZE   (1)  /* �����ģ�� */
#define LVOS_SYSCALL_GROUP_OM_DEPENDS  (2)
#define LVOS_SYSCALL_GROUP_UPGRADE     (3)
#define LVOS_SYSCALL_GROUP_AGENT       (4)  /* ISM��AGENT */
#define LVOS_SYSCALL_GROUP_AUTH        (5)  /* �û�����ģ�� */

/* ��ϵͳ��������Ϊֱ�ӵ��ã�
   ϵͳ���ô�������Ҫ�Լ�����copy_from_user/copy_to_user, 
   v_pvParamֱ��͸�����ص�����
   �����û�̬�����ҵ���Ƶ������Ҫ���������ݽ϶�ʱ����ʹ�ô˷�ʽ
*/
#define LVOS_SYSCALL_TYPE_DIRECT      0

/* ��ϵͳ��������Ϊ��ӵ��ã�
   v_pvParamΪ�ں˵�ַ��ϵͳ���û��ƴ����ں˵��û�̬�Ŀ���
   �˷�ʽ���һ���ڴ濽��, ����/������������������: LVOS_SYSCALL_MAX_IN_OUT_BUF_LEN
*/
#define LVOS_SYSCALL_TYPE_INDIRECT    1



#define LVOS_SYSCALL_CMD(group, id)   (((group) << 8) + (id))

#define LVOS_SYSCALL_MAX_IN_OUT_BUF_LEN   (510)
#define LVOS_MAX_GROUP_NUM                (32)

#define FILL_SYSCALL_PARAM(param, inBuf, inLen, outBuf, outLen) \
do { \
    (param).pvInBuf     = (inBuf);  \
    (param).uiInBufLen  = (inLen);  \
    (param).pvOutBuf    = (outBuf); \
    (param).uiOutBufLen = (outLen); \
    (param).uiRetBufLen = 0;        \
} while(0)

/* ����ϵͳ���õĲ��� */
typedef struct
{
    OSP_U32 uiInBufLen;   /* �������Ч���ݳ��� */
    OSP_U32 uiOutBufLen;  /* �����OutBuf���������� */
    OSP_U32 uiRetBufLen;  /* ���ص�OutBufʵ�����ݳ��� */
    void *pvInBuf;        /* ��ϵͳ���õ����뻺����ָ�� */
    void *pvOutBuf;       /* ��ϵͳ���õ����������ָ�� */
} LVOS_SYSCALL_PARAM_S;

/* ע��ϵͳ���õĲ��� */
typedef struct
{
    OSP_U32 uiCmd;
    OSP_U32 uiType;   /* LVOS_SYSCALL_TYPE_DIRECT or LVOS_SYSCALL_TYPE_INDIRECT */
    OSP_S32 (*pfnSysCall)(OSP_U32 uiCmd, LVOS_SYSCALL_PARAM_S *);
} LVOS_GROUP_SYSCALL_S;

/**
    \brief ����ע���ϵͳ���õĽӿ�
    \param[in] v_uiCmd  ˽��ϵͳ���õ�������
    \param[inout] v_pvParam ϵͳ���õĲ���������ΪNULL��ΪNULLʱ�����Լ�����
*/
OSP_S32 LVOS_SysCall(OSP_U32 v_uiCmd, LVOS_SYSCALL_PARAM_S *v_pvParam);

/** \brief ��VOSע��ϵͳ���ô�����
*/
OSP_S32 LVOS_RegSysCall(OSP_U32 v_uiGroupId, LVOS_GROUP_SYSCALL_S *v_pstSysCalls, OSP_U32 v_uiCount);

/** \brief ��ע��ϵͳ���ô�����
*/
void LVOS_UnRegSysCall(OSP_U32 v_uiGroupId);

#endif

