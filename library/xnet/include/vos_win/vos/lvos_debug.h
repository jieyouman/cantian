/******************************************************************************

                  ��Ȩ���� (C), 2008-2008, ��Ϊ�������˿Ƽ����޹�˾

 ******************************************************************************
  �� �� ��   : debug.h
  �� �� ��   : ����

  ��������   : 2008��5��31��
  ����޸�   :
  ��������   : ����ģ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :

  2.��    ��   : 2008��11��13��

    �޸�����   : ����ģ��PID��������ж�����
  1.��    ��   : 2008��5��31��

    �޸�����   : �����ļ�

******************************************************************************/
/**
    \file  lvos_debug.h
    \brief ���Դ�ӡģ�����ӿ�, ��ͷ�ļ�����lvos.h�а���������Ҫ���а���
    \note  ֧��windows/linux_kernel/linux_user���첽�ӿڣ��޵�������������

    \date 2008-11-13
*/

/** \addtogroup DEBUG  ���Դ�ӡ
    @{ 
*/

#ifndef __DEBUG_H__
#define __DEBUG_H__
#if defined(__KERNEL__) && !defined(_PCLINT_)
#include <linux/kdb.h>
#endif

#include "lvos_diag.h"

#ifndef KDB_ENTER
#define KDB_ENTER()
#endif

#ifndef BUG
#define BUG()
#endif

/* ��ӡ����ö�� */
/** \brief ��Ϊ5������������������ͨ�쳣����Ϣ��������Ϣ
    \see MSG_SendSyncMsg, MSG_PostAsyncMsg
*/
typedef enum tagDBG_LOG_TYPE
{
    DBG_LOG_EMERG = 1,  /**< ����(��Ƿ��������Ƿ�ָ��) */
    DBG_LOG_ERROR,      /**< ����(����Դ�����) */
    DBG_LOG_WARNING,    /**< ��ͨ�쳣��������������� */
    DBG_LOG_EVENT,      /**< ��Ϣ */
    DBG_LOG_INFO = DBG_LOG_EVENT,
    DBG_LOG_TRACE,      /**< ������������Ϣ�����ڿ������ü�¼ */
    DBG_LOG_DEBUG = DBG_LOG_TRACE,

    DBG_LOG_BUTT
} DBG_LOG_TYPE;

/*****************************************************************************
 �� �� ��  : DBG_SetDefLogLevel
 ��������  : �趨 Ĭ�ϵĴ�ӡ����
 �������  : v_iLogLevel    �����ӡ����Ϣ����
 �������  : ��
 �� �� ֵ  : TRUE   ���óɹ�
             FALSE  ����ʧ��
 ���ú���  : DBG_GetSharedMem()
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2009��10��30��


*****************************************************************************/
OSP_BOOL DBG_SetDefLogLevel(OSP_U8 v_iLogLevel);

OSP_U8 DBG_GetPidLevel(OSP_U32 v_uiPid);

/** \brief ����PID������ 
    \param[in] v_uiPid PID��ֵ
    \param[in] v_szName  PID������
    \note �ڲ���ֱ��ʹ��v_szName����ĵ�ַ�����´���ַ��������Դ�������Ʋ����Ǿֲ������ĵ�ַ
*/
void DBG_SetPidName(OSP_U32 v_uiPid, OSP_CHAR *v_szName);

/** \brief ��ȡPID��Ӧ�����ƣ����δ֪�򷵻� "<pid>"
    \param[in] v_uiPid ����PID
    \return �����ַ���ָ��
*/
OSP_CHAR *DBG_GetPidName(OSP_U32 v_uiPid);

