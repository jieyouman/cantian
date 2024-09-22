/******************************************************************************

                  ��Ȩ���� (C) 2008-2008 ��Ϊ�������˿Ƽ����޹�˾

 ******************************************************************************
  �� �� ��   : lvos_bitops.h
  �� �� ��   : ����
  ��    ��   : x00001559
  ��������   : 2008��7��8��
  ����޸�   :
  ��������   : Linux�ں˵�bit�������ܷ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2008��7��8��
    ��    ��   : x00001559
    �޸�����   : �����ļ�

******************************************************************************/
/**
    \file  lvos_bitops.h
    \brief bit��������

    \date 2008-05-27
*/

/** \addtogroup VOS_BITOPS λ����
    @{ 
*/

#ifndef __LVOS_BITOPS_H__
#define __LVOS_BITOPS_H__

#if defined(WIN32) || defined(_PCLINT_)
/**
    \brief ԭ�ӵ�����addr��ָ�����nrλ
    \note  ������windows��linux�ں�̬��linux�û�̬(����֤ԭ����)�����ﱣ��֧��linux�û�ֻ̬��Ϊ�˼�����ǰ�Ĵ��룬
    \note  linux�û�̬�뾡����Ҫʹ���ں�̬��λ������ʽ��
    \note  �޵�������������
    \param[in] nr        Ҫ���õڼ�λ
    \param[in] addr      �����ַ
    \return  ��
*/
void set_bit( OSP_S32 nr, void *addr);

/**
    \brief ԭ�ӵ����addr��ָ�����nrλ
    \note  ������windows��linux�ں�̬��linux�û�̬(����֤ԭ����)�����ﱣ��֧��linux�û�ֻ̬��Ϊ�˼�����ǰ�Ĵ��룬
    \note  linux�û�̬�뾡����Ҫʹ���ں�̬��λ������ʽ��
    \note  �޵�������������
    \param[in] nr        Ҫ��յڼ�λ
    \param[in] addr      �����ַ
    \return    ��
*/
void clear_bit(OSP_S32 nr, void *addr);

/**
    \brief ԭ�ӵĲ���addr��ָ�����nrλ��Ϊ0�򷵻�0�����򷵻ط�0
    \note  ������windows��linux�ں�̬��linux�û�̬(����֤ԭ����)�����ﱣ��֧��linux�û�ֻ̬��Ϊ�˼�����ǰ�Ĵ��룬
    \note  linux�û�̬�뾡����Ҫʹ���ں�̬��λ������ʽ��
    \note  �޵�������������
    \attention ���ԭ��bitֵ����0�Ļ����᷵�ط�0����һ������1
    \param[in] nr        Ҫ���Եڼ�λ
    \param[in] addr      �����ַ
    \retval    0   ԭ��bitֵΪ0
    \retval    ��0 ԭ��bitֵ��Ϊ0
*/
OSP_S32 test_bit(OSP_S32 nr, void *addr);


/**
    \brief ԭ�ӵ�����addr��ָ�����nrλ��������ԭ��bitֵ�Ƿ�Ϊ0��Ϊ0�򷵻�0�����򷵻ط�0
    \note  ֧��windows��linux�ں�̬����֧��linux�û�̬
    \note  �޵�������������    
    \attention ���ԭ��bitֵ����0�Ļ����᷵�ط�0����һ������1
    \param[in] nr        Ҫ���õڼ�λ
    \param[in] addr      �����ַ
    \retval    0   ԭ��bitֵΪ0
    \retval    ��0 ԭ��bitֵ��Ϊ0
*/

OSP_S32 test_and_set_bit(OSP_S32 nr, void *addr);

/**
    \brief ԭ�ӵ�����addr��ָ�����nrλ������������ǰ��bitֵ
    \note  ֧��windows��linux�ں�̬����֧��linux�û�̬
    \note  �޵�������������    
    \attention ���ԭ��bitֵ����0�Ļ����᷵�ط�0����һ������1
    \param[in] nr        Ҫ��յڼ�λ
    \param[in] addr      �����ַ
    \retval    0   ԭ��bitֵΪ0
    \retval    ��0 ԭ��bitֵ��Ϊ0
*/
OSP_S32 test_and_clear_bit(OSP_S32 nr, void *addr);

/**
    \brief ԭ�ӵķ�תaddr��ָ�����nrλ�������ط�תǰ��bitֵ
    \note  ֧��windows��linux�ں�̬����֧��linux�û�̬
    \note  �޵�������������
    \attention ���ԭ��bitֵ����0�Ļ����᷵�ط�0����һ������1
    \param[in] nr        Ҫ��յڼ�λ
    \param[in] addr      �����ַ
    \retval    0   ԭ��bitֵΪ0
    \retval    ��0 ԭ��bitֵ��Ϊ0
*/
OSP_S32 test_and_change_bit(OSP_S32 nr, void *addr);

/**
    \brief ����w��Ϊ1��bit������
*/
OSP_U32 hweight32(OSP_U32 w);

/* ����w��Ϊ1��bit������ */
unsigned long hweight64(uint64_t w);

