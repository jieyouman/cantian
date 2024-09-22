/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������˿Ƽ����޹�˾

 ******************************************************************************
  �� �� ��   : lvos_mem.h
  �� �� ��   : ����

  ��������   : 2008��11��13��
  ����޸�   :
  ��������   : �ڴ�����ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2008��11��13��

    �޸�����   : �����ļ�

******************************************************************************/

/**
    \file  lvos_mem.h
    \brief ����ϵͳ�ڴ����ӿڷ�װ
    \note  ֧��windows/linux_kernel/linux_user

    \date 2008-05-27
*/

/** \addtogroup MEM  �ڴ����ģ��
    ����ϵͳ�ڴ����ӿڷ�װ
    @{ 
*/
#ifndef _LVOS_MEM_H__
#define _LVOS_MEM_H__

#if defined(__KERNEL__) && !defined(_PCLINT_)
    #define MEM_FUN_CALLER (OSP_U64)__builtin_return_address(0)
#else
    #define MEM_FUN_CALLER (OSP_U64)NULL
#endif

#if defined(__KERNEL__)
#ifdef _PCLINT_
#define GFP_ATOMIC 0
#endif

#define LVOS_MallocSub(pid, v_uiByte, MEM_FUN_CALLER) \
    LVOS_MallocSubStandard(pid, v_uiByte, MEM_FUN_CALLER,__FUNCTION__, __LINE__)
/** \brief windows��linux�ں�̬��linux�û�̬ͳһ���ڴ�����
    \param[in] v_uiByte ��Ҫ������ڴ泤��
    \return ����ʧ��ʱ����NULL, �ɹ�ʱ�������뵽���ڴ��ַ
    \note �벻Ҫֱ��ʹ�ú���\ref LVOS_MallocSub���롣���������ÿ��ܵ��µ���������
    \see  LVOS_MallocGfp, LVOS_Free
*/
#define LVOS_Malloc(v_uiByte) LVOS_MallocSub(MY_PID, v_uiByte, MEM_FUN_CALLER)

/** \brief linux�ں�̬GFP��ʽ���ڴ����룬windows��linux�û�ֱ̬��ʹ����LVOS_Malloc��ʽ����
    \param[in] v_uiByte     ��Ҫ������ڴ泤��
    \param[in] v_uiGfpMask  ���뷽ʽ
    \return ����ʧ��ʱ����NULL, �ɹ�ʱ�������뵽���ڴ��ַ
    \note �벻Ҫֱ��ʹ�ú���\ref LVOS_MallocGfpSub ���롣�����������з�GFP_ATOMIC��ʽ���ܵ��µ���������
    \see  LVOS_Malloc, LVOS_Free
*/
#define LVOS_MallocGfp(v_uiByte, v_uiGfpMask) \
    LVOS_MallocGfpSub(MY_PID, v_uiByte, v_uiGfpMask, MEM_FUN_CALLER)

/** \brief windows��linux�ں�̬��linux�û�̬ͳһ���ڴ��ͷ�
    \param[in] v_ptr ��Ҫ�ͷŵ��ڴ��׵�ַ
    \return ����ʧ��ʱ����NULL, �ɹ�ʱ�������뵽���ڴ��ַ
    \note �벻Ҫֱ��ʹ�ú���\ref LVOS_MallocSub���롣�����������޵�������������
    \see  LVOS_Malloc, LVOS_MallocGfp
*/
#define LVOS_Free(v_ptr)            \
    {                               \
        LVOS_FreeSub(v_ptr, __FUNCTION__, __LINE__);  \
        v_ptr = NULL;               \
    }


/* ����Ľӿڲ����⿪�ţ������궨��ʹ�� */
/*lint -function(realloc(0), LVOS_MallocSubStandard) */
/*lint -function(malloc(1), LVOS_MallocSubStandard(2)) */
/*lint -function(malloc(r), LVOS_MallocSubStandard(r)) */
/** \brief windows��linux�ں�̬��linux�û�̬ͳһ���ڴ��ͷ�
    \param[in] v_uiPid �����ڴ��ģ��PID
    \param[in] v_uiByte �����ڴ�Ĵ�С
    \param[in] v_pcFunction �����ڴ�ĺ�����   
    \param[in] v_uiLine �����ڴ���к�
    \return ����ʧ��ʱ����NULL, �ɹ�ʱ�������뵽���ڴ��ַ
*/
OSP_VOID *LVOS_MallocSubStandard(OSP_U32 v_uiPid, OSP_U32 v_uiByte, OSP_U64 v_ulCaller, 
                       OSP_CHAR const *v_pcFunction, OSP_U32 v_uiLine);


