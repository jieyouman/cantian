/******************************************************************************
     ��Ȩ���� (C) 2010 - 2010  ��Ϊ�������˿Ƽ����޹�˾
*******************************************************************************
* �� �� ��: ����
* ��    ��: x00001559
* ��������: 2010��6��26��
* ����par ������
	 : TracePoint����ͷ�ļ�
* ��    ע: 
* �޸ļ�¼: 
*         1)ʱ��    : 
*          �޸���  : 
*          �޸�����: 
******************************************************************************/
/**
    \lvos_tracepoint.h
    \VOS_TRACEP TracePoint����
*/

/* VOS_TRACEP TracePoint(new)
    @{ 
    \example tracepoint_example.c
    TracePoint����ʹ������
*/

/** @defgroup VOS_TRACEP TracePoint */

#ifndef __LVOS_TRACEPOINT_H__
#define __LVOS_TRACEPOINT_H__

#include <stdlib.h>

#ifdef WIN32
#include "lvos_tracepoint.h"
#define LVOS_HVS_doTracePointPause		doTracePointPause
#define LVOS_HVS_getTracePoint			getTracePoint
#define LVOS_HVS_regTracePoint			regTracePoint
#define LVOS_HVS_unregTracePoint		unregTracePoint
#define LVOS_HVS_activeTracePoint		activeTracePoint
#define LVOS_HVS_deactiveTracePoint		deactiveTracePoint
#define LVOS_HVS_deactiveTracePointAll	deactiveTracePointAll

#ifndef DPAX_PANIC

#define DPAX_PANIC() \
do {\
    abort(); \
} while(0)
#endif

#endif

#define LVOS_MAX_HOOK_PER_TRACEP  16

#define LVOS_TRACEP_STAT_DELETED   0
#define LVOS_TRACEP_STAT_ACTIVE    1
#define LVOS_TRACEP_STAT_DEACTIVE  2

#define LVOS_TRACEP_PARAM_SIZE     32UL

/*HVS�¿��*/
typedef enum tagLVOS_TP_TYPE_E
{
	LVOS_TP_TYPE_CALLBACK = 0,	/*�ص�*/
	LVOS_TP_TYPE_RESET,	    /*��λ*/
	LVOS_TP_TYPE_PAUSE,         /*��ͣ*/
	LVOS_TP_TYPE_ABORT,
	LVOS_TP_TYPE_BUTT
}LVOS_TP_TYPE_E;

/** \brief ÿ��TracePoint���Զ�������� */
typedef struct
{
    OSP_CHAR achParamData[LVOS_TRACEP_PARAM_SIZE]; /**<  �Զ������������ */
} LVOS_TRACEP_PARAM_S;

#ifdef DOXYGEN
/** \brief ����һ������������TracePoint */
#define LVOS_TRACEP_DEF0(tracep_name)

/** \brief ����һ����������TracePoint 
    \param[in] tracep_name TracePoint������
    \param[in] ...  �ص��������Զ�������б���  :  OSP_S32 *, OSP_U64 *
    \note  ����ֻ���ǺϷ��ı������ƣ���Ҫ�����ţ�������õ�ʱ��Ҳ���ܼ�����
*/
#define LVOS_TRACEP_DEFN(tracep_name, ...)

/** \brief ���ò���������TracePoint�ص�����
    \note  ��Ҫ��ҵ������е��ò��Դ���ע���TracePoint
*/
#define LVOS_TRACEP_CALL0(tracep_name)

/** \brief ���ô�������TracePoint�ص�����
    \note     \note  ��Ҫ��ҵ������е��ò��Դ���ע���TracePoint
*/
#define LVOS_TRACEP_CALLN(tracep_name, ...)

/** \brief ���ò���������TracePoint�ص�����
    \note  ��Ҫ��ҵ������е��ò��Դ���ע���TracePoint
*/
#define LVOS_TRACEPHOOK_CALL0(tracep_name)

/** \brief ���ô�������TracePoint�ص�����
    \note     \note  ��Ҫ��ҵ������е��ò��Դ���ע���TracePoint
*/
#define LVOS_TRACEPHOOK_CALLN(tracep_name, ...)

/** \brief ע��һ��TracePoint 
    \param[in] tracep_name TracePoint�����ƣ��Ͷ���ʱһ�£���Ҫ������
    \param[in] desc ��Ҫ������Ϣ
    \param[in] flag ��ʼ�Ǽ����ȥ����, FALSE��ʾȥ���������ʾ����
    \note  ҵ������е��õ�TracePoint������ҵ�������ע�ᣬ���Դ�����Ե���ҵ�����ע���TracePoint���Ƿ�������Ҫ����ʹ��
*/
#define LVOS_TRACEP_REG_POINT(tracep_name, desc, flag)

/** \brief ע��һ��TracePoint */
#define LVOS_TRACEP_UNREG_POINT(tracep_name)

/** \brief ����/ȥ����һ��TracePoint 
    \param[in] tracep_name TracePoint����
    \param[in] flag FALSE��ʾȥ�������ֵ��ʾ����
*/
#define LVOS_TRACEP_ACTIVE(tracep_name, flag)

/** \brief ��TracePoint��ӻص����� 
    \param[in] tracep_name TracePoint�����ƣ��Ͷ���ʱһ�£���Ҫ������
    \param[in] fn �ص�����
    \param[in] desc ��Ҫ������Ϣ
    \param[in] flag ��ʼ�Ǽ����ȥ����, FALSE��ʾȥ���������ʾ����
*/
#define LVOS_TRACEP_ADD_HOOK(tracep_name, fn, desc, flag)

/** \brief ��TracePointɾ��һ���ص����� */
#define LVOS_TRACEP_DEL_HOOK(tracep_name, fn)

/** \brief ����/ȥ����һ���ص����� */
#define LVOS_TRACEP_HOOK_ACTIVE(tracep_name, fn, flag)

