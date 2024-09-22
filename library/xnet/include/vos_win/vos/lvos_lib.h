/******************************************************************************

                  ��Ȩ���� (C) 2008-2008 ��Ϊ�������˿Ƽ����޹�˾

 ******************************************************************************
  �� �� ��   : lvos_lib.h
  �� �� ��   : ����
  ��    ��   : x00001559
  ��������   : 2008��8��19��
  ����޸�   :
  ��������   : �Ա�����������ϵͳ���ṩ�Ŀ⺯�������䡣
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2008��8��19��
    ��    ��   : x00001559
    �޸�����   : �����ļ�

******************************************************************************/

/**
    \file  lvos_lib.h
    \brief �������������кͶ�̬����صĺ���֧��windows��linux�û�̬������֧��windows��linux�ں�̬��linux�û�̬

    \date 2008-08-19
*/

/** \addtogroup VOS_LIB  ����⺯��
    ���ڱ�׼�⺯��: memcpy, memset, strcpy, strcmp, sprintf, snprintf ֱ��ʹ�ÿ⺯��ԭ�ͣ��ӿڲ㲻�ٷ�װ(ͷ�ļ��ڽӿڲ�ͷ�ļ����Ѿ�����)
    @{ 
*/

#ifndef __LVOS_LIB_H__
#define __LVOS_LIB_H__

#if defined(WIN32) || defined(_PCLINT_)

/* VC�±���ʱʹ��VC����ĺ��� */
#define snprintf    _snprintf
#define vsnprintf   _vsnprintf
#define filelength  _filelength
#define chsize      _chsize
#define fileno      _fileno
#define stricmp     _stricmp
#define strnicmp     _strnicmp
#define ftruncate   _chsize
#define unlink      _unlink
#define strncasecmp  _strnicmp
static inline unsigned int copy_from_user(void *dst, const void *src, unsigned int size)
{
    memcpy(dst, src, size);
    return 0;
}
static inline unsigned int copy_to_user(void *dst, const void *src, unsigned int size)
{
    memcpy(dst, src, size);
    return 0;
}







#elif defined(__KERNEL__) /* Linux�ں�̬  */
#include <linux/math64.h>

/* ��������Ϊ4096������Ժ��и��������޸� */
#define stricmp(s1, s2) strnicmp(s1 ,s2, 4096)


#elif defined(__LINUX_USR__) /* Linux�û�̬  */

typedef void* HMODULE;  /* ����װ�ض�̬��ʱ���صľ������ */
typedef void* FARPROC;

#define stricmp strcasecmp
#define strnicmp strncasecmp

/** \brief װ�ض�̬��
    \note  ֧��windows��linux�û�̬
    \param[in] v_szLibPathName ��̬���·��������
    \return �򿪵Ķ�̬��ľ����װ��ʧ��ʱ����Ϊ NULL
*/
HMODULE LVOS_LoadLibrary(const OSP_CHAR *v_szLibPathName);

/** \brief ��ѯ��̬���еķ��ŵ�ַ
    \note  ֧��windows��linux�û�̬
    \param[in] v_hModule ָ��򿪵Ķ�̬��ľ��
    \param[in] v_szSymbolName   ��Ҫ��ѯ�ķ�������
    \return ָ��÷��ŵ�ָ�룬�����ѯʧ�ܣ��򷵻�NULL
*/
FARPROC LVOS_GetSymbolAddress(HMODULE v_hModule, const OSP_CHAR *v_szSymbolName);

/** \brief ��ѯ��̬���еķ��ŵ�ַ
    \note  ֧��windows��linux�û�̬
    \param[in] v_hModule ָ��򿪵Ķ�̬��ľ��
    \retval RETURN_OK       �رճɹ�
    \retval RETURN_ERROR    �ر�ʧ��
*/
OSP_S32 LVOS_FreeLibrary(HMODULE v_hModule);

#endif


#ifndef memzero
#define memzero(s,n)    memset ((s),0,(n))
#endif