/** \brief ��¼������Ϣ����Ҫ���øú�����ʹ�������궨��ӿڴ���
    \param[in] v_uiPid          ����ģ���PID
    \param[in] v_iLogLevel      ���Դ�ӡ�ļ���, \ref DBG_LOG_TYPE
    \param[in] v_pszFuncName    �����ߵĺ�����
    \param[in] v_iLine          ���øýӿڵ�Դ���������к�
    \param[in] v_uiLogId        ��־��ţ������Զ�����־�������߷���
    \param[in] v_pszFormat      ���ڿ���������ݵĸ�ʽ���ַ���
    \param[in] ...              ���������������и�ʽ�����Ʒ���������
    \retval    ��
    \attention ����ĺ��������ֻ��16���ַ�������ĸ�ʽ���ַ���(�����õ�����)�Ϊ159���ַ�(����������)
    \see DBG_LogEmerg, DBG_LogError, DBG_LogWarning, DBG_LogEvent, DBG_LogTrace
*/
/*lint -printf(6,DBG_Log)*/
void DBG_Log(OSP_U32 v_uiPid,
                 OSP_S32 v_iLogLevel,
                 const OSP_CHAR *v_pszFuncName,
                 OSP_S32 v_iLine,
                 OSP_U32 v_uiLogId,
                 const OSP_CHAR *v_pszFormat,
                 ...);

/****************************************************************************
���¼������DEBUG�����ṩ�Ľӿڽ����˷�װ�������������ԣ�
�����µ�DEBUGģ�����ǰ�ĵ��÷�ʽ���ݡ�
�������ڲ����ı仯��Ҫ������һ��ģ��� PID ��Ϊ���������Ϊ���ⷳ�������룬
Ҫ��ÿ��ʹ����Щ���Դ�ļ������ļ���ͷ���������:

MODULE_ID(__PID__);

���С�__PID__��Ϊ���ļ�������ģ��š�ִ�д������Ҫ���� "lvos.h" �� "lvos_macro.h"
******************************************************************************/
/** \brief ��¼�������������־
    \param[in] LogID  ��־���
    \param[in] ...    ��ʽ������ַ��������������������и�ʽ�����Ʒ���������
    \retval    ��
    \attention ����ĸ�ʽ���ַ���(�����õ�����)�Ϊ159���ַ�(����������)
*/
#define DBG_LogCritical(LogID,...)    \
    DBG_Log(MY_PID, DBG_LOG_EMERG,  \
        __FUNCTION__, __LINE__, \
        (LogID), __VA_ARGS__)
#define DBG_LogEmerg  DBG_LogCritical

/** \brief ��DBG_LOG_ERROR�����¼������Ϣ
    \param[in] LogID  ��־���
    \param[in] ...  ��ʽ������ַ��������������������и�ʽ�����Ʒ���������
    \retval    ��
    \attention ����ĸ�ʽ���ַ���(�����õ�����)�Ϊ159���ַ�(����������)
    \see DBG_Log()
*/
#define DBG_LogError(LogID, ...)                                               \
    DBG_Log(MY_PID, DBG_LOG_ERROR,  \
        __FUNCTION__, __LINE__, \
        (LogID), __VA_ARGS__)

/** \brief ��DBG_LOG_WARNING�����¼������Ϣ
    \param[in] LogID  ��־���
    \param[in] ...  ��ʽ������ַ��������������������и�ʽ�����Ʒ���������
    \retval    ��
    \attention ����ĸ�ʽ���ַ���(�����õ�����)�Ϊ159���ַ�(����������)
    \see DBG_Log()
*/
#define DBG_LogWarning(LogID, ...)   \
    DBG_Log(MY_PID, DBG_LOG_WARNING,  \
        __FUNCTION__, __LINE__,   \
        (LogID), __VA_ARGS__)

/** \brief ��DBG_LOG_EVENT�����¼������Ϣ
    \param[in] LogID  ��־���
    \param[in] ...  ��ʽ������ַ��������������������и�ʽ�����Ʒ���������
    \retval    ��
    \attention ����ĸ�ʽ���ַ���(�����õ�����)�Ϊ159���ַ�(����������)
    \see DBG_Log()
*/
#define DBG_LogInfo(LogID, ...)   \
    DBG_Log(MY_PID, DBG_LOG_EVENT,  \
        __FUNCTION__, __LINE__, \
        (LogID), __VA_ARGS__)
 #define DBG_LogEvent  DBG_LogInfo

