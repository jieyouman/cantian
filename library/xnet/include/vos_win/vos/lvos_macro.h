/******************************************************************************

                  ��Ȩ���� (C) 2008-2008 ��Ϊ�������˿Ƽ����޹�˾

 ******************************************************************************
  �� �� ��   : lvos_macro.h
  �� �� ��   : ����
  ��    ��   : x00001559
  ��������   : 2008��7��8��
  ����޸�   :
  ��������   : һЩͨ�õĺ궨��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2008��7��8��
    ��    ��   : x00001559
    �޸�����   : �����ļ�

******************************************************************************/
/**
    \file  lvos_macro.h
    \brief һЩͨ�õĺ궨��

    \date 2008-08-19
*/

/** \addtogroup VOS_MACRO �����궨��
    @{ 
*/

#ifndef __LVOS_MACRO_H__
#define __LVOS_MACRO_H__

#ifndef KERNEL_VERSION
#define KERNEL_VERSION(a,b,c) (((a) << 16) + ((b) << 8) + (c))
#endif

#if defined(LINUX_VERSION_CODE) && LINUX_VERSION_CODE > KERNEL_VERSION(2,6,26)
#define __LINUX_VERSION_SUSE11__ 1
#define __LINUX_VERSION_SUSE10__ 1
#elif defined(LINUX_VERSION_CODE) && LINUX_VERSION_CODE > KERNEL_VERSION(2,6,5)
#define __LINUX_VERSION_SUSE10__ 1
#endif

#ifndef _WARN_FIXME
#define FIXME(desc)
#else
#ifdef WIN32
void __declspec(deprecated("must be fixed.")) FIXME(char *);
#else
void __attribute__((deprecated)) FIXME(char *);
#endif /* WIN32 */
#endif /* _WARN_FIXME */

#ifndef unlikely
#define unlikely(x) (x)
#endif

#ifndef likely
#define likely(x) (x)
#endif

#define LVOS_LITTLE_ENDIAN 0x1234
#define LVOS_BIG_ENDIAN    0x4321

#ifdef WIN32
    #if LITTLEENDIAN
        #define LVOS_BYTE_ORDER LVOS_LITTLE_ENDIAN
    #else
        #define LVOS_BYTE_ORDER LVOS_BIG_ENDIAN
    #endif
#elif defined(__KERNEL__)
    #if defined(__LITTLE_ENDIAN) && __LITTLE_ENDIAN
        #define LVOS_BYTE_ORDER LVOS_LITTLE_ENDIAN
    #else
        #define LVOS_BYTE_ORDER LVOS_BIG_ENDIAN
    #endif
#else
    #if __BYTE_ORDER == __LITTLE_ENDIAN
        #define LVOS_BYTE_ORDER LVOS_LITTLE_ENDIAN
    #else
        #define LVOS_BYTE_ORDER LVOS_BIG_ENDIAN
    #endif
#endif

/** \brief ����ṹ���Ա��С */
#define ST_MEMBER_SIZE(st, member) (sizeof(((st *)(0))->member))

/** \brief �ṹ���Ա������ʱ��������Ԫ�ظ��� */
#define ST_MEMBER_ARRAY_LEN(st, member) (ST_MEMBER_SIZE(st, member) / ST_MEMBER_SIZE(st, member[0]))

/** \brief ���ݽṹ��Ա��ַ�ҵ��ṹ�׵�ַ */
#ifndef container_of
#define container_of(ptr, type, member) \
    ((type *)(void *)((char *)(ptr) - offsetof(type, member)))
#endif

/** \brief ���������Ԫ�ظ��� */
#ifndef ARRAY_LEN
#define ARRAY_LEN(x) (sizeof(x) / sizeof((x)[0]))
#endif

/** \brief ȡ�������ϴ���� */
#ifndef MAX
#define MAX(x,y)  ((x) > (y) ? (x) : (y))
#endif

/** \brief ȡ��������С���� */
#ifndef MIN
#define MIN(x,y)  ((x) < (y) ? (x) : (y))
#endif

/* �������� align������2��n�η� */
#ifndef ROUND_UP
#define ROUND_UP(x, align)    (((x)+ (align) - 1) & ~((align) - 1))
#endif
#ifndef ROUND_DOWN
#define ROUND_DOWN(x, align)  ((x) & ~((align) - 1))
#endif

/** \brief δʹ�ò������� 
    \note  һЩ����ԭ��Ҫ��Ĳ�����ʵ�ʿ��ܲ�ʹ�ã���ʹ�õĲ���ʹ�ô˺궨������PC-Lint�ͱ���澯
*/
#ifndef UNREFERENCE_PARAM
#define UNREFERENCE_PARAM(x) ((void)(x))
#endif

#if defined(WIN32) || defined(_PCLINT_) || defined(__LINUX_USR__)