/* Ϊ�˼���32Ϊ�ں˵�Linux�ں�̬��������64λ�������� */
/** \brief 64λ��������
    \note  ֧��windows��linux�û�̬��linux�ں�̬
    \param[in] n       ������
    \param[in] base    ����
    \param[out] puiMod ָ������ֵ��ָ��
    \retval ��
*/
static inline OSP_U64 LVOS_div64(OSP_U64 n, OSP_U32 base, OSP_U32 *puiMod)
{
#if !defined(__KERNEL__) || defined(_PCLINT_)
    if (NULL != puiMod)
    {
        *puiMod = (OSP_U32)(n % base);
    }

    return (OSP_U64)(n / base);

#else /* �ں�̬ */
    OSP_U32 uiMod;

    if (NULL == puiMod)
    {
        return div_u64_rem(n, base, &uiMod);
    }
    else
    {
        return div_u64_rem(n, base, puiMod);
    }
#endif
}

static inline OSP_U64 UnSignedDivide64(OSP_U64  v_ullDvidend, OSP_U64  v_ullDivisor)
{
#if !defined(__KERNEL__) || defined(_PCLINT_)
    return v_ullDvidend / v_ullDivisor;
#else /* �ں�̬ */
    return div64_u64(v_ullDvidend, v_ullDivisor);
#endif
}

static inline OSP_U64 UnSignedRemain64(OSP_U64  v_ullDvidend, OSP_U64  v_ullDivisor)
{
#if !defined(__KERNEL__) || defined(_PCLINT_)
        return v_ullDvidend % v_ullDivisor;
#else /* �ں�̬ */
    #ifdef __x86_64__
        return v_ullDvidend % v_ullDivisor;

    #else
        return v_ullDvidend - v_ullDivisor * div64_u64(v_ullDvidend, v_ullDivisor);
    #endif
#endif
}

/** \brief strncpy����������β����0�Ĺ��� */
#define LVOS_strncpy(s1, s2, n) do { \
    /* s1����Ϊָ��������飬������ʱ���뱣֤��С >= n ���ߵ���0 */ \
    DBG_ASSERT((sizeof(s1) == 0) || (sizeof(s1) == sizeof(void *)) || (sizeof(s1) >= (n))); \
    strncpy((s1), (s2), (n)); \
    ((char *)(s1))[(n) - 1] = '\0'; \
 } while(0)

/** \brief �ַ���תS64
    \note  ֧��windows��linux�û�̬��linux�ں�̬
    \param[in] szStr ��Ҫת�����ַ���
    \return �ɹ�ʱ����ת�������szStrΪNULL����0�����򷵻���ת���Ĳ���
    \note ��֧��ʮ���ƣ��޵�������������
    \see  LVOS_StrToU64
*/
OSP_S64 LVOS_StrToS64(const OSP_CHAR *szStr);

/** \brief �ַ���תU64
    \param[in] szStr ��Ҫת�����ַ���
    \return �ɹ�ʱ����ת�������szStrΪNULL����0�����򷵻���ת���Ĳ���
    \note ֧��ʮ���ƺ�ʮ�����ƣ��޵�������������
    \see  LVOS_StrToS64
*/
OSP_U64 LVOS_StrToU64(const OSP_CHAR *szStr);

/** \brief �ַ���תСд�ַ�
    \param[in] v_pszStr ��Ҫת�����ַ���
*/
void LVOS_StrToLower(OSP_CHAR *v_pszStr);

/** \brief �ж��Ƿ����޷�������
    \retval RETURN_OK ��
    \retval RETURN_ERROR  ����
*/
OSP_S32 LVOS_IsUnsignedNumbericStr(const OSP_CHAR *v_szStr);

/** 
    \brief ִ��ϵͳ����
    \param[in] v_szCommand ��Ҫִ�е�����
    \retval  0    ִ�гɹ�
    \retval  ���� ִ��ʧ��
*/
OSP_S32 LVOS_Execute(const OSP_CHAR*v_szCommand);

#ifdef WIN32 /* �ں˺�Linux�û�̬�����������ֱ�������õ� */
char *strsep(char **s, const char *ct);
#endif

#endif /* __LVOS_LIB_H__ */
/** @} */