/** \brief ����һ������������TracePoint (�����԰汾) */
#define LVOS_TRACEP_DEF0_D(tracep_name)

/** \brief ����һ����������TracePoint (�����԰汾)
    \param[in] tracep_name TracePoint������
    \param[in] ...  �ص��������Զ�������б���  :  OSP_S32 *, OSP_U64 *
    \note  ����ֻ���ǺϷ��ı������ƣ���Ҫ�����ţ�������õ�ʱ��Ҳ���ܼ�����
*/
#define LVOS_TRACEP_DEFN_D(tracep_name, ...)

/** \brief ���ò���������TracePoint�ص����� (�����԰汾)
    \note  ��Ҫ��ҵ������е��ò��Դ���ע���TracePoint
*/
#define LVOS_TRACEP_CALL0_D(tracep_name)

/** \brief ���ô�������TracePoint�ص����� (�����԰汾)
    \note     \note  ��Ҫ��ҵ������е��ò��Դ���ע���TracePoint
*/
#define LVOS_TRACEP_CALLN_D(tracep_name, ...)

/** \brief ���ò���������TracePoint�ص����� (�����԰汾)
    \note  ��Ҫ��ҵ������е��ò��Դ���ע���TracePoint
*/
#define LVOS_TRACEPHOOK_CALL0(tracep_name)

/** \brief ���ô�������TracePoint�ص����� (�����԰汾)
    \note     \note  ��Ҫ��ҵ������е��ò��Դ���ע���TracePoint
*/
#define LVOS_TRACEPHOOK_CALLN(tracep_name, ...)

/** \brief ע��һ��TracePoint (�����԰汾)
    \param[in] tracep_name TracePoint�����ƣ��Ͷ���ʱһ�£���Ҫ������
    \param[in] desc ��Ҫ������Ϣ
    \param[in] flag ��ʼ�Ǽ����ȥ����, FALSE��ʾȥ���������ʾ����
    \note  ҵ������е��õ�TracePoint������ҵ�������ע�ᣬ���Դ�����Ե���ҵ�����ע���TracePoint���Ƿ�������Ҫ����ʹ��
*/
#define LVOS_TRACEP_REG_POINT_D(tracep_name, desc, flag)

/** \brief ע��һ��TracePoint (�����԰汾) */
#define LVOS_TRACEP_UNREG_POINT_D(tracep_name)

/** \brief ����/ȥ����һ��TracePoint (�����԰汾)
    \param[in] tracep_name TracePoint����
    \param[in] flag FALSE��ʾȥ�������ֵ��ʾ����
*/
#define LVOS_TRACEP_ACTIVE_D(tracep_name, flag)

/** \brief ��TracePoint��ӻص����� (�����԰汾)
    \param[in] tracep_name TracePoint�����ƣ��Ͷ���ʱһ�£���Ҫ������
    \param[in] fn �ص�����
    \param[in] desc ��Ҫ������Ϣ
    \param[in] flag ��ʼ�Ǽ����ȥ����, FALSE��ʾȥ���������ʾ����
*/
#define LVOS_TRACEP_ADD_HOOK_D(tracep_name, fn, desc, flag)

/** \brief ��TracePointɾ��һ���ص����� (�����԰汾) */
#define LVOS_TRACEP_DEL_HOOK_D(tracep_name, fn)

/** \brief ����/ȥ����һ���ص����� (�����԰汾) */
#define LVOS_TRACEP_HOOK_ACTIVE_D(tracep_name, fn, flag)

/*HVS�¿��*/
#define LVOS_TP_REG(name, desc, fn)
#define LVOS_TP_UNREG(name)
#define LVOS_TP_START(name, ...) 
#define LVOS_TP_NOPARAM_START(name)
#define LVOS_TP_END

#else

typedef void (*FN_TRACEP_COMMON_T)(LVOS_TRACEP_PARAM_S *, ...);

/**
 \ingroup VOS_TRACEP 
 *���ڱ���ÿ���ص����������Ϣ�����ݽṹ��
 */
typedef struct
{
    OSP_CHAR  szName[MAX_NAME_LEN];  /**< ���hook�����֡� */
    OSP_CHAR  szDesc[MAX_DESC_LEN]; /**< ���hook�������ֶΡ� */
    OSP_S32   iId;    /**< Ψһ��ʶ�������ɾ����ñ�ʶ�����ӡ� */
    OSP_S32   iActive;  /**< ����ʶ���hook�Ƿ񼤻*/
    OSP_S32   iDbgOnly; /**< ������*/
    FN_TRACEP_COMMON_T fnHook; /**< �ص�������*/
} LVOS_TRACEP_HOOK_S;

/**
   \ingroup VOS_TRACEP 
 *���ڱ���ÿ��tracepint�����Ϣ�����ݽṹ��
 */
typedef struct
{
    OSP_CHAR  szName[MAX_NAME_LEN]; /**< ���tracepoint�����֡� */
    OSP_CHAR  szDesc[MAX_DESC_LEN]; /**< ���tracepoint�������ֶΡ� */
    OSP_U32   uiPid; /**< ģ��ID�š�*/
    OSP_S32   iId;     /**< ��Ϊ��ʶ�������ӻ�ɾ��Hookʱ����������1�Ĳ����� */
    OSP_S32   iActive;  /**< ����ʶ���tracepoint �Ƿ񼤻�*/
    OSP_S32   iDbgOnly; /**< ������*/
    LVOS_TRACEP_PARAM_S stParam;  /**< ���ڴ�Żص��������Զ��������*/
    LVOS_TRACEP_HOOK_S  stHooks[LVOS_MAX_HOOK_PER_TRACEP]; /**< ���ÿ��tracepoint�ϵĻص�������*/
} LVOS_TRACEP_S;

