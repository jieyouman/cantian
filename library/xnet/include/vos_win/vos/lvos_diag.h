/******************************************************************************
     ��Ȩ���� (C) 2010 - 2010  ��Ϊ�������˿Ƽ����޹�˾
*******************************************************************************
* �� �� ��: ����
* ��������: 2010��6��21��
* ��������: ����������ͷ�ļ�
* ��    ע: 
* �޸ļ�¼: 
*         1)ʱ��    : 
*          �޸���  : 
*          �޸�����: 
******************************************************************************/
/**
    \file  lvos_diag.h
    \brief ���������й���
*/

/** \addtogroup VOS_DIAG ����������(new)
    �µĵ��������л��ƣ����MML, �淶�����ʽ���ṩ����ʽ����(ȷ��)���ܡ�

    @{
    \example diagnose_example.c ����������ʹ������
*/
#ifndef __LVOS_DIAGNOSE_H__
#define __LVOS_DIAGNOSE_H__

#define DBG_RET_UNKNOWN_ARG   1

#define DBG_MAX_COMMAND_LEN   20
#define DBG_MAX_CMD_DESC_LEN  64

#define DBG_MAX_ERR_MSG_LEN   80

typedef void (*FN_DBG_CMD_PROC)(OSP_S32 v_iArgc, OSP_CHAR *v_szArgv[]);
typedef void (*FN_DBG_CMD_HELP_PROC)(OSP_CHAR *v_szCommand, OSP_S32 iShowDetail);

/** \brief ��������ע��ṹ */
typedef struct
{
    OSP_CHAR szCommand[DBG_MAX_COMMAND_LEN];              /**< ������, ����[1,15] */
    OSP_CHAR szDescription[DBG_MAX_CMD_DESC_LEN];         /**< ����ļ�Ҫ���� */
    FN_DBG_CMD_PROC fnCmdDo;             /**< ����ִ�к���,  v_szArgv[0] �������� */
    FN_DBG_CMD_HELP_PROC fnPrintCmdHelp; /**< �����ӡ�����ĺ��� */
} DBG_CMD_S;

/** \brief ���������������ʱʹ�õĽṹ */
typedef struct
{
    OSP_CHAR *szOptArg; /**< ��ѡ�������������ʱ������ָ��������� */
    OSP_S32  iOptIndex; /**< ��ǰ�����argc���� */
    OSP_CHAR chOpt;     /**< ��������Чѡ���ʱ���ֵ������Ч��ѡ���ַ� */
    OSP_CHAR szErrMsg[DBG_MAX_ERR_MSG_LEN]; /**< ����ʱ����������Ϣ */
} DBG_OPT_S;

/** 
    \brief ���������ӡ����ӿ�, ��������������ʹ��
    \param[in] v_pchFormat �������ͬ��׼�⺯��printf
    \param[in] ...         �������ͬ��׼�⺯��printf
    \note �ú���ֻ���ڵ���ģ�����fnCmdDo���߳������ĵ��ã������������̵߳���
    \note �ú���������������������Χ�е���, ��Ҫ�ڼ����е�����ʹ��\ref DBG_PrintBuf
    \note �ú�����DBG_Log��һ���������Զ��ں���ӻ���
*/
/*lint -printf(1,DBG_Print)*/
void DBG_Print(const OSP_CHAR *v_pchFormat, ...);

/** 
    \brief ���������ӡ����ӿڣ��������ʱ����������������������ʹ��
    \param[in] v_pchFormat �������ͬ��׼�⺯��printf
    \param[in] ...         �������ͬ��׼�⺯��printf
    \note �ú���ֻ���ڵ���ģ�����fnCmdDo���߳������ĵ��ã������������̵߳���
    \note ���ڻ�����������(<2K)�������������ͻᶪʧ����Ҫʹ����ע��
    \note ����\ref DBG_Print���ߴ��������ػ��Զ����������е����ݴ��ؿͻ���
*/
/*lint -printf(1,DBG_PrintBuf)*/
void DBG_PrintBuf(const OSP_CHAR *v_pchFormat, ...);

/** 
    \brief ���������ӡ����ӿ�, ��ָ���Ļ�����������ͻ���
    \param[in] v_pchBuf ��������ַ
    \param[in] v_uiSize ����������
    \note �ú���ֻ���ڵ���ģ�����fnCmdDo���߳������ĵ��ã������������̵߳���
    \note �ú���������������������Χ�е���
*/
void DBG_SendBuf(const OSP_CHAR *v_pchBuf, OSP_U32 v_uiSize);

/** 
    \brief ���������Ϣ�������Ҫ�÷�
    \param[in] v_pchFormat �������ͬ��׼�⺯��printf, pchFormatΪNULLʱ�������Ҫ�÷���Ϣ
    \param[in] ...         �������ͬ��׼�⺯��printf
    \note �ú���ֻ���ڵ���ģ�����fnCmdDo���߳������ĵ��ã������������̵߳���
*/
void DBG_ShowUsageAndErrMsg(const OSP_CHAR *v_pchFormat, ...);