/*lint -function(realloc(0), LVOS_MallocGfpSub) */
/*lint -function(malloc(1), LVOS_MallocGfpSub(2)) */
/*lint -function(malloc(r), LVOS_MallocGfpSub(r)) */
/** \brief linux�ں�̬��������ʽ�����ڴ�
    \param[in] v_uiPid �����ڴ��ģ��PID
    \param[in] v_uiByte �����ڴ�Ĵ�С
    \param[in] v_uiGfpMask �ڴ����뷽ʽ
    \param[in] v_pcFunction �����ڴ�ĺ�����   
    \param[in] v_uiLine �����ڴ���к�
    \return ����ʧ��ʱ����NULL, �ɹ�ʱ�������뵽���ڴ��ַ
*/
void *LVOS_MallocGfpSub(OSP_U32 v_uiPid, OSP_U32 v_uiByte, OSP_U32 v_uiGfpMask, OSP_U64 v_ulCaller);

/*lint -function(free, LVOS_FreeSub) */
void LVOS_FreeSub(void *v_ptr, 
    OSP_CHAR const *v_pcFunction, OSP_U32 v_uiLine);
#elif defined(__LINUX_USR__)
#define LVOS_MallocSub(pid, v_uiByte, MEM_FUN_CALLER) \
    LVOS_MallocSubStandard(pid, v_uiByte, MEM_FUN_CALLER,__FUNCTION__, __LINE__)
#define LVOS_Malloc(v_uiByte)  LVOS_MallocSub(MY_PID, v_uiByte, MEM_FUN_CALLER)
#define LVOS_MallocGfp(v_uiByte, v_uiGfpMask) malloc(v_uiByte)
#define LVOS_Free(v_ptr)         \
    {                            \
        LVOS_FreeSub(v_ptr, __FUNCTION__, __LINE__);            \
        v_ptr = NULL;            \
    }
OSP_VOID *LVOS_MallocSubStandard(OSP_U32 v_uiPid, OSP_U32 v_uiByte, OSP_U64 v_ulCaller, 
                       OSP_CHAR const *v_pcFunction, OSP_U32 v_uiLine);
void LVOS_FreeSub(void *v_ptr, 
    OSP_CHAR const *v_pcFunction, OSP_U32 v_uiLine);

#else
#define LVOS_Malloc(v_uiByte)  malloc(v_uiByte)
#define LVOS_MallocGfp(v_uiByte, v_uiGfpMask) malloc(v_uiByte)
#define LVOS_Free(v_ptr)         \
    {                            \
        free(v_ptr);             \
        v_ptr = NULL;            \
    }

#ifndef PCLINT_VOS_MEM
#define LVOS_MallocSub(v_uiPid, v_uiByte, v_ulCaller)  malloc(v_uiByte),(void)(v_ulCaller), (void)(v_uiPid)
#endif

#endif /* __KERNEL__ */

/* ���������Ĵ���pid�ķ�ʽ�Ķ��� */
#ifdef DECLARE_FOR_DRV_COMPAT
#undef LVOS_Malloc
#undef LVOS_MallocGfp
#if defined(__KERNEL__)
#define LVOS_Malloc(pid, size)  LVOS_MallocSub(pid, size, MEM_FUN_CALLER)
#define LVOS_MallocGfp(pid, size, gfp) LVOS_MallocGfpSub(pid, size, gfp, MEM_FUN_CALLER)
#elif defined(__LINUX_USR__)
#define LVOS_Malloc(pid, size)  LVOS_MallocSub(pid, size, MEM_FUN_CALLER)
#define LVOS_MallocGfp(pid, size, gfp) malloc(size)
#else
#define LVOS_Malloc(pid, size)  malloc(size)
#define LVOS_MallocGfp(pid, size, gfp) malloc(size)
#endif
#endif  /* UN_MEM */


#endif /* _LVOS_MEM_H__ */
/** @} */

