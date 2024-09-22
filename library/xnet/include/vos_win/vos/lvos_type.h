/******************************************************************************

                  ��Ȩ���� (C), 2008-2010, ��Ϊ�������˿Ƽ����޹�˾

 ******************************************************************************
  �� �� ��   : lvos_type.h
  �� �� ��   : ����

  ��������   : 2008��6��3��
  ����޸�   :
  ��������   : ���Ͷ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2008��6��3��

    �޸�����   : �����ļ�

******************************************************************************/
/**
    \file  lvos_type.h
    \brief �������Ͷ���
    \date 2008-12-19
*/

/** \addtogroup VOS_TYPES ���Ͷ���
    @{ 
*/


#ifndef __LVOS_TYPE_H__
#define __LVOS_TYPE_H__


#ifndef inline
#define inline __inline
#endif

#ifndef __inline__
#define __inline__ inline
#endif

#if defined(WIN32) || defined(_PCLINT_)

#ifndef __cplusplus
typedef int bool;
#endif

typedef char    int8_t;
typedef short   int16_t;
typedef int     int32_t;
typedef __int64 int64_t;

typedef unsigned char    uint8_t;
typedef unsigned short   uint16_t;
typedef unsigned int     uint32_t;
typedef unsigned __int64 uint64_t;
#endif


/* OSP��ʼ���Ǽ����Զ��壬������Ҫʹ�� */
#ifndef _OSP_TYPES_
#define _OSP_TYPES_

typedef void            OSP_VOID;  /**< \brief OSP_VOID���Ͷ��� */
typedef  int            OSP_BOOL;  /**< \brief OSP_BOOL���Ͷ��� */
typedef unsigned long   OSP_ULONG; /**< \brief OSP_ULONG���Ͷ���\n  Linux, ��32λ����32λ����64λ����64λ\n Windows 32��64λ��������32λ  */
typedef long            OSP_LONG;  /**< \brief OSP_LONG���Ͷ���\n  Linux, ��32λ����32λ����64λ����64λ\n Windows 32��64λ��������32λ  */
typedef char            OSP_CHAR;  /**< \brief OSP_CHAR���Ͷ��� */


typedef int8_t   OSP_S8;
typedef int16_t  OSP_S16;
typedef int32_t  OSP_S32;
typedef int64_t  OSP_S64;

typedef uint8_t   OSP_U8;
typedef uint16_t  OSP_U16;
typedef uint32_t  OSP_U32;
typedef uint64_t  OSP_U64;

#endif

/* ��ʽ����ӡǰ׺ */
#if defined(WIN32) || defined(__KERNEL__)

#ifdef WIN32
#define __PRI64_PREFIX        "ll"
#else
#define __PRI64_PREFIX        "l"
#endif

#define PRIi64         __PRI64_PREFIX "i"
#define PRIu64         __PRI64_PREFIX "u"
#define PRIx64         __PRI64_PREFIX "x"
#define PRIX64         __PRI64_PREFIX "X"

#endif

typedef size_t    OSP_SIZE_T;

#ifdef _PCLINT_
#ifdef ESTOR_X64
#define ptrdiff_t long long
typedef long long OSP_PTR_DIFF;
#else
#define ptrdiff_t long
typedef long OSP_PTR_DIFF;
#endif
#else
#ifdef ESTOR_X64
#define ptrdiff_t long long
typedef ptrdiff_t OSP_PTR_DIFF;
#else
typedef ptrdiff_t OSP_PTR_DIFF;
#endif
#endif

/** \brief �ڵ� ���Ͷ���
      \code
      \endcode
*/
typedef uint16_t nid_t;       /* �ڵ�����ͣ���: ��� */
typedef uint16_t moduleid_t;  /* ģ�� PID���ڵ����� */

#ifndef INVALID_NID
#define INVALID_NID 0xFFFF  /*��Ч�Ľڵ�ID*/
#endif

/* ����SOCKET������Windows��Linux�û�̬�Լ�Linux�ں�̬���룬���ǵ�socket���������岻һ�� */
#if defined(WIN32) || defined(_PCLINT_)
#elif defined(__LINUX_USR__)
typedef int SOCKET;
#define INVALID_SOCKET  (-1)
#elif defined(__KERNEL__)
typedef int SOCKET;
#define INVALID_SOCKET  (-1)
#else
#error "platform not specify"
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef B_TRUE
#define B_TRUE 1
#endif

#ifndef B_FALSE
#define B_FALSE 0
#endif

#ifndef INVALID_VALUE64
#define INVALID_VALUE64     0xFFFFFFFFFFFFFFFFULL
#endif

#ifndef INVALID_VALUE_ULONG
#define INVALID_VALUE_ULONG ((OSP_ULONG)(-1))
#endif

#ifndef INVALID_VALUE32
#define INVALID_VALUE32     0xFFFFFFFF
#endif

#ifndef INVALID_VALUE16
#define INVALID_VALUE16     0xFFFF
#endif

#ifndef INVALID_VALUE8
#define INVALID_VALUE8      0xFF
#endif

#if !defined(__KERNEL__) || defined(_PCLINT_)
#define __user
#endif

#endif /* __LVOS_TYPE_H__  */

/** @} */

