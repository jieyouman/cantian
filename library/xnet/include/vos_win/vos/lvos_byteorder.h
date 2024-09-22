/******************************************************************************

                  ��Ȩ���� (C) 2008-2008 ��Ϊ�������˿Ƽ����޹�˾

 ******************************************************************************
  �� �� ��   : byteorder.h
  �� �� ��   : ����
  ��    ��   : x00001559
  ��������   : 2008��7��26��
  ����޸�   :
  ��������   : �����ֽ���ת���Ĺ���
  �޸���ʷ   :
  1.��    ��   : 2008��7��26��
    ��    ��   : x00001559
    �޸�����   : �����ļ�

******************************************************************************/
/**
    \file  lvos_byteorder.h
    \brief �ֽ���ת������ӿ�

    \date 2008-07-26
*/


/** \addtogroup VOS_BYTEORDER  �ֽ���ת��
    @{ 
*/

#ifndef __BYTEORDER_H__
#define __BYTEORDER_H__

#ifdef __LINUX_USR__
//#include <byteswap.h>
#endif

/** \brief 16λ������CPU��ת����С��
    \param[in] usData  ��Ҫת��������
    \return ת���������
    \see CpuToLittleEndian32  CpuToLittleEndian64
*/
OSP_U16 CpuToLittleEndian16(OSP_U16 usData);

/** \brief 32λ������CPU��ת����С��
    \param[in] usData  ��Ҫת��������
    \return ת���������
    \see CpuToLittleEndian16  CpuToLittleEndian64
*/
OSP_U32 CpuToLittleEndian32(OSP_U32 usData);

/** \brief 64λ������CPU��ת����С��
    \param[in] ulData  ��Ҫת��������
    \return ת���������
    \see CpuToLittleEndian16  CpuToLittleEndian32
*/
OSP_U64 CpuToLittleEndian64(OSP_U64 ulData);

/** \brief 16λ������CPU��ת��������
    \param[in] usData  ��Ҫת��������
    \return ת���������
    \see CpuToBigEndian32  CpuToBigEndian64
*/
OSP_U16 CpuToBigEndian16(OSP_U16 usData);

/** \brief 32λ������CPU��ת��������
    \param[in] usData  ��Ҫת��������
    \return ת���������
    \see CpuToBigEndian16  CpuToBigEndian64
*/
OSP_U32 CpuToBigEndian32(OSP_U32 usData);

/** \brief 64λ������CPU��ת��������
    \param[in] ulData  ��Ҫת��������
    \return ת���������
    \see CpuToBigEndian16  CpuToBigEndian32
*/
OSP_U64 CpuToBigEndian64(OSP_U64 ulData);

/** \brief 16λ������С��ת����CPU��
    \param[in] usData  ��Ҫת��������
    \return ת���������
    \see LittleEndianToCpu32  LittleEndianToCpu64
*/
OSP_U16 LittleEndianToCpu16(OSP_U16 usData);

/** \brief 32λ������С��ת����CPU��
    \param[in] usData  ��Ҫת��������
    \return ת���������
    \see LittleEndianToCpu32  LittleEndianToCpu64
*/
OSP_U32 LittleEndianToCpu32(OSP_U32 usData);

/** \brief 64λ������С��ת����CPU��
    \param[in] ulData  ��Ҫת��������
    \return ת���������
    \see LittleEndianToCpu32  LittleEndianToCpu64
*/
OSP_U64 LittleEndianToCpu64(OSP_U64 ulData);

/** \brief 16λ������CPU��ת��������
    \param[in] usData  ��Ҫת��������
    \return ת���������
    \see BigEndianToCpu32  BigEndianToCpu64
*/
OSP_U16 BigEndianToCpu16(OSP_U16 usData);

/** \brief 32λ������CPU��ת��������
    \param[in] usData  ��Ҫת��������
    \return ת���������
    \see BigEndianToCpu16  BigEndianToCpu64
*/
OSP_U32 BigEndianToCpu32(OSP_U32 usData);

/** \brief 64λ������CPU��ת��������
    \param[in] ulData  ��Ҫת��������
    \return ת���������
    \see BigEndianToCpu16  BigEndianToCpu32
*/
OSP_U64 BigEndianToCpu64(OSP_U64 ulData);

#endif
/** @} */

