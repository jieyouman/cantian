/******************************************************************************

                  ��Ȩ���� (C) 2008-2008 ��Ϊ�������˿Ƽ����޹�˾

 ******************************************************************************
  �� �� ��   : lvos_time.h
  �� �� ��   : ����
  
  ��������   : 2008��7��8��
  ����޸�   :
  ��������   : ʱ�书��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2008��7��8��
    
    �޸�����   : �����ļ�

******************************************************************************/

/**
    \file  lvos_time.h
    \brief ʱ�书��

    \date 2008-12-24
*/

/** \addtogroup VOS_TIME  ʱ����ӿ�
    @{ 
*/

#ifndef __LVOS_TIME_H__
#define __LVOS_TIME_H__

#define MAX_DATE_TIME            20

/** \brief ʱ��ṹ�� */
typedef struct 
{
    OSP_S32 iYear;          /**< ��, 1999����Ϊ1999 */ 
    OSP_S32 iMonth;       /**< ��, 1-12*/
    OSP_S32 iMDay;        /**< ��, 1-31 */
    OSP_S32 iHour;         /**< ʱ, 0-23 */
    OSP_S32 iMinute;     /**< ��, 0-59 */
    OSP_S32 iSecond;     /**< ��, 0-59 */
    OSP_S32 iWDay;      /**< ����, 0-6:��~�� */
} TIME_S;

/** \brief ȡ�õ�ǰ�ı���ʱ�䣬��1970-1-1 00:00:00 ��ʼ����������
    \note  ֧��windows/linux_kernel/linux_user���޵�������������
    \param[in] llUtcTime  ����UTC time
    \return OSP_S64 ����localʱ��
*/
OSP_S64 LVOS_GetLocalTimeFromUtcTime(OSP_S64 llUtcTime);

/** \brief ȡ�õ�ǰ�ı���ʱ�䣬��1970-1-1 00:00:00 ��ʼ����������
    \note  ֧��windows/linux_kernel/linux_user���޵�������������
    \param[in] piTime  ����ʱ�䣬ΪNULLʱ������
    \return OSP_S64 ����ʱ��
*/
OSP_S64 LVOS_GetLocalTime(OSP_S64 *piTime);


/** \brief ȡ�õ�ǰ�ı�������ʱʱ�䣬��1970-1-1 00:00:00 ��ʼ����������
    \note  
    \param[in] v_pllTime  ����ʱ�䣬ΪNULLʱ������
    \return OSP_S32   �ɹ�:RETURN_OK ;  ʧ��:RETURN_ERROR
*/
OSP_S32 LVOS_GetDSTTime(OSP_S64 *v_pllTime);

/** \brief ���ݴ����UTC ʱ���ȡ����ʱʱ�䣬��1970-1-1 00:00:00 ��ʼ����������
    \note  
    \param[in] 
    \return OSP_S64   ����ʱ��,�������0��ʾ��ȡʧ��
*/
OSP_S64 LVOS_GetDSTTimeFromUtcTime(OSP_S64 llUtcTime);



/** \brief ��ѯʱ���Ƿ�������ʱ����
           ֧�����֣�1����ѯϵͳʱ�䣻2����ѯ����utcʱ�䣻
    \note  
    \param[in]  OSP_U32 uiFlag ��ѯ��־��0����ѯϵͳʱ�䣬��������ѯ����ʱ��
                OSP_S64 llUtcTime             �����UTCʱ�䣬��ѯϵͳʱ��ʱ����0
    \return OSP_S64   RETURN_OK       ʱ��������ʱ����
                                RETURN_ERROR ʱ�䲻������ʱ����
*/
OSP_S32 LVOS_CheckIsDSTTime(OSP_U32 uiFlag,OSP_S64 llUtcTime);


/** \brief ȡ�õ�ǰ��ʱ�䣬��1970-1-1 00:00:00 ��ʼ����������
    \note  ֧��windows/linux_kernel/linux_user���޵�������������
    \param[in] piTime  ����ʱ�䣬ΪNULLʱ������
    \return OSP_S64 ����ʱ��
*/
OSP_S64 LVOS_GetTime(OSP_S64 *piTime);

/*lint -sem(TIME_GmTime, 2p) */
/** \brief ��ʽ��ʱ��Ϊ�ꡢ�¡��ա�ʱ���֡����ʽ
    \note  ֧��windows/linux_kernel/linux_user���޵�������������
    \param[in]  piTime   ��Ҫ��ʽ����ʱ�䣬ΪNULLʱ��ʾȡ��ǰʱ��
    \param[out] pstTime  ��ʽ����Ĵ���ʱ��
    \return ��
*/
void LVOS_GmTime(const OSP_S64 *piTime, TIME_S *pstTime);