/*HVS�¿��*/
typedef struct tagLVOS_TRACEP_NEW_S
{
    char szName[MAX_NAME_LEN];
    char szDesc[MAX_DESC_LEN];
    uint32_t uiPid;
    int32_t iActive;
    int32_t type;
    uint32_t timeAlive;
    uint32_t timeCalled;
    FN_TRACEP_COMMON_T fnHook;
    LVOS_TRACEP_PARAM_S stParam;
}LVOS_TRACEP_NEW_S;

/** \ingroup VOS_TRACEP 
    \par ������
	 ����һ��TracePoint��������������\ref LVOS_TRACEP_DEFN������ͬ����\ref LVOS_TRACEP_DEFN�ɴ�������
    \attention  ����ֻ���ǺϷ��ı������ƣ���Ҫ�����ţ�������õ�ʱ��Ҳ���ܼ����š�
    \param tracep_name [in] TracePoint�����ƣ�ȡֵ������С��128�ֽڡ�
    \par����:  
	 lvos_tracepoint.h
	\since V100R001C00
*/
#define LVOS_TRACEP_DEF0(tracep_name) \
    typedef void (*FN_TRACEP_T_##tracep_name)(LVOS_TRACEP_PARAM_S *);

/** \ingroup VOS_TRACEP 
    \par ������
	  ����һ��TracePoint���ɴ���������\ref LVOS_TRACEP_DEF0������ͬ����\ref LVOS_TRACEP_DEF0���ܴ�������
    \attention  ����ֻ���ǺϷ��ı������ƣ���Ҫ�����ţ�������õ�ʱ��Ҳ���ܼ����š�
    \param tracep_name [in] TracePoint�����ƣ�ȡֵ������С��128�ֽڡ�
    \param ...  [in] �ص��������Զ�������б��磺OSP_S32 *, OSP_U64 *��
    \par����:  
	 lvos_tracepoint.h
	\since V100R001C00
*/
#define LVOS_TRACEP_DEFN(tracep_name, ...) \
    typedef void (*FN_TRACEP_T_##tracep_name)(LVOS_TRACEP_PARAM_S *, __VA_ARGS__);

#define LVOS_TRACEP_CALL(tracep_name, ...)                                             \
do                                                                              \
{                                                                               \
    static LVOS_TRACEP_S *_pstTp = NULL;                                        \
    static OSP_S32   _iId = 0;                                                  \
    OSP_U32   _i;                                                               \
    if (unlikely(NULL == _pstTp || _pstTp->iId != _iId))                       \
    {                                                                           \
        _pstTp = LVOS_FindTracePoint(MY_PID, #tracep_name);                            \
        if (NULL == _pstTp)                                                     \
        {                                                                       \
            DBG_LogWarning(DBG_LOGID_BUTT, "tracepoint `%s` not register", #tracep_name);    \
            break;                                                              \
        }                                                                       \
        else                                                                    \
        {                                                                       \
            _iId = _pstTp->iId;                                                 \
        }                                                                       \
    }                                                                           \
    if (_pstTp->iActive != LVOS_TRACEP_STAT_ACTIVE)                             \
    {                                                                           \
        break;                                                                  \
    }                                                                           \
    for (_i = 0; _i < LVOS_MAX_HOOK_PER_TRACEP; _i++)                           \
    {                                                                           \
        if ((_pstTp->stHooks[_i].iActive == LVOS_TRACEP_STAT_ACTIVE)            \
            && (NULL != _pstTp->stHooks[_i].fnHook))                            \
        {                                                                       \
            FN_TRACEP_T_##tracep_name fn = (FN_TRACEP_T_##tracep_name)_pstTp->stHooks[_i].fnHook;     \
            fn(__VA_ARGS__);                                                    \
        }                                                                       \
    }                                                                           \
}while(0)

        
#define LVOS_TRACEPHOOK_CALL(tracep_name, fn, ...)                              \
do                                                                              \
{                                                                               \
    static LVOS_TRACEP_S *_pstTp = NULL;                                        \
    static LVOS_TRACEP_HOOK_S *_pstHook = NULL;                                 \
    static OSP_S32   _iId = 0;                                                  \
    static OSP_S32   _iHookId = 0;                                              \
    if (unlikely(NULL == _pstTp || _pstTp->iId != _iId))                       \
    {                                                                           \
        _pstTp = LVOS_FindTracePoint(MY_PID, #tracep_name);                     \
        if (NULL == _pstTp)                                                     \
        {                                                                       \
            DBG_LogWarning(DBG_LOGID_BUTT, "tracepoint `%s` not register", #tracep_name);    \
            break;                                                              \
        }                                                                       \
        else                                                                    \
        {                                                                       \
            _iId = _pstTp->iId;                                                 \
        }                                                                       \
    }                                                                           \
    if (_pstTp->iActive != LVOS_TRACEP_STAT_ACTIVE)                             \
    {                                                                           \
        break;                                                                  \
    }                                                                           \
    if (unlikely(NULL == _pstHook || _pstHook->iId != _iHookId))               \
    {                                                                           \
        _pstHook = LVOS_FindTraceHook(_pstTp, #fn);                             \
        if (NULL == _pstHook)                                                   \
        {                                                                       \
            DBG_LogWarning(DBG_LOGID_BUTT, "hook `%s`not found", #fn);        \
            break;                                                              \
        }                                                                       \
        else                                                                    \
        {                                                                       \
            _iHookId = _pstHook->iId;                                           \
        }                                                                       \
    }                                                                           \
    if ((_pstHook->iActive == LVOS_TRACEP_STAT_ACTIVE)                          \
        && (NULL != _pstHook->fnHook))                                          \
    {                                                                           \
        FN_TRACEP_T_##tracep_name _fn = (FN_TRACEP_T_##tracep_name)_pstHook->fnHook; \
        _fn(__VA_ARGS__);                                                       \
    }                                                                           \
}while(0)

/** \ingroup VOS_TRACEP 
    \par ������
	  ͨ������tracep_nameָ��TracePoint��ִ�и�TracePoint���м����˵Ļص������� 
    \attention  ��Ҫ��ҵ������е��ò��Դ���ע���TracePoint��
    \param tracep_name [in] TracePoint�����ƣ�ȡֵ������С��128�ֽڡ�    
    \par����:  
	 lvos_tracepoint.h
	\since V100R001C00
*/
#define LVOS_TRACEP_CALL0(tracep_name)  LVOS_TRACEP_CALL(tracep_name, &_pstTp->stParam)

/** \ingroup VOS_TRACEP 
    \par ������
	  ͨ������tracep_nameָ��TracePoint��ִ�и�TracePoint���м����˵Ļص����������ҿ�ͨ��������ָ���ص������Ĳ����� 
    \attention  ��Ҫ��ҵ������е��ò��Դ���ע���TracePoint��
    \param tracep_name [in] TracePoint�����ƣ�ȡֵ������С��128�ֽڡ�
    \param ... [in] �ص��������Զ��������     
    \par����:  
	 lvos_tracepoint.h
	\since V100R001C00
*/
#define LVOS_TRACEP_CALLN(tracep_name, ...)  LVOS_TRACEP_CALL(tracep_name, &_pstTp->stParam, __VA_ARGS__)

/** \ingroup VOS_TRACEP 
    \par ������
	 ͨ������tracep_nameָ��TracePoint��ִ�в���fnָ���Ļص���������\ref LVOS_TRACEP_CALL0�������ǣ�LVOS_TRACEP_CALL0��ִ��������tracep_name���tracepoint��Ļص�������
    \attention  ��Ҫ��ҵ������е��ò��Դ���ע���TracePoint��
    \param tracep_name [in] TracePoint�����ƣ�ȡֵ������С��128�ֽڡ�  
    \param fn [in] �ص������� 
    \par����:  
	 lvos_tracepoint.h
	\since V100R001C00
*/
#define LVOS_TRACEPHOOK_CALL0(tracep_name, fn)      LVOS_TRACEPHOOK_CALL(tracep_name, fn, &_pstTp->stParam)

/** \ingroup VOS_TRACEP 
    \par ������
	 ͨ������tracep_nameָ��TracePoint��ִ�в���fnָ���Ļص����������ҿ�ͨ��������ָ���ص������Ĳ�������\ref LVOS_TRACEP_CALLN�������ǣ�LVOS_TRACEP_CALLN��ִ��������tracep_name���tracepoint��Ļص�������
    \attention  ��Ҫ��ҵ������е��ò��Դ���ע���TracePoint��
    \param tracep_name [in] TracePoint�����ƣ�ȡֵ������С��128�ֽڡ�  
    \param fn [in] �ص�������
    \param ... [in] �ص��������Զ��������     
    \par����:  
	 lvos_tracepoint.h
	\since V100R001C00
*/
#define LVOS_TRACEPHOOK_CALLN(tracep_name, fn, ...) LVOS_TRACEPHOOK_CALL(tracep_name, fn, &_pstTp->stParam, __VA_ARGS__)

/** \ingroup VOS_TRACEP 
    \par ������
	   TracePointע��ӿڣ�ͨ���˽ӿ��û�����ע��һ��tracePoint��
    \attention  ҵ������е��õ�TracePoint������ҵ�������ע�ᣬ���Դ�����Ե���ҵ�����ע���TracePoint��
    \param tracep_name [in] TracePoint�����ƣ���Ҫ�����ţ�ȡֵ������С��128�ֽڡ�  
    \param desc [in] ע��ӿ���صļ�Ҫ������Ϣ��ȡֵ������С��256�ֽڡ�
    \param flag [in] ���ó�ʼ�Ǽ����ȥ����, FALSE��ʾȥ���TURE��ʾ���
    \par����:  
	 lvos_tracepoint.h
	\since V100R001C00
*/
#define LVOS_TRACEP_REG_POINT(tracep_name, desc, flag)   LVOS_RegTracePoint(MY_PID, #tracep_name, desc, flag, FALSE)

/** \ingroup VOS_TRACEP 
    \par ������
	   TracePointע���ӿڣ���\ref LVOS_TRACEP_REG_POINTע��ӿ����Ӧ��
    \param tracep_name [in] TracePoint�����ƣ�ȡֵ������С��128�ֽڡ�  
     \par����:  
	 lvos_tracepoint.h
	\since V100R001C00
*/
#define LVOS_TRACEP_UNREG_POINT(tracep_name)       LVOS_UnRegTracePoint(MY_PID, #tracep_name)

/** \ingroup VOS_TRACEP  
    \par ������
	  ����/ȥ����һ��TracePoint��TracePoint�������֣�LVOS_TRACEP_STAT_ACTIVE�������LVOS_TRACEP_STAT_DEACTIVE��ȥ�����LVOS_TRACEP_STAT_DELETED��ע������˺����޹أ���
    \param tracep_name [in] TracePoint���ƣ�ȡֵ������С��128�ֽڡ�  
    \param flag [in] FALSE��ʾȥ�������ֵ��ʾ���
    \par����:  
	 lvos_tracepoint.h
	\since V100R001C00
*/
#define LVOS_TRACEP_ACTIVE(tracep_name, flag)      LVOS_ActiveTracePoint(MY_PID, #tracep_name, flag)

/** \ingroup VOS_TRACEP 
    \par ������
	  ��tracep_nameָ����tracepoint�����һ���ص�������
    \param tracep_name [in] TracePoint�����ƣ���Ҫ�����ţ�ȡֵ������С��128�ֽڡ�  
    \param fn [in] �ص�������ȡֵ���ǿա�
    \param desc [in] ��Ҫ������Ϣ��ȡֵ������С��256�ֽڡ�  
    \param flag [in] ��ʼ���ص������ļ���״̬��ȡֵ��FALSE��ʾȥ�������ֵ��ʾ���
    \par����:  
	 lvos_tracepoint.h
	\since V100R001C00
*/
#define LVOS_TRACEP_ADD_HOOK(tracep_name, fn, desc, flag)                              \
    do                                                                          \
    {                                                                           \
        FN_TRACEP_T_##tracep_name _Hookfn = fn;                                        \
        LVOS_AddTracePointHook(MY_PID, #tracep_name, #fn, (FN_TRACEP_COMMON_T)_Hookfn, desc, flag, FALSE);\
    } while(0) 
    
/** \ingroup VOS_TRACEP 
    \par ������
	   ͨ������tracep_nameָ����Ӧ��tracepoint��ɾ����tracepoint�ϻص�������fn�ĺ�����
    \param tracep_name [in] TracePoint�����ƣ�ȡֵ������С��128�ֽڡ� 
    \param fn [in] �ص�������ȡֵ���ǿա�
    \par����:  
	 lvos_tracepoint.h
	\since V100R001C00
*/
#define LVOS_TRACEP_DEL_HOOK(tracep_name, fn)                                          \
    do                                                                          \
    {                                                                           \
        FN_TRACEP_T_##tracep_name _Hookfn = fn;  /* ������� */                        \
        UNREFERENCE_PARAM(_Hookfn);                                           \
        LVOS_DelTracePointHook(MY_PID, #tracep_name, #fn);                             \
    } while (0)

/** \ingroup VOS_TRACEP 
    \par ������
	   ����/ȥ����һ���ص�������ͨ������tracep_nameָ����Ӧ��tracepoint���޸ĸ�tracepoint�ϻص�������fn�ĺ����Ļ״̬��
    \param tracep_name [in] TracePoint�����ƣ�ȡֵ������С��128�ֽڡ�  
    \param fn [in] �ص�������ȡֵ���ǿա�
    \param flag [in] �޸Ļص������Ļ״̬��ȡֵ��FALSE��ʾȥ�������ֵ��ʾ���
    \par����:  
	 lvos_tracepoint.h
	\since V100R001C00
*/    
#define LVOS_TRACEP_HOOK_ACTIVE(tracep_name, fn, flag) LVOS_ActiveTracePointHook(MY_PID, #tracep_name, #fn, flag)


#ifdef _DEBUG

/** \ingroup VOS_TRACEP 
    \par ������
	  ����һ��TracePoint��������������LVOS_TRACEP_DEFN������ͬ����LVOS_TRACEP_DEFN�ɴ�����(�����԰汾���ǵ��԰汾Ϊ��)��
    \attention  ����ֻ���ǺϷ��ı������ƣ���Ҫ�����ţ�������õ�ʱ��Ҳ���ܼ����š�
    \param tracep_name [in] TracePoint�����ƣ�ȡֵ������С��128�ֽڡ�
    \par����:  
	 lvos_tracepoint.h
	\since V100R001C00
*/
#define LVOS_TRACEP_DEF0_D(tracep_name)                LVOS_TRACEP_DEF0(tracep_name)

/** \ingroup VOS_TRACEP 
    \par ������
	  ����һ��TracePoint���ɴ���������LVOS_TRACEP_DEF0������ͬ����LVOS_TRACEP_DEF0���ܴ�����(�����԰汾���ǵ��԰汾Ϊ��)��
    \attention  ����ֻ���ǺϷ��ı������ƣ���Ҫ�����ţ�������õ�ʱ��Ҳ���ܼ����š�
    \param tracep_name [in] TracePoint�����ƣ�ȡֵ������С��128�ֽڡ�
    \param ...  [in] �ص��������Զ���������磺OSP_S32 *��OSP_U64 *��
    \par����:  
	 lvos_tracepoint.h
	\since V100R001C00
*/
#define LVOS_TRACEP_DEFN_D(tracep_name, ...)           LVOS_TRACEP_DEFN(tracep_name, __VA_ARGS__)

/** \ingroup VOS_TRACEP 
    \par ������
	  �ص�������ִ�У��ûص�������������(�����԰汾���ǵ��԰汾Ϊ��)��
    \attention  ��Ҫ��ҵ������е��ò��Դ���ע���TracePoint��
    \param tracep_name [in] TracePoint�����ƣ�ȡֵ������С��128�ֽڡ�     
    \par����:  
	 lvos_tracepoint.h
	\since V100R001C00
*/
#define LVOS_TRACEP_CALL0_D(tracep_name)               LVOS_TRACEP_CALL0(tracep_name)

/** \ingroup VOS_TRACEP 
    \par ������
	  �ص�������ִ�У��ûص������ɴ�����(�����԰汾���ǵ��԰汾Ϊ��)��  
    \attention  ��Ҫ��ҵ������е��ò��Դ���ע���TracePoint��
    \param tracep_name [in] TracePoint�����ƣ�ȡֵ������С��128�ֽڡ�
    \param ... [in] �ص��������Զ���������磺OSP_S32 *��OSP_U64 *��  
    \par����:  
	 lvos_tracepoint.h
	\since V100R001C00
*/
#define LVOS_TRACEP_CALLN_D(tracep_name, ...)          LVOS_TRACEP_CALLN(tracep_name, __VA_ARGS__)

/** \ingroup VOS_TRACEP 
    \par ������
	  �ص�������ִ�У��ûص�����������������\ref LVOS_TRACEP_CALL0�������ǣ�LVOS_TRACEP_CALL0������ִ�в���tracep_nameָ����tracepoint�����еĻص�����(�����԰汾���ǵ��԰汾Ϊ��)��
    \attention  ��Ҫ��ҵ������е��ò��Դ���ע���TracePoint��
    \param tracep_name [in] TracePoint�����ƣ�ȡֵ������С��128�ֽڡ�  
    \param fn [in] �ص�������ȡֵ���ǿա� 
    \par����:  
	 lvos_tracepoint.h
	\since V100R001C00
*/
#define LVOS_TRACEPHOOK_CALL0_D(tracep_name, fn)       LVOS_TRACEPHOOK_CALL0(tracep_name, fn)

/** \ingroup VOS_TRACEP 
    \par ������
	  �ص�������ִ�У��ûص������ɴ���������\ref LVOS_TRACEP_CALLN�������ǣ�LVOS_TRACEP_CALLN������ִ�в���tracep_nameָ����tracepoint�����еĻص�����(�����԰汾���ǵ��԰汾Ϊ��)��
    \attention  ��Ҫ��ҵ������е��ò��Դ���ע���TracePoint��
    \param tracep_name [in] TracePoint�����ƣ�ȡֵ������С��128�ֽڡ�  
    \param fn [in] �ص�������ȡֵ���ǿա�
    \param ... [in] �ص��������Զ���������磺OSP_S32 *��OSP_U64 *��    
    \par����:  
	 lvos_tracepoint.h
	\since V100R001C00
*/
#define LVOS_TRACEPHOOK_CALLN_D(tracep_name, fn, ...)  LVOS_TRACEPHOOK_CALLN(tracep_name, fn, __VA_ARGS__)

/** \ingroup VOS_TRACEP 
    \par ������
	   TracePointע��ӿڣ�����ע��һ��tracePoint(�����԰汾���ǵ��԰汾Ϊ��)��
    \attention  ҵ������е��õ�TracePoint������ҵ�������ע�ᣬ���Դ�����Ե���ҵ�����ע���TracePoint��
    \param tracep_name [in] TracePoint�����ƣ��Ͷ���ʱһ�£���Ҫ�����ţ�ȡֵ������С��128�ֽڡ�  
    \param desc [in] ��Ҫ������Ϣ��ȡֵ������С��256�ֽڡ�  
    \param flag [in] ��ʼ�Ǽ����ȥ����, FALSE��ʾȥ�������ֵ��ʾ���
    \par����:  
	 lvos_tracepoint.h
	\since V100R001C00
*/
#define LVOS_TRACEP_REG_POINT_D(tracep_name, desc, flag)     LVOS_RegTracePoint(MY_PID, #tracep_name, desc, flag, TRUE)

/** \ingroup VOS_TRACEP 
    \par ������
	   TracePointע���ӿڣ���\ref LVOS_TRACEP_REG_POINT��Ӧ(�����԰汾���ǵ��԰汾Ϊ��)��
    \param tracep_name [in] TracePoint�����ƣ�ȡֵ������С��128�ֽڡ�
     \par����:  
	 lvos_tracepoint.h
	\since V100R001C00
*/
#define LVOS_TRACEP_UNREG_POINT_D(tracep_name)         LVOS_TRACEP_UNREG_POINT(tracep_name)

/** \ingroup VOS_TRACEP  
    \par ������
	  ����/ȥ����һ��TracePoint��TracePoint��������״̬��LVOS_TRACEP_STAT_ACTIVE�������LVOS_TRACEP_STAT_DEACTIVE��ȥ�����LVOS_TRACEP_STAT_DELETED��ע������˺����޹أ����������ڵ��԰汾��
    \param tracep_name [in] TracePoint���ƣ�ȡֵ������С��128�ֽ�  
    \param flag [in] �ص������ļ���״̬��FALSE��ʾȥ�������ֵ��ʾ���
    \par����:  
	 lvos_tracepoint.h
	\since V100R001C00
*/
#define LVOS_TRACEP_ACTIVE_D(tracep_name, flag)        LVOS_TRACEP_ACTIVE(tracep_name, flag)

/** \ingroup VOS_TRACEP 
    \par ������
	  ���Ӧ������tracep_name��tracepoint�����һ���ص�����(�����԰汾���ǵ��԰汾Ϊ��)��
    \param tracep_name TracePoint�����ƣ���Ҫ�����ţ�ȡֵ������С��128�ֽڡ�  
    \param fn [in] �ص�������ȡֵ���ǿա�
    \param desc [in] ��Ҫ������Ϣ��ȡֵ������С��256�ֽڡ�  
    \param flag [in] ��ʼ���ص������ļ���״̬��ȡֵ��FALSE��ʾȥ�������ֵ��ʾ���
    \par����:  
	 lvos_tracepoint.h
	\since V100R001C00
*/
#define LVOS_TRACEP_ADD_HOOK_D(tracep_name, fn, desc, flag)                            \
    do                                                                          \
    {                                                                           \
        FN_TRACEP_T_##tracep_name _Hookfn = fn;                                        \
        LVOS_AddTracePointHook(MY_PID, #tracep_name, #fn, (FN_TRACEP_COMMON_T)_Hookfn, desc, flag, TRUE);\
    } while(0) 

 /** \ingroup VOS_TRACEP 
    \par ������
	   ͨ������tracep_nameָ��tracepoint��ɾ���ص�������fn�ĺ���(�����԰汾���ǵ��԰汾Ϊ��)��
    \param tracep_name [in] TracePoint�����ƣ�ȡֵ������С��128�ֽڡ�  
    \param fn [in]  �ص�������ȡֵ���ǿա�
    \par����:  
	 lvos_tracepoint.h
	\since V100R001C00
*/
#define LVOS_TRACEP_DEL_HOOK_D(tracep_name, fn)        LVOS_TRACEP_DEL_HOOK(tracep_name, fn)

/** \ingroup VOS_TRACEP 
    \par ������
	   ����/ȥ����һ���ص��������޸�������tracep_name��tracepoint�ϻص�����fn�Ļ״̬(�����԰汾���ǵ��԰汾Ϊ��)��
    \param tracep_name [in] TracePoint�����ƣ�ȡֵ������С��128�ֽڡ�
    \param fn [in] �ص�������ȡֵ���ǿա�
    \param flag [in] �޸Ļص������Ļ״̬��ȡֵ��FALSE��ʾȥ�������ֵ��ʾ���
    \par����:  
	 lvos_tracepoint.h
	\since V100R001C00
*/  
#define LVOS_TRACEP_HOOK_ACTIVE_D(tracep_name, fn, flag)  LVOS_TRACEP_HOOK_ACTIVE(tracep_name, fn, flag)

/*HVS�¿��*/

/*ע��Tracepoint*/
/** \ingroup VOS_TRACEP 
    \par ������
	   HVS�¿�ܵ�ע��ӿڣ�����ע��һ��tracePoint��HASH���С�
    \param name [in] TracePoint�����ƣ��Ͷ���ʱһ�£���Ҫ�����ţ�ȡֵ������С��128�ֽڡ�  
    \param desc [in] ��Ҫ������Ϣ��ȡֵ������С��256�ֽڡ�  
    \param fn [in] �ص�������ȡֵ���ǿա�
    \par����:  
	 lvos_tracepoint.h
	\since V100R001C00
*/
#define LVOS_TP_REG(name, desc, fn)    LVOS_HVS_regTracePoint(MY_PID, #name, desc, (FN_TRACEP_COMMON_T)fn)
/*ж��Tracepoint*/  
/** \ingroup VOS_TRACEP 
    \par ������
	   HVS�¿�ܵ�ע���ӿڣ����ڴ�HASH����ע��һ��tracePoint��
    \param name [in] TracePoint�����ƣ��Ͷ���ʱһ�£���Ҫ�����ţ�ȡֵ������С��128�ֽڡ�  
    \par����:  
	 lvos_tracepoint.h
	\since V100R001C00
*/  
#define LVOS_TP_UNREG(name)                      LVOS_HVS_unregTracePoint(PID_OSP_NULL, #name)
/*������ϵ�*/
/** \ingroup VOS_TRACEP 
    \par ������
	   HVS�¿�ܵĲ�����ϵ㹦�ܡ�
    \param name [in] TracePoint�����ƣ��Ͷ���ʱһ�£���Ҫ�����ţ�ȡֵ������С��128�ֽڡ�
    \param ... [in] ���ص�������Ӧ�Ĳ�����Ϣ��
    \par����:  
	 lvos_tracepoint.h
	\since V100R001C00
*/ 
#define LVOS_TP_START(name, ...)                                 \
    do                                                                                          \
    {                                                                                           \
        static LVOS_TRACEP_NEW_S *_pstTp = NULL;                      \
        if (unlikely(NULL == _pstTp))                                             \
        {                                                                                       \
            (void)LVOS_HVS_getTracePoint(PID_OSP_NULL, #name, &_pstTp);     \
            if (NULL == _pstTp)                                                     \
            {                                                                                 \
                DBG_LogWarning(DBG_LOGID_BUTT, "tracepoint `%s` not registered", #name);    \
            }                                                                                   \
        }                                                                                       \
        if (NULL != _pstTp && LVOS_TRACEP_STAT_ACTIVE == _pstTp->iActive && LVOS_TP_TYPE_CALLBACK == _pstTp->type)              \
        {                                                                                       \
            _pstTp->fnHook(&_pstTp->stParam, __VA_ARGS__);  \
            _pstTp->timeCalled++;                                   \
            if (_pstTp->timeAlive > 0 && 0 == --(_pstTp->timeAlive))                                                \
            {                                                                                                           \
                LVOS_HVS_deactiveTracePoint(PID_OSP_NULL, #name);                                            \
            }                                                                                           \
        }                                                                                       \
        else                                                                                   \
        {                                                                                       \
            if (NULL != _pstTp && LVOS_TRACEP_STAT_ACTIVE == _pstTp->iActive && LVOS_TP_TYPE_ABORT == _pstTp->type)               \
            {                                                                                   \
                DPAX_PANIC();              \
            }                      \
            if (NULL != _pstTp && LVOS_TRACEP_STAT_ACTIVE == _pstTp->iActive && LVOS_TP_TYPE_RESET == _pstTp->type)               \
            {                                                                                   \
                system("reboot");                \
            }                                           \
            else if (NULL != _pstTp && LVOS_TRACEP_STAT_ACTIVE == _pstTp->iActive && LVOS_TP_TYPE_PAUSE == _pstTp->type)        \
            {                                           \
                LVOS_HVS_doTracePointPause(_pstTp);               \
                _pstTp->timeCalled++;                                   \
                if (_pstTp->timeAlive > 0 && 0 == --(_pstTp->timeAlive))                                                \
                {                                                                                                           \
                    LVOS_HVS_deactiveTracePoint(PID_OSP_NULL, #name);                                            \
                }                                                                           \
            }
/*������ϵ�(���޻ص�������ص�����ֻ���û�����ʱ)*/
/** \ingroup VOS_TRACEP 
    \par ������
	   HVS�¿�ܵĲ�����ϵ㹦��(���޻ص�������ص�����ֻ���û�����ʱ)��
    \param name [in] TracePoint�����ƣ��Ͷ���ʱһ�£���Ҫ�����ţ�ȡֵ������С��128�ֽڡ�
    \par����:  
	 lvos_tracepoint.h
	\since V100R001C00
*/ 
#define LVOS_TP_NOPARAM_START(name)                                 \
    do                                                                                          \
    {                                                                                           \
        static LVOS_TRACEP_NEW_S *_pstTp = NULL;                      \
        if (unlikely(NULL == _pstTp))                                             \
        {                                                                                       \
            (void)LVOS_HVS_getTracePoint(PID_OSP_NULL, #name, &_pstTp);     \
            if (NULL == _pstTp)                                                     \
            {                                                                                 \
                DBG_LogWarning(DBG_LOGID_BUTT, "tracepoint `%s` not registered", #name);    \
            }                                                                                   \
        }                                                                                       \
        if (NULL != _pstTp && LVOS_TRACEP_STAT_ACTIVE == _pstTp->iActive && LVOS_TP_TYPE_CALLBACK == _pstTp->type)              \
        {                                                                                       \
            _pstTp->fnHook(&_pstTp->stParam);                               \
            _pstTp->timeCalled++;                                   \
            if (_pstTp->timeAlive > 0 && 0 == --(_pstTp->timeAlive))                                                \
            {                                                                                                           \
                LVOS_HVS_deactiveTracePoint(PID_OSP_NULL, #name);                                            \
            }                                                                                           \
        }                                                                                       \
        else                                                                                   \
        {                                                                                       \
            if (NULL != _pstTp && LVOS_TRACEP_STAT_ACTIVE == _pstTp->iActive && LVOS_TP_TYPE_ABORT == _pstTp->type)               \
            {                                                                                   \
                DPAX_PANIC();              \
            }                      \
            if (NULL != _pstTp && LVOS_TRACEP_STAT_ACTIVE == _pstTp->iActive && LVOS_TP_TYPE_RESET == _pstTp->type)               \
            {                                                                                   \
                system("reboot");                \
            }                                           \
            else if (NULL != _pstTp && LVOS_TRACEP_STAT_ACTIVE == _pstTp->iActive && LVOS_TP_TYPE_PAUSE == _pstTp->type)        \
            {                                           \
                LVOS_HVS_doTracePointPause(_pstTp);               \
                _pstTp->timeCalled++;                                   \
                if (_pstTp->timeAlive > 0 && 0 == --(_pstTp->timeAlive))                                                \
                {                                                                                                           \
                    LVOS_HVS_deactiveTracePoint(PID_OSP_NULL, #name);                                            \
                }                                                                           \
            }

/*������ϵ����*/
/** \ingroup VOS_TRACEP 
    \par ������
	   HVS�¿�ܲ�����ϵ������
    \par����:  
	 lvos_tracepoint.h
	\since V100R001C00
*/ 
#define LVOS_TP_END     \
        }                              \
    }while(0);
       
#else
#define LVOS_TRACEP_DEF0_D(tracep_name)
#define LVOS_TRACEP_DEFN_D(tracep_name, ...)
#define LVOS_TRACEP_CALL0_D(tracep_name)
#define LVOS_TRACEP_CALLN_D(tracep_name, ...)
#define LVOS_TRACEPHOOK_CALL0_D(tracep_name, fn)
#define LVOS_TRACEPHOOK_CALLN_D(tracep_name, fn, ...)
#define LVOS_TRACEP_REG_POINT_D(tracep_name, desc, flag)
#define LVOS_TRACEP_UNREG_POINT_D(tracep_name)
#define LVOS_TRACEP_ACTIVE_D(tracep_name, flag)
#define LVOS_TRACEP_ADD_HOOK_D(tracep_name, fn, desc, flag)
#define LVOS_TRACEP_DEL_HOOK_D(tracep_name, fn)
#define LVOS_TRACEP_HOOK_ACTIVE_D(tracep_name, fn, flag)

#define LVOS_TP_REG(name, desc, fn)  
#define LVOS_TP_UNREG(name)
#define LVOS_TP_START(name, ...) 
#define LVOS_TP_NOPARAM_START(name)
#define LVOS_TP_END


#endif

LVOS_TRACEP_S *LVOS_FindTracePoint(OSP_U32 v_uiPid, const OSP_CHAR *v_szName);


void LVOS_RegTracePoint(OSP_U32 v_uiPid, const OSP_CHAR *v_szName, const OSP_CHAR *v_szDesc, OSP_S32 v_iInitState, OSP_S32 v_iDbgOnly);
void LVOS_UnRegTracePoint(OSP_U32 v_uiPid, const OSP_CHAR *v_szName);

void LVOS_AddTracePointHook(OSP_U32 v_uiPid, const OSP_CHAR *v_szName, const OSP_CHAR *v_szHookName, FN_TRACEP_COMMON_T fnHook, const OSP_CHAR *v_szDesc, OSP_S32 v_iInitState, OSP_S32 v_iDbgOnly);
void LVOS_DelTracePointHook(OSP_U32 v_uiPid, const OSP_CHAR *v_szName, const OSP_CHAR *v_szHookName);

void LVOS_ActiveTracePoint(OSP_U32 v_uiPid, const OSP_CHAR *v_szName, OSP_S32 v_iFlag);
void LVOS_ActiveTracePointHook(OSP_U32 v_uiPid, const OSP_CHAR *v_szName, const OSP_CHAR *v_szHookName, OSP_S32 v_iFlag);
LVOS_TRACEP_HOOK_S *LVOS_FindTraceHook(LVOS_TRACEP_S *v_pstTp, const OSP_CHAR *v_szName);

/*HVS�¿��*/
void LVOS_HVS_doTracePointPause(LVOS_TRACEP_NEW_S *tracepoint);
int32_t LVOS_HVS_getTracePoint(uint32_t pid, const char *name, LVOS_TRACEP_NEW_S **tracepoint);
int32_t LVOS_HVS_regTracePoint(uint32_t pid, const char *name, const char *desc, FN_TRACEP_COMMON_T fnHook);
int32_t LVOS_HVS_unregTracePoint(uint32_t pid, const char *name);
int32_t LVOS_HVS_activeTracePoint(uint32_t pid, const char *name, int32_t type, uint32_t time, LVOS_TRACEP_PARAM_S userParam);
int32_t LVOS_HVS_deactiveTracePoint(uint32_t pid, const char *name);
int32_t LVOS_HVS_deactiveTracePointAll(void);

#endif

#endif
/** @} */