/** \brief ��DBG_LOG_TRACE�����¼������Ϣ��ͬ\ref DBG_LogTrace������Ҫ������־ID��
    \param[in] ...  ��ʽ������ַ��������������������и�ʽ�����Ʒ���������
    \retval    ��
    \attention ����ĸ�ʽ���ַ���(�����õ�����)�Ϊ159���ַ�(����������)
    \see DBG_LogTrace
*/
#define DBG_LogDebug(LogID, ...)   \
    DBG_Log(MY_PID, DBG_LOG_TRACE,  \
        __FUNCTION__, __LINE__, \
        (LogID), __VA_ARGS__)
#define DBG_LogTrace DBG_LogDebug

#define DBG_LogIntf(level, logid, ...)  DBG_Log(MY_PID, level, __FUNCTION__, __LINE__, (OSP_U32)(logid), __VA_ARGS__)


enum tagOSP_DEBUG_LEVEL_E
{
    OSP_DBL_CRITICAL = 0,  /*�����������ָ�롢�Ƿ�������*/
    OSP_DBL_MAJOR,        /*���أ�����ϵͳ��Դ���㡢������·���ϣ�*/
    OSP_DBL_MINOR,       /*һ�㣨�������ʱ��*/
    OSP_DBL_INFO,          /*��Ϣ*/
    OSP_DBL_DATA,       /*�������Ӧ������*/
    OSP_DBL_ALL,        /*������������к������Լ�һ�����ϵĴ�����Ϣ*/
    OSP_DBL_BUTT
};


#define OSP_TRACE(pid, loglevel, ...)

#ifdef _DEBUG