#define EXPORT_SYMBOL(x)
#define module_init(x)
#define module_exit(x)
#define MODULE_AUTHOR(x)
#define MODULE_LICENSE(x)
#define dump_stack()    /* pengshufeng 90003000. 2008/12/22 */

#ifndef __init
#define __init
#endif

#ifndef __exit
#define __exit
#endif

#ifndef __initdata
#define __initdata
#endif

#elif defined(__KERNEL__)
#else
#error "platform not specify"
#endif

/** \brief ����ģ��PID������\ref LVOS_Malloc, \ref DBG_LogError �Ƚӿ��Զ�������� */
#define MODULE_ID(x)        \
            static OSP_U32 MY_PID = (x)
#ifdef _PCLINT_
#define MODULE_NAME(x) int _pclint_module_name
#else
#define MODULE_NAME(x)
#endif

#ifndef MAX_PATH_NAME
#define MAX_PATH_NAME 256
#endif

/** \brief �ڲ�ʹ�õ����Ƴ��ȶ��� */
#define MAX_NAME_LEN 128
#define MAX_DESC_LEN 256

/** \brief ����IP��ַ�ַ�������󳤶� */
#define MAX_IP_STR_LEN      16
#define MAX_IPV6_STR_LEN    64

/** \brief �������ֵ�����ַ������ȣ� 2^64ֻ��20�ֽڳ���24�ֽ��㹻 */
#define MAX_NUMBER_STR_LEN  24

/* ����״̬--�� */
#define SWITCH_ON   1

/* ����״̬--�� */
#define SWITCH_OFF  0

/* ����ת�� */
#define BYTE_PER_SECTOR     (512)
#define BYTE_PER_PAGE       (4096)
#define SECTOR_PER_PAGE     (BYTE_PER_PAGE / BYTE_PER_SECTOR)

/** 
*   ֧��PI(Protection Information)��������ҳ���С����
*   PI������512�ֽ�����+8�ֽ�DIF(Data Integrity Field)���
*   PIҳ����8��PI�������
*
*   ������DIFʱ��DIF�ֽڱ��0����_NO_DIF_���ȫ�ֺ���ʶ��DIF����
*/
#ifdef _NO_DIF_
#define BYTES_PER_DIF          (0)
#else
#define BYTES_PER_DIF          (8)
#endif
#define BYTES_PER_SECTOR_PI    (BYTE_PER_SECTOR + BYTES_PER_DIF)
#define SECTORS_PER_PAGE_PI    (8)
#define BYTES_PER_PAGE_PI      (BYTES_PER_SECTOR_PI * SECTORS_PER_PAGE_PI)

#define BITS_PER_BYTE   8
#ifndef BITS_PER_LONG
#define BITS_PER_LONG   (BITS_PER_BYTE*sizeof(long))
#endif
#ifndef PAGE_SIZE
#define PAGE_SIZE       4096
#endif
#define SECTOR_SIZE     512
#define PAGE_SHIFT      12
#define SECTOR_SHIFT    9

#define KB_TO_SECTOR(x)   ((x)<<1)
#define PAGE_TO_SECTOR(x) ((x)<<3)
#define MB_TO_SECTOR(x)   ((x)<<11)
#define GB_TO_SECTOR(x)   ((x)<<21)

#define SECTOR_TO_KB(x)   ((x)>>1)
#define SECTOR_TO_PAGE(x) ((x)>>3)
#define SECTOR_TO_MB(x)   ((x)>>11)
#define SECTOR_TO_GB(x)   ((x)>>21)

#define TB_TO_GB(x) ((x)<<10)
#define TB_TO_MB(x) ((x)<<20)
#define GB_TO_MB(x) ((x)<<10)
#define GB_TO_KB(x) ((x)<<20)
#define MB_TO_KB(x) ((x)<<10)

#define KB_TO_MB(x) ((x)>>10)
#define KB_TO_GB(x) ((x)>>20)
#define MB_TO_GB(x) ((x)>>10)
#define MB_TO_TB(x) ((x)>>20)
#define GB_TO_TB(x) ((x)>>10)


/* �ж�ָ��Ϸ��Եĺ� */
#define POINTER_VALID(p) (NULL != (p))
#define POINTER_VALID2(p1, p2) (POINTER_VALID(p1) && POINTER_VALID(p2))
#define POINTER_VALID3(p1, p2, p3) (POINTER_VALID2(p1, p2) && POINTER_VALID(p3))
#define POINTER_VALID4(p1, p2, p3, p4) (POINTER_VALID3(p1, p2, p3) && POINTER_VALID(p4))
#define POINTER_VALID5(p1, p2, p3, p4, p5) (POINTER_VALID4(p1, p2, p3, p4) && POINTER_VALID(p5))


#endif  /* __LVOS_MACRO_H__ */

/** @} */