/** \brief  ��ȡ����ʽ����
    \param[in]  v_szPrompt      ����ʽ�������ʾ��
    \param[out] v_szInput       �����ȡ���Ľ���ʽ�����ַ���
    \param[in]  v_uiMaxInputLen ��ȡ����ʽ����Ļ���������, Ŀǰ֧�ֵ���󳤶�Ϊ63��Ч�ַ�(������'\\0')
    \retval     RETURN_OK     ��ȷ��ȡ���û�����
    \retval     RETURN_ERROR  û�л�ȡ������(����ͻ����˳���)
    \note �ú���ֻ���ڵ���ģ�����fnCmdDo���߳������ĵ��ã������������̵߳���
    \note �ú�����һֱ����ֱ���ͻ����˳��������û�����Ϊֹ
*/
OSP_S32 DBG_GetInput(OSP_CHAR *v_szPrompt, OSP_CHAR *v_szInput, OSP_U32 v_uiMaxInputLen);

/** 
    \brief ����ע��ӿ�
    \param[in]  v_pstCmd    ע��������������ο�\ref DBG_CMD_S
    \note �ú����ڲ�û�������Ᵽ�����뾡����init�����е��ã���֤�Ǵ��е��õ�
*/
OSP_S32 DBG_RegCmd(DBG_CMD_S *v_pstCmd);

OSP_S32 DBG_RegCmdToCLI(DBG_CMD_S *v_pstCmd);


/** 
    \brief ע������ӿ�
    \param[in]  v_szCommand  ע��������
*/
void DBG_UnRegCmd(OSP_CHAR *v_szCommand);

void DBG_UnRegCmdToCLI(OSP_CHAR *v_szCommand);



/** 
    \brief ���������ӿ�
    \param[in]  v_iArgc         �������fnCmdDoʱ�Ĳ���
    \param[in]  v_szArgv        �������fnCmdDoʱ�Ĳ���
    \param[in]  v_szOptString   �Ϸ���ѡ���б����ѡ����Ҫ�������ں����':', ��: "a:bi:dl"����ʾ�Ϸ���ѡ����abidl������a��i��Ҫ���ӵĲ���ֵ
    \param[out] v_pstOpt        �����ǰ�����ĸ������ݣ��ο�\ref DBG_OPT_S
    \retval  -1     ѡ������
    \retval  '?'    ��ǰ��ѡ���ַ����ٺϷ�ѡ���б���
    \retval  DBG_RET_UNKNOWN_ARG      ���ַ�ѡ���ַ���
    \retval  ����   ���ص�ǰ��ѡ���ַ�
    \attention �ú���ֻ���ڵ���ģ�����fnCmdDo���߳������ĵ��ã������������̵߳���
*/
OSP_S32 DBG_GetOpt(OSP_S32 v_iArgc, OSP_CHAR *v_szArgv[], const OSP_CHAR *v_szOptString, DBG_OPT_S *v_pstOpt);

/** \brief ���ò�������ĳ������
    \param[out] v_puiOptBits ���ڱ������λ��ʶ�ı���
    \param[in]  iOpt  ����ֻ����Сд��ĸ
*/
void DBG_SetOpt(OSP_U32 *v_puiOptBits, OSP_S32 iOpt);

/** \brief ���Բ����Ƿ����ĳ������
    \param[in] uiOptBits ���ڱ������λ��ʶ�ı���
    \param[in] iOpt ����ֻ����Сд��ĸ
    \return    ����������0, ���򷵻ط�0(ע��: ��0����1)
*/
OSP_S32 DBG_TestOpt(OSP_U32 uiOptBits, OSP_S32 iOpt);

/** \brief ��ȡU64�޷�������
    \param[in]  pszParam    �����ַ���
    \param[out] pullData    ����ת���Ժ��ֵ
    \retval RETURN_OK       ת���ɹ�
    \retval RETURN_ERROR    ת��ʧ��
*/
OSP_S32 DBG_GetParamU64(const OSP_CHAR *pszParam, OSP_U64 *pullData);

/** \brief ��ȡU32�޷�������
    \param[in]  pszParam    �����ַ���
    \param[out] pullData    ����ת���Ժ��ֵ
    \retval RETURN_OK       ת���ɹ�
    \retval RETURN_ERROR    ת��ʧ��
*/
OSP_S32 DBG_GetParamU32(const OSP_CHAR *pszParam, OSP_U32 *puiData);

/** \brief ��ȡָ�����
    \param[in]  pszParam    �����ַ���
    \param[out] pullData    ����ת���Ժ��ֵ
    \retval RETURN_OK       ת���ɹ�
    \retval RETURN_ERROR    ת��ʧ��
*/
OSP_S32 DBG_GetParamPointer(const OSP_CHAR *pszParam, void **ppPointer);

/** \brief ��ӡ��ַ������
    \param[in] v_pvAddr    ��ӡ�ĵ�ַ
    \param[in] v_uiLen     ��ӡ�ĳ���
*/
void DBG_PrintMemContext(void *v_pvAddr, OSP_U32 v_uiLen);

#endif

/** @} */