#if defined(WIN32) /* Windows��ֱ��ʹ��Windows�����_ASSERT */
/** \brief ASSERT����, Linux����ֻ��¼
    \param[in] (���ʽ)  �����ж��桢�ٵı��ʽ
    \retval    ��
    \attention ����ĸ�ʽ���ַ���(�����õ�����)�Ϊ159���ַ�(����������)���ôʾ����_DEBUG������ʱ��Ч
    \see DBG_Log()
*/
#if defined(_PCLINT)  /* Windows Debugģʽ��PC-LINT��飬ֱ�Ӷ���  */
#define DBG_ASSERT(exp)
#define DBG_ASSERT_EXPR(expr, ...)
#define DBG_ASSERT_LIMIT(exp, interval, times)
#else
#define DBG_ASSERT(exp)     if (unlikely(!(exp))) \
                            { \
                                DBG_Log(MY_PID, DBG_LOG_EMERG, __FUNCTION__, __LINE__, 0, "Assert fail: (%s)", #exp); \
                            } \
                            _ASSERT(exp)

#define DBG_ASSERT_EXPR(expr, ...) \
            (void) ((!!(expr)) || \
                    (1 != _CrtDbgReport(_CRT_ASSERT, __FILE__, __LINE__, NULL, __VA_ARGS__)) || \
                    (_CrtDbgBreak(), 0))

#define DBG_ASSERT_LIMIT(exp, interval, times) DBG_ASSERT(exp)

#endif
#else

/** \brief ASSERT����, Linux����ֻ��¼
    \param[in] exp  �����ж��桢�ٵı��ʽ
    \retval    ��
    \attention ����ĸ�ʽ���ַ���(�����õ�����)�Ϊ159���ַ�(����������)���ôʾ����_DEBUG������ʱ��Ч
    \see DBG_Log()
*/
#define DBG_ASSERT(exp)     if (unlikely(!(exp))) \
                            {\
                                DBG_Log(MY_PID, DBG_LOG_EMERG, __FUNCTION__, __LINE__, 0, "Assert fail: (%s)", #exp); \
                                KDB_ENTER(); \
                                BUG(); \
                            }

#define DBG_ASSERT_EXPR(exp, ...)     if (unlikely(!(exp))) \
                            { \
                                DBG_Log(MY_PID, DBG_LOG_EMERG, __FUNCTION__, __LINE__, 0, __VA_ARGS__); \
                                KDB_ENTER(); \
                                BUG(); \
                            }

#define DBG_ASSERT_LIMIT(exp, interval, times) \
do \
{ \
    OSP_BOOL bCanPrint = FALSE; \
    if (unlikely(!(exp))) \
    { \
	    PRINT_LIMIT(DBG_LOG_ERROR, DBG_LOGID_BUTT, interval, times, bCanPrint); \
        if (TRUE == bCanPrint) \
        { \
		    DBG_Log(MY_PID, DBG_LOG_EMERG, __FUNCTION__, __LINE__, 0, "Assert fail: (%s)", #exp); \
            KDB_ENTER(); \
        } \
    } \
}while(0)

#endif /* WIN32 */

#else
/** \brief ASSERT����, Linux����ֻ��¼
    \param[in] exp  �����ж��桢�ٵı��ʽ
    \retval    ��
    \attention ����ĸ�ʽ���ַ���(�����õ�����)�Ϊ159���ַ�(����������)���ôʾ����_DEBUG������ʱ��Ч
    \see DBG_Log()
*/
#define DBG_ASSERT(exp)
#define DBG_ASSERT_EXPR(expr, ...)
#define DBG_ASSERT_LIMIT(exp, interval, times)

#endif  /* _DEBUG */

#define ASSERT(p) DBG_ASSERT(p)
#define ASSERT_LIMIT(exp, interval, times) DBG_ASSERT_LIMIT(exp, interval, times)

/* ����ͳһ�ı��ڱ��� */
#define DBG_LOGID_BUTT   0  /* ������ǰ�� */
#define NO_LOGID         0  /* ���������־û����־ID */
#define DBG_LOGID_NEW    0 /*HVS����δ������־ID*/
#ifdef WIN32
void DBG_SetWin32LogDir(OSP_CHAR *szDir);
#endif

/* ��ӡƵ�����ƹ��ܣ����ù����������ٿ�����Ż� */
#if defined(WIN32) || defined(_PCLINT_)
/* WIN32�²�֧��ʹ�øù��ܣ�����Ķ�����Ϊ��PC_lint��ͨ�� */
#define PRINT_LIMIT_PERIOD( level, logid, interval, burst, can)             \
do                                                                                              \
{                                                                                                \
    static int print_times = burst;                                                 \
    static int missed = 0;                                                              \
    if (0 < print_times)                                                                \
    {                                                                                           \
    (can) = TRUE;                                                                  \
        print_times--;                                                                   \
    }                                                                                           \
    else                                                                                      \
    {                                                                                           \
        (can) = FALSE;                                                                   \
        missed++;                                                                          \
        if (burst <= missed)                                                           \
        {                                                                                        \
            print_times = burst;                                                        \
            missed = 0;                                                                     \
        }                                                                                        \
    }                                                                                           \
}while(0)

#define PRINT_LIMIT( level, logid, interval, burst, can)                     \
do                                                                                              \
{                                                                                                \
    static int print_times = burst;                                                 \
    static int missed = 0;                                                              \
    if (0 < print_times)                                                                \
    {                                                                                           \
    (can) = TRUE;                                                                  \
        print_times--;                                                                   \
    }                                                                                           \
    else                                                                                      \
    {                                                                                           \
        (can) = FALSE;                                                                   \
        missed++;                                                                          \
        if (burst <= missed)                                                           \
        {                                                                                        \
            print_times = burst;                                                        \
            missed = 0;                                                                     \
        }                                                                                        \
    }                                                                                           \
}while(0)

#elif defined(__KERNEL__) 
/************************************************************************
 * ������: PRINT_LIMINT_PERIOD
 *
 * ����: �����ԵĴ�ӡƵ�ʿ��ƣ���һ�������ӡbusrt�Σ�
 *             ����ÿinterval��ʱ������ӡһ��
 *
 * �������: interval: ʱ�����ڳ���,ÿ��interval�ɴ�ӡһ��
 *                        burst: ��ʼ��ӡ����
 *
 * �������: can: ����ֵ��ʾ�Ƿ������ӡ
 *
 *************************************************************************/
#define PRINT_LIMIT_PERIOD( level, logid, interval, burst, can)                \
do                                                      \
{                                                       \
    /*ʹ�þ�̬���������������������*/  \
    static OSP_U64 ulMaxToks = (burst) * (interval);                    \
    static OSP_U64 ulToks = (burst) * (interval);                       \
    static OSP_U32 uiMissed = 0;                                    \
    static OSP_U64 ulLast = 0;                                  \
    OSP_U64 ulNow = jiffies;                                    \
                                                        \
    /*���µ�ǰ���*/                                    \
    ulToks += ulNow - ulLast;                                   \
    ulToks = (ulToks > ulMaxToks)?ulMaxToks:ulToks;                 \
    /*�����ǰ������ÿ�����ĵ�ʱ��*/          \
    if (ulToks >= (interval))                                   \
    {                                                       \
        if (uiMissed)                                           \
        {                                                   \
            DBG_LogIntf(level, logid,                           \
                    "%d messages suppressed. %s,line=%d.\n",     \
                    uiMissed,__FUNCTION__,__LINE__);          \
        }                                                   \
        /*�����ӡ��ͬʱ�������*/                  \
        ulToks -= (interval);                                       \
        uiMissed = 0;                                           \
        (can) = TRUE;                                           \
    }                                                       \
    else                                                    \
    {                                                       \
        uiMissed++;                                         \
        (can) = FALSE;                                          \
    }                                                       \
    /*������һ�δ�����ʱ��*/                        \
    ulLast = ulNow;                                         \
}while(0)

/************************************************************************
 * ������: PRINT_LIMIT
 *
 * ����: ��ӡƵ�ʿ��ƣ���ȴʱ�����intervalʱ
 *             �������ӡbusrt��
 *
 * �������: interval: ��ȴʱ��
 *                        burst: ÿ�οɴ�ӡ�Ĵ���
 *
 * �������: can: ����ֵ��ʾ�Ƿ������ӡ
 *
 *************************************************************************/
#define PRINT_LIMIT( level, logid, interval, burst, can)                       \
do                                                          \
{                                                           \
    static OSP_U32 uiPrinted = 0;                                   \
    static OSP_U32 uiMissed = 0;                                        \
    static OSP_ULONG ulLast = 0;                                      \
    OSP_ULONG ulNow = jiffies;                                        \
                                                            \
    /*������δ�����ʱ���������趨ʱ��*/           \
    if (time_after_eq(ulNow, ulLast + (interval)))                      \
    {                                                           \
        if (uiMissed)                                               \
        {                                                       \
            DBG_LogIntf(level, logid,                                    \
                    "%d messages suppressed.%s,line=%d.\n",         \
                    uiMissed,__FUNCTION__,__LINE__);              \
        }                                                       \
        /*��ӡ��������*/                                    \
        uiPrinted = 0;                                              \
        uiMissed = 0;                                               \
    }                                                           \
                                                            \
    /*��ӡ�������Ϊburst��*/                                    \
    if ((burst) > uiPrinted)                                            \
    {                                                           \
        uiPrinted++;                                                \
        (can) = TRUE;                                                    \
    }                                                           \
    else                                                        \
    {                                                           \
        uiMissed++;                                             \
        (can) = FALSE;                                          \
    }                                                           \
    /*������һ�δ�����ʱ��*/                            \
    ulLast = ulNow;                                                 \
}while(0)
#elif defined(__LINUX_USR__) 
#define PRINT_LIMIT_PERIOD( level, logid, interval, burst, can)           \
do                                                                                            \
{                                                                                              \
    (can) = TRUE;                                                                \
}while(0)

#define PRINT_LIMIT( level, logid, interval, burst, can)                   \
do                                                                                            \
{                                                                                              \
    (can) = TRUE;                                                                \
}while(0)

#endif



#endif

/** @} */


