/******************************************************************************

                  ��Ȩ���� (C) 2008-2008 ��Ϊ�������˿Ƽ����޹�˾

 ******************************************************************************
  �� �� ��   : lvos_atomic.h
  �� �� ��   : ����

  ��������   : 2008��7��8��
  ����޸�   :
  ��������   : Linux�ں˵�atomic���ܷ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2008��7��8��

    �޸�����   : �����ļ�

  2.��    ��   : 2008��11��18��

    �޸�����   : ����atomic_inc ��atomic_dec

******************************************************************************/
/**
    \file  lvos_atomic.h
    \brief ԭ�Ӳ�����ؽӿڶ���

    \date 2010-05-08
*/

/** \addtogroup VOS_ATOMIC ԭ�Ӳ���
    @{ 
*/

#ifndef __LVOS_ATOMIC_H__
#define __LVOS_ATOMIC_H__

#if defined(WIN32) || defined(_PCLINT_) || defined(__LINUX_USR__)

/** \brief ԭ�ӱ������Ͷ��� */
typedef struct { 
    volatile long counter;
} atomic_t;

/**
    \brief ��ʼ��ԭ�ӱ���
    \note  ������windows��linux�ں�̬����֧��linux�û�̬
    \note  �޵�������������
    \param[in] i    ԭ�ӱ����ĳ�ʼ��ֵ
    \retval    ��ʼ�����ԭ�ӱ���
*/
#define ATOMIC_INIT(i)  { (i) }


/**
    \brief ����ԭ�ӱ���ֵ
    \note  ������windows��linux�ں�̬��linux�û�̬�����ﱣ��֧��linux�û�ֻ̬��Ϊ�˼�����ǰ�Ĵ��룬
    \note  linux�û�̬���Լ���ͬ������������뾡����Ҫʹ���ں�̬��ͬ����ʽ��
    \note  �޵�������������
*/
void atomic_set(atomic_t *v, OSP_S32 val);

/**
    \brief ԭ�Ӽӣ�������Ӻ��ֵ
    \note  ������windows��linux�ں�̬����֧��linux�û�̬
    \note  �޵�������������
    \param[in] i    ԭ�ӱ���Ҫ���ӵ�ֵ
    \param[in] v ԭ�ӱ���ָ��
    \return    ԭ�ӱ�����Ӻ��ֵ
*/
OSP_S32 atomic_add_return(OSP_S32 i, atomic_t *v);


/**
    \brief ԭ�Ӽӣ����޷���ֵ    
    \note  ������windows��linux�ں�̬��linux�û�̬(����֤ԭ����)�����ﱣ��֧��linux�û�ֻ̬��Ϊ�˼�����ǰ�Ĵ��룬
    \note  linux�û�̬���Լ���ͬ������������뾡����Ҫʹ���ں�̬��ͬ����ʽ��
    \note  �޵�������������
    \param[in] i ԭ�ӱ���Ҫ���ӵ�ֵ
    \param[in] v ԭ�ӱ���ָ��
    \return    ��
*/
void atomic_add(OSP_S32 i, atomic_t *v);

/**
    \brief ��ȡԭ�ӱ���ֵ
    \note  ������windows��linux�ں�̬��linux�û�̬�����ﱣ��֧��linux�û�ֻ̬��Ϊ�˼�����ǰ�Ĵ��룬
    \note  linux�û�̬���Լ���ͬ������������뾡����Ҫʹ���ں�̬��ͬ����ʽ��
    \note  �޵�������������
    \param[in] v ԭ�ӱ���ָ��
    \retval    OSP_S32   ԭ�ӱ�����ֵ
*/
OSP_S32 atomic_read(atomic_t *v);

/**
    \brief ԭ�Ӽ�������������ֵ
    \note  ������windows��linux�ں�̬����֧��linux�û�̬
    \note  �޵�������������
    \param[in] i    ԭ�ӱ���Ҫ���ٵ�ֵ
    \param[in] v ԭ�ӱ���ָ��
    \retval    OSP_S32   ԭ�ӱ���������ֵ
*/
OSP_S32 atomic_sub_return(OSP_S32 i, atomic_t *v);


/**
    \brief ԭ�Ӽ�
    \note  ������windows��linux�ں�̬��linux�û�̬(����֤ԭ����)�����ﱣ��֧��linux�û�ֻ̬��Ϊ�˼�����ǰ�Ĵ��룬
    \note  linux�û�̬���Լ���ͬ������������뾡����Ҫʹ���ں�̬��ͬ����ʽ��
    \note  �޵�������������
    \param[in]  i  ԭ�ӱ���Ҫ���ٵ�ֵ
    \param[in]  v  ԭ�ӱ���ָ��
    \return     ��
*/
void atomic_sub(OSP_S32 i, atomic_t *v);