#elif defined(__LINUX_USR__)
#ifdef mips
#include <asm/bitops.h>
#else
static inline void set_bit(OSP_S32 nr, void *addr)
{
    asm volatile("lock;" "bts %1,%0" : "+m" (addr) : "Ir" (nr) : "memory");
}

static inline OSP_S32 test_bit(OSP_S32 nr, void *addr)
{
    int oldbit;

    asm volatile("bt %2,%1\n\t"
             "sbb %0,%0"
             : "=r" (oldbit)
             : "m" (*(unsigned long *)addr), "Ir" (nr));

    return oldbit;
}

static inline void clear_bit(OSP_S32 nr, void *addr)
{
    asm volatile("lock;" "btr %1,%0" : "+m" (addr) : "Ir" (nr));
}
#endif
#elif defined(__KERNEL__)
#include <asm/bitops.h>

#else
#error "platform not specify"
#endif

#define LVOS_set_bit                             set_bit            
#define LVOS_test_bit                            test_bit           
#define LVOS_clear_bit                           clear_bit          
#define LVOS_test_and_set_bit                    test_and_set_bit   
#define LVOS_test_and_clear_bit                  test_and_clear_bit 
#define LVOS_test_and_change_bit                 test_and_change_bit

/**
    Dorado_V3����7����ԭ�ӱ���λ��������ӿڣ�ʹ��ԭ�ӱ�������ʵ�֡�
    ������û�з�ԭ�ӱ���λ����ʵ�ַ����������ַ����ڹ�����û�в��ֻ�������ϵĲ�ࡣ
    ���治�������ܣ���ʹ��ԭ�ӱ���λ�����������·�װ��
    ����ʱ�䣺2016/06/20
*/
#define LVOS_set_bit_non_atomic                  set_bit
#define LVOS_clear_bit_non_atomic                clear_bit
#define LVOS_test_and_set_bit_non_atomic         test_and_set_bit
#define LVOS_test_and_clear_bit_non_atomic       test_and_clear_bit
#define LVOS_test_and_change_bit_non_atomic      test_and_change_bit
#define LVOS_change_bit_non_atomic               (void)test_and_change_bit

/**
    \brief ���ҵ�һ��Ϊ1��bitλ(��ԭ�Ӳ���)
    \param[in]  v_pAddr  ��Ҫ���ҵ���ʼ��ַ
    \param[in]  iSize   ���ҵĳ���(��λΪbitλ)
    \param[out] v_pIndex �����ҵ�������(��λΪbitλ)
    \retval     TRUE     �ɹ��ҵ�Ϊ1��bitλ
    \retval     FALSE    û���ҵ�
*/
OSP_BOOL LVOS_FindFirst1Bit(const void *v_pAddr, OSP_S32 iSize, OSP_S32 *v_pIndex);

/**
    \brief ���ҵ�һ��Ϊ0��bitλ(��ԭ�Ӳ���)
    \param[in]  v_pAddr  ��Ҫ���ҵ���ʼ��ַ
    \param[in]  iSize    ���ҵĳ���(��λΪbitλ)
    \param[out] v_pIndex �����ҵ�������(��λΪbitλ)
    \retval     TRUE     �ɹ��ҵ�Ϊ0��bitλ
    \retval     FALSE    û���ҵ�
*/
OSP_BOOL LVOS_FindFirst0Bit(const void *v_pAddr, OSP_S32 iSize, OSP_S32 *v_pIndex);

/**
    \brief ������һ��Ϊ1��bitλ(��ԭ�Ӳ���)
    \param[in]  addr     ��Ҫ���ҵ���ʼ��ַ
    \param[in]  size     ���ҵĳ���(��λΪbitλ)
    \param[in]  offset   ������ʼλ��
    \param[out] index    �����ҵ�������(��λΪbitλ)
    \retval     TRUE     �ɹ��ҵ�Ϊ1��bitλ
    \retval     FALSE    û���ҵ�
*/
bool LVOS_FindNext1Bit(const void *addr, int32_t size, int32_t offset, int32_t *index);

#ifdef WIN32 /* Linux��ֱ�����ں˵� */
/*
    \brief ���ҵ�һ��Ϊ1��bitλ(��ԭ�Ӳ���)
    \return �ҵ������������Ҳ�������ֵ >= size
*/
unsigned long find_first_bit(const unsigned long * addr, unsigned long size);
/*
    \brief ������һ��Ϊ1��bitλ(��ԭ�Ӳ���)
    \return �ҵ������������Ҳ������� >= size
*/
unsigned long find_next_bit(const unsigned long *addr, unsigned long size, unsigned long offset);

unsigned long find_next_zero_bit(const unsigned long *addr, unsigned long size, unsigned long offset);

/*
    \brief   ���ҵ�һ��Ϊ1��bit���λ
    \return  �����ҵ���bitλ������ 1 ~ 32, Ϊ 0 ��ʾû���ҵ�
*/
int ffs(int x);

/*
    \brief   ���ҵ�һ��Ϊ1��bit���λ 
    \return  �����ҵ���bitλ������ 1 ~ 32, Ϊ 0 ��ʾû���ҵ�
*/
int fls(int x);

#endif

#endif /* __LVOS_BITOPS_H__ */
/**
    @}
*/