/*lint -sem(LVOS_mkTime, 1p) */
/** \brief ���ꡢ�¡��ա�ʱ���֡����ʽ��ʱ��ת��Ϊ����
    \param[in]  pstTime  ��Ҫת����ʱ��
    \return ת�����ʱ��
*/
OSP_S64 LVOS_mkTime(TIME_S *pstTime);

/*lint -sem(TIME_AscTime, 3n > 24 && 3n <= 2P) */
/** \brief �����ַ�����ʽ��ʱ��
    \note  ֧��windows/linux_kernel/linux_user���޵�������������
    \param[in] piTime  ������Ҫת����ʱ��ֵ�����ΪNULL��ת����ǰʱ��
    \param[in] szBuffer  �ַ�������ռ�
    \param[in] uiBufferSize �ַ��������С
    \return ��
*/
void LVOS_AscTime(const OSP_S64 *piTime, OSP_CHAR *szBuffer, OSP_U32 uiBufferSize);

/** \brief ��ȡϵͳ�����󾭹��ĺ�����
    \note  ֧��windows/linux_kernel/linux_user��ͬ���ӿڣ��޵�������������
    \return ϵͳ�����󾭹��ĺ�����
*/
OSP_U64 LVOS_GetMilliSecond(void);

#ifdef WIN32
__declspec(deprecated("This function will be deleted for future, please use 'LVOS_GetMilliSecond' instead."))
#endif
static inline OSP_U32 LVOS_GetTickCount(void)
{
    return (OSP_U32)LVOS_GetMilliSecond();
}

/** \brief ��ȡϵͳ�����󾭹���������
    \note  ֧��windows/linux_kernel��ͬ���ӿڣ��޵�������������
    \return ��ȡϵͳ�����󾭹���������
*/
OSP_U64 LVOS_GetNanoSecond(void);

/** \brief ��ѯϵͳʱ��(windows��ֱ�ӷ���OK)
    \note  ֻ֧��linux�û�̬
    \param[in]  ���ֱ�ʾ��ʽ��ʱ����Ϣ
    \retval RETURN_OK       ��ѯ�ɹ�
    \retval RETURN_ERROR    ��ѯʧ��
*/
OSP_S32 LVOS_GetTimeZone(OSP_CHAR *pTimeZoneUTC,OSP_CHAR *pTimeZoneName,OSP_CHAR *pTimeZoneStyle);

/** \brief ����ϵͳʱ��(windows��ֱ�ӷ���OK)
    \note  ֻ֧��linux�û�̬
    \param[in] OSP_CHAR *ʱ�������ַ���
    \retval RETURN_OK       ���óɹ�
    \retval RETURN_ERROR    ����ʧ��
*/
OSP_S32 LVOS_SetTimeZone(OSP_CHAR *pTimeZoneName);

/** \brief ��ѯ������������Ƿ�ʹ��������ʱ(windows��ֱ�ӷ���OK)
    \note  ֻ֧��linux�û�̬
    \param[in]  OSP_CHAR * ����ʱ��ʼʱ��
                OSP_CHAR * ����ʱ�� ƫ��ʱ��
                OSP_U32 *  ƫ��ʱ��
    \retval RETURN_OK       ��ѯ�ɹ�
    \retval RETURN_ERROR    ��ѯʧ��
*/
OSP_S32 LVOS_QueryDstConfInfo(OSP_CHAR *pDstBegin,
                              OSP_CHAR *pDstEnd,OSP_U32 *DstMinOffset,OSP_U32 *DstConfMod);



OSP_S32 LVOS_QueryDstConfInfoForRegion(OSP_CHAR *pTimeZoneName, OSP_CHAR *pDstBegin,
                              OSP_CHAR *pDstEnd,OSP_U32 *DstMinOffset,OSP_U32 *DstConfMod);


OSP_S32 LVOS_QueryDstForRegion(OSP_CHAR *pTimeZoneName,OSP_U32 *pFlag);

/** \brief ����UTCʱ��(windows��ֱ�ӷ���OK)
    \note  ֻ֧��linux�û�̬
    \param[in] const OSP_S64 *����Ϊ��λ��UTCʱ��
    \retval RETURN_OK       ���óɹ�
    \retval RETURN_ERROR    ����ʧ��
*/
OSP_S32  LVOS_SetTime(const OSP_S64 *v_pllTime);

#endif
/** @} */