/**
    \brief ԭ�Ӽ������Խ���Ƿ�Ϊ0
    \note  ������windows��linux�ں�̬��linux�û�̬(����֤ԭ����)�����ﱣ��֧��linux�û�ֻ̬��Ϊ�˼�����ǰ�Ĵ��룬
    \note  linux�û�̬���Լ���ͬ������������뾡����Ҫʹ���ں�̬��ͬ����ʽ��
    \note  �޵�������������
    \param[in] i    ԭ�ӱ���Ҫ���ٵ�ֵ
    \param[in] v ԭ�ӱ���ָ��
    \retval    FALSE       ������ֵ��Ϊ0
    \retval    TRUE        ������ֵΪ0
*/
OSP_BOOL atomic_sub_and_test(OSP_S32 i, atomic_t *v);


/**
    \brief ԭ������
    \note  ������windows��linux�ں�̬��linux�û�̬(����֤ԭ����)�����ﱣ��֧��linux�û�ֻ̬��Ϊ�˼�����ǰ�Ĵ��룬
    \note  linux�û�̬���Լ���ͬ������������뾡����Ҫʹ���ں�̬��ͬ����ʽ��
    \note  �޵�������������
    \param[in] v ԭ�ӱ���ָ��
    \return    ��
*/
void atomic_inc(atomic_t *v);


/**
    \brief ԭ�������������������ֵ
    \note  ������windows��linux�ں�̬��linux�û�̬(����֤ԭ����)�����ﱣ��֧��linux�û�ֻ̬��Ϊ�˼�����ǰ�Ĵ��룬
    \note  linux�û�̬���Լ���ͬ������������뾡����Ҫʹ���ں�̬��ͬ����ʽ��
    \note  �޵�������������
    \param[in] v ԭ�ӱ���ָ��
    \return    �������Ӻ��ֵ
*/
OSP_S32 atomic_inc_return(atomic_t *v);


/**
    \brief ԭ���Լ�
    \note  ������windows��linux�ں�̬��linux�û�̬(����֤ԭ����)�����ﱣ��֧��linux�û�ֻ̬��Ϊ�˼�����ǰ�Ĵ��룬
    \note  linux�û�̬���Լ���ͬ������������뾡����Ҫʹ���ں�̬��ͬ����ʽ��
    \note  �޵�������������
    \param[in] v ԭ�ӱ���ָ��
    \retval    void
*/
void atomic_dec(atomic_t *v);


/**
    \brief ԭ���Լ��������Լ����ֵ
    \note  ������windows��linux�ں�̬��linux�û�̬(����֤ԭ����)�����ﱣ��֧��linux�û�ֻ̬��Ϊ�˼�����ǰ�Ĵ��룬
    \note  linux�û�̬���Լ���ͬ������������뾡����Ҫʹ���ں�̬��ͬ����ʽ��
    \note  �޵�������������
    \param[in] v ԭ�ӱ���ָ��
    \retval    void
*/
OSP_S32 atomic_dec_return(atomic_t *v);

/**
    \brief ����ԭ�ӱ��������Խ���Ƿ�Ϊ0
    \note  ������windows��linux�ں�̬����֧��linux�û�̬
    \note  �޵�������������
    \param[in] v ԭ�ӱ���ָ��
    \retval    TRUE  ������Ľ��Ϊ0
    \retval    FALSE ������Ľ����Ϊ0
*/
OSP_BOOL atomic_inc_and_test(atomic_t *v);

/**
    \brief �Լ�ԭ�ӱ��������Խ���Ƿ�Ϊ0
    \note  ������windows��linux�ں�̬����֧��linux�û�̬
    \note  �޵�������������
    \param[in] v ԭ�ӱ���ָ��
    \retval    TRUE  �Լ���Ľ��Ϊ0������TRUE
    \retval    FALSE �Լ���Ľ����Ϊ0������FALSE
*/
OSP_BOOL atomic_dec_and_test(atomic_t *v);

/**
    \brief 64λԭ�ӱ����汾����
*/
typedef struct {
    volatile OSP_S64 counter;
} atomic64_t;

#define ATOMIC64_INIT(i) { (i) }

/**
    \brief ����ԭ�ӱ���ֵ
    \note  ������windows��linux�ں�̬��linux�û�̬�����ﱣ��֧��linux�û�ֻ̬��Ϊ�˼�����ǰ�Ĵ��룬
    \note  linux�û�̬���Լ���ͬ������������뾡����Ҫʹ���ں�̬��ͬ����ʽ��
    \note  �޵�������������
*/
void atomic64_set(atomic64_t *v, OSP_S64 val);

