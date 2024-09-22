/**************************************************************************

    (C) 2007 ~2019   ��Ϊ�������˿Ƽ����޹�˾  ��Ȩ���У�����һ��Ȩ����

***************************************************************************
 �� �� ��:  ����
 ��    ��:  x00001559
 �������:  2011��9��23��
 ��������:  OS�ṩ���ϲ�ģ����õĽӿ�
 ��    ע:  
 �޸ļ�¼:  
        1.ʱ     �� :
          �� �� �� :
          �޸����� :
**************************************************************************/
#ifndef OS_INTF_H
#define OS_INTF_H

#if defined(WIN32) || defined(__KERNEL__)
#if defined(__KERNEL__) && !defined(_PCLINT_)
#include <linux/blkdev.h>
#endif /* __KERNEL__ && !(_PCLINT_) */

/* ���������CACHEMEMMAX��cache���͵��ڴ�� */
#define CACHEMEMMAX 4
typedef struct tagOS_CACHE_MEM_INFO
{
    OSP_U32 nr_cache;       /* cache�ڴ�εĸ��� */
    struct cacheEntry
    {
        OSP_U64 addr;       /* �ڴ�ε���ʼ���Ե�ַ */
        OSP_U64 size;       /* �ڴ�γ��ȣ���λ:�ֽ� */
    }map[CACHEMEMMAX];      /* �ڴ�����飬���CACHEMEMMAX����Ա */
}OS_CACHE_MEM_INFO;

/**
    \brief ��λ������������λԭ���� software
*/
static inline OSP_U32 OS_ResetLocalBoard(void)
{
	return 0;
}
OSP_S32 OS_SetMemoryRO(OSP_VOID *addr, OSP_S32 numpages);
OSP_S32 OS_SetMemoryRW(OSP_VOID *addr, OSP_S32 numpages);
OSP_VOID OS_GetCacheMemInfo(OS_CACHE_MEM_INFO *v_pstCacheMemInfo);
OSP_S32 OS_GetMemoryRW(OSP_VOID *addr);

extern OSP_U32 uiSetMem;
#define OS_SETMEMORY_RO(addr, numpages) \
do \
{ \
    if ( 1 == uiSetMem )\
    {\
        (void)OS_SetMemoryRO(addr, numpages); \
    }\
} while (0)
#define OS_SETMEMORY_RW(addr, numpages) \
do \
{ \
    if ( 1 == uiSetMem )\
    {\
        (void)OS_SetMemoryRW(addr, numpages); \
    }\
} while (0)

#ifdef __KERNEL__
void OS_BlkExecuteRqNowait(struct request_queue *q,
                           struct gendisk *bd_disk,
                           struct request *rq, OSP_S32 at_head,
                           rq_end_io_fn *done);
/**
    \brief �򿪴��ڴ�ӡ
*/
OSP_U32 OS_TtySPrintOn(void);
/**
    \brief �رմ��ڴ�ӡ
*/
OSP_U32 OS_TtySPrintOff(void);
OSP_S32 OS_SetThrdAffinityCPU(OSP_ULONG v_ulCpu);
#endif /* __KERNEL__ */

#endif /* WIN32 || __KERNEL__ */

#endif /* OS_INTF_H */