/**
    \brief ��ȡԭ�ӱ���ֵ
    \note  ������windows��linux�ں�̬��linux�û�̬�����ﱣ��֧��linux�û�ֻ̬��Ϊ�˼�����ǰ�Ĵ��룬
    \note  linux�û�̬���Լ���ͬ������������뾡����Ҫʹ���ں�̬��ͬ����ʽ��
    \note  �޵�������������
    \param[in] v ԭ�ӱ���ָ��
    \retval    OSP_S32   ԭ�ӱ�����ֵ
*/
OSP_S64 atomic64_read(atomic64_t *v);

/**
    \brief ԭ������
    \note  ������windows��linux�ں�̬��linux�û�̬(����֤ԭ����)�����ﱣ��֧��linux�û�ֻ̬��Ϊ�˼�����ǰ�Ĵ��룬
    \note  linux�û�̬���Լ���ͬ������������뾡����Ҫʹ���ں�̬��ͬ����ʽ��
    \note  �޵�������������
    \param[in] v ԭ�ӱ���ָ��
    \return    ��
*/
void atomic64_inc(atomic64_t *v);

/**
    \brief ԭ�������������������ֵ
    \note  ������windows��linux�ں�̬��linux�û�̬(����֤ԭ����)�����ﱣ��֧��linux�û�ֻ̬��Ϊ�˼�����ǰ�Ĵ��룬
    \note  linux�û�̬���Լ���ͬ������������뾡����Ҫʹ���ں�̬��ͬ����ʽ��
    \note  �޵�������������
    \param[in] v ԭ�ӱ���ָ��
    \return    �������Ӻ��ֵ
*/
OSP_S64 atomic64_inc_return(atomic64_t *v);

/**
    \brief ԭ���Լ�
    \note  ������windows��linux�ں�̬��linux�û�̬(����֤ԭ����)�����ﱣ��֧��linux�û�ֻ̬��Ϊ�˼�����ǰ�Ĵ��룬
    \note  linux�û�̬���Լ���ͬ������������뾡����Ҫʹ���ں�̬��ͬ����ʽ��
    \note  �޵�������������
    \param[in] v ԭ�ӱ���ָ��
    \retval    void
*/
void atomic64_dec(atomic64_t *v);


/**
    \brief ԭ���Լ��������Լ����ֵ
    \note  ������windows��linux�ں�̬��linux�û�̬(����֤ԭ����)�����ﱣ��֧��linux�û�ֻ̬��Ϊ�˼�����ǰ�Ĵ��룬
    \note  linux�û�̬���Լ���ͬ������������뾡����Ҫʹ���ں�̬��ͬ����ʽ��
    \note  �޵�������������
    \param[in] v ԭ�ӱ���ָ��
    \retval    void
*/
OSP_S64 atomic64_dec_return(atomic64_t *v);

/**
    \brief ԭ�Ӽӣ����޷���ֵ    
    \note  ������windows��linux�ں�̬��linux�û�̬(����֤ԭ����)�����ﱣ��֧��linux�û�ֻ̬��Ϊ�˼�����ǰ�Ĵ��룬
    \note  linux�û�̬���Լ���ͬ������������뾡����Ҫʹ���ں�̬��ͬ����ʽ��
    \note  �޵�������������
    \param[in] i ԭ�ӱ���Ҫ���ӵ�ֵ
    \param[in] v ԭ�ӱ���ָ��
    \return    ��
*/
void atomic64_add(OSP_S64 i, atomic64_t *v);

/**
    \brief 64λԭ�Ӽӷ���������Ӻ��ֵ
    \note  ������windows��linux�ں�̬��linux�û�̬(����֤ԭ����)�����ﱣ��֧��linux�û�ֻ̬��Ϊ�˼�����ǰ�Ĵ��룬
    \note  linux�û�̬���Լ���ͬ������������뾡����Ҫʹ���ں�̬��ͬ����ʽ��
    \note  �޵�������������
    \param[in] v ,i
    \retval    OSP_S64
*/

OSP_S64 atomic64_add_return(OSP_S64 i, atomic64_t *v);

/**
    \brief 64λԭ�Ӽ���������������ֵ
    \note  ������windows��linux�ں�̬��linux�û�̬(����֤ԭ����)�����ﱣ��֧��linux�û�ֻ̬��Ϊ�˼�����ǰ�Ĵ��룬
    \note  linux�û�̬���Լ���ͬ������������뾡����Ҫʹ���ں�̬��ͬ����ʽ��
    \note  �޵�������������
    \param[in] v ,i
    \retval    OSP_S64
*/
OSP_S64 atomic64_sub_return(OSP_S64 i, atomic64_t *v);


#elif defined(__KERNEL__)
#include <asm/atomic.h>
#else
#error "platform not specify"
#endif

#endif /* __LVOS_ATOMIC_H__ */

/** @} */

