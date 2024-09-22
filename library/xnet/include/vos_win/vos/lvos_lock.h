/******************************************************************************

                  ��Ȩ���� (C), 2008-2008, ��Ϊ�������˿Ƽ����޹�˾

 ******************************************************************************
  �� �� ��   : lvos_lock.h
  �� �� ��   : ����
  
  ��������   : 2008��6��3��
  ����޸�   :
  ��������   : �������ź����������������������������
  �����б�   :
              LVOS_sema_destroy
              LVOS_sema_down
              LVOS_sema_init
              LVOS_sema_up
  �޸���ʷ   :
  1.��    ��   : 2008��6��3��
    
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef __LVOS_LOCK_H__
#define __LVOS_LOCK_H__

#if 0
/**
    \file  lvos_lock.h
    \brief �����������������������ź���

    \date 2008-08-19
*/

/** \addtogroup VOS_SPINLOCK ������
    ע��:  init��destroy��������ʹ�ã������ʹ������Windows(����)�ϻ���ھ��й©\n
    ��������Linux�ں�Ϊԭ�ͷ�װ\n
    ���������������в����п��ܵ����߳��л��Ĳ����������ߣ��ӻ������������ź���������socket������
    @{ 
*/
#if DESC("������")
#if defined(WIN32) || defined(_PCLINT_)

/** \brief ���������Ͷ��� */
typedef struct
{
    int32_t magic;
    HANDLE hMutex;
} spinlock_t;

typedef spinlock_t rwlock_t;


typedef spinlock_t mcs_spinlock_t;


void spin_lock_init_inner(spinlock_t *v_pLock, OSP_U32 v_uiPid);
/** \brief ��ʼ�������� */
#define spin_lock_init(v_pLock) spin_lock_init_inner(v_pLock, MY_PID)

/** \brief ���������� */
void spin_lock(spinlock_t *v_pLock);

/** \brief ���������Լ���
    \retval TRUE  �����ɹ�
    \retval FALSE ����ʧ��
*/
OSP_S32 spin_trylock(spinlock_t *v_pLock);

/** \brief ���������� */
void spin_unlock(spinlock_t *v_pLock);

void spin_lock_destroy_inner(spinlock_t *v_pLock, OSP_U32 v_uiPid);
/** \brief ���������� */
#define spin_lock_destroy(v_pLock) spin_lock_destroy_inner(v_pLock, MY_PID)

/** \brief �����������������жϱ�־ */
#define spin_lock_irqsave(pLock, flag)   { spin_lock(pLock); (void)(flag); } 

/** \brief �����������������жϱ�־, ����ֵͬ \ref spin_trylock */
#define spin_trylock_irqsave(pLock, flag)   { spin_trylock(pLock); (void)(flag); } 

/** \brief �������������ָ��жϱ�־ */
#define spin_unlock_irqrestore(pLock, flag) { spin_unlock(pLock); (void)(flag); }


#define mcs_spin_lock_init          spin_lock_init
#define mcs_spin_lock               spin_lock
#define mcs_spin_unlock             spin_unlock
#define mcs_spin_lock_irqsave       spin_lock_irqsave
#define mcs_spin_unlock_irqrestore  spin_unlock_irqrestore
#define mcs_spin_lock_destroy       spin_lock_destroy



struct rcu_head {
    struct rcu_head *next;
    void (*func)(struct rcu_head *head);
};

/* ������, ʹ��һ��ȫ����ģ��RCU������� */
spinlock_t g_rcuLock;

/* ���������ݼӶ���, ������ռ�����ڱ�ʶ���ʹ������ݵ�����, ʵ������ */
inline void rcu_read_lock(void)
{
    spin_lock(&g_rcuLock);
}

/* ���������ݽ����, ������ռ�����ڱ�ʶ���ʹ������ݵ�����, ʵ������ */
inline void rcu_read_unlock(void)
{
    spin_unlock(&g_rcuLock);
}

/*��rcu_read_lock������ͬ, ��������ʹ��rcu_read_lock_bh�ĳ�����
  �Ὣ���жϽ���Ҳ��Ϊ�������л��ı�ʶ */
inline void rcu_read_lock_bh(void)
{
    spin_lock(&g_rcuLock);
}

/*��rcu_read_unlock������ͬ, ��������ʹ��rcu_read_unlock_bh�ĳ�����
  �Ὣ���жϽ���Ҳ��Ϊ�������л��ı�ʶ */
inline void rcu_read_unlock_bh(void)
{
    spin_unlock(&g_rcuLock);
}

/* д/�޸Ĺ�������ʱ��д���Ĺ���, ���ڷ���ʹ��, �ں���Ϊ�� */
inline void rcu_write_lock(void)
{
    spin_lock(&g_rcuLock);
}

/* д/�޸Ĺ�������ʱ��д���Ĺ���, ���ڷ���ʹ��, �ں���Ϊ�� */
inline void rcu_write_unlock(void)
{
    spin_unlock(&g_rcuLock);
}

/* ��rcu_write_lock������ͬ, ��rcu_read_lock_bh��Ӧʹ�� */
inline void rcu_write_lock_bh(void)
{
    spin_lock(&g_rcuLock);
}
/* ��rcu_write_unlock������ͬ, ��rcu_read_unlock_bh��Ӧʹ�� */
inline void rcu_write_unlock_bh(void)
{
    spin_unlock(&g_rcuLock);
}

/*����ע���ͷŹ�����Դ�������ڴ溯��, func���������ã�
  ��ʾhead������Ϊ0,��ֱ���ͷ���Դ, headΪ�ṹrcu_headָ�� */
#define OS_CallRcu(head, func)        do {(func)(head);} while (0)

/* ��call_rcu������ͬ, ���bh��ǵļӽ���������Ӧʹ�� */
#define OS_CallRcuBh(head, func)     do {(func)(head);} while (0)



/* ��һ���ڵ����RCU����ͷ */
inline void list_add_rcu(struct list_head *new_node, struct list_head *head)
{
    list_add((new_node), (head));
}

/* ��һ���ڵ����RCU����β */
inline void list_add_tail_rcu(struct list_head *new_node, 
                              struct list_head *head)
{
    list_add_tail(new_node, head);
}

/* ��һ��RCU������ɾ��һ���ڵ� */
inline void list_del_rcu(struct list_head *entry)
{
    list_del(entry);
}

/* �滻һ��RCU�ڵ� */
inline void list_replace_rcu(struct list_head *old_node,
                             struct list_head *new_node)
{
    new_node->next = old_node->next;
    new_node->prev = old_node->prev;
    new_node->prev->next = new_node;
    new_node->next->prev = new_node;
    INIT_LIST_NODE(old_node);
}

/* ����ͬlist_entry */
#define list_entry_rcu(ptr, type, member)           \
        list_entry(ptr, type, member)

/* ��ptr����һ���ڵ���list_entry���� */
#define list_first_entry_rcu(ptr, type, member)     \
        list_entry_rcu((ptr)->next, type, member)

/* ������pos��ʼ����RCU���� */
#define list_for_each_continue_rcu(pos, head)       \
        for ((pos) = (pos)->next; (pos) != (head); (pos) = (pos)->next)



#ifndef BUILD_WITH_ACE
#define rwlock_init  spin_lock_init
#define read_lock    spin_lock
#define read_unlock  spin_unlock
#define write_lock   spin_lock
#define write_unlock spin_unlock
#define read_lock_irqsave       spin_lock_irqsave
#define read_unlock_irqrestore  spin_unlock_irqrestore
#define write_lock_irqsave      spin_lock_irqsave
#define write_unlock_irqrestore spin_unlock_irqrestore
#define rwlock_destroy spin_lock_destroy
#endif

/* ������������������ʹ�� */
#define spin_lock_bh    spin_lock
#define spin_unlock_bh  spin_unlock

#elif defined(__LINUX_USR__)
#include <semaphore.h>
#include <pthread.h>

#if defined(__USE_XOPEN2K)
typedef pthread_spinlock_t spinlock_t;
#define spin_lock_init(lock) pthread_spin_init(lock, 0)
#define spin_lock pthread_spin_lock
#define spin_unlock pthread_spin_unlock
#define spin_lock_destroy  pthread_spin_destroy
#else
typedef pthread_mutex_t spinlock_t;
#define spin_lock_init(lock)    pthread_mutex_init(lock, NULL)
#define spin_lock               pthread_mutex_lock
#define spin_unlock             pthread_mutex_unlock
#define spin_lock_destroy       pthread_mutex_destroy
#endif

#define spin_lock_irqsave(pLock, flag)  do { spin_lock(pLock); (void)(flag); } while(0)
#define spin_unlock_irqrestore(pLock, flag) { spin_unlock(pLock); (void)(flag); }
#define spin_lock_bh    spin_lock
#define spin_unlock_bh  spin_unlock


#if defined(__USE_XOPEN2K)
typedef pthread_spinlock_t          mcs_spinlock_t;
#define mcs_spin_lock_init(lock)    pthread_spin_init(lock, 0)
#define mcs_spin_lock               pthread_spin_lock
#define mcs_spin_unlock             pthread_spin_unlock
#define mcs_spin_lock_destroy       pthread_spin_destroy
#else
typedef pthread_mutex_t             mcs_spinlock_t;
#define mcs_spin_lock_init(lock)    pthread_mutex_init(lock, NULL)
#define mcs_spin_lock               pthread_mutex_lock
#define mcs_spin_unlock             pthread_mutex_unlock
#define mcs_spin_lock_destroy       pthread_mutex_destroy
#endif

#define mcs_spin_lock_irqsave(pLock, flag)  do { mcs_spin_lock(pLock); (void)(flag); } while(0)
#define mcs_spin_unlock_irqrestore(pLock, flag) do { mcs_spin_unlock(pLock); (void)(flag); } while(0)


#elif defined(__KERNEL__)
/* ֱ��ʹ���ں˶���������� */
#define spin_lock_destroy(pLock)
#define rwlock_destroy(pLock)


/* �ں˲�����, ��Ҫ����д�� */
#define rcu_write_lock(lock)
#define rcu_write_unlock(lock)
#define rcu_write_lock_bh(lock)
#define rcu_write_unlock_bh(lock)



#define mcs_spin_lock_destroy(lock)

#include <linux/irqflags.h>
#include <asm/processor.h>
#include <asm/cmpxchg.h>

typedef struct _mcs_lock_node {
    volatile int waiting;
    struct _mcs_lock_node *volatile next;
}mcs_lock_node;

typedef mcs_lock_node *volatile mcs_lock;

typedef struct {
    mcs_lock slock;
    mcs_lock_node nodes[NR_CPUS];
} mcs_spinlock_t;

/*****************************************************************************
 �� �� ��  : mcs_spin_lock_init
 ��������  : MCS����ʼ��
 �������  : mcs_spinlock_t *lock
 �������  : ��
 �� �� ֵ     : ��
 ���ú���  : ��
 ��������  :  
 
 �޸���ʷ      :
  1.��    ��   : 2012��1��10
    
    �޸�����   : �����ɺ���
*****************************************************************************/
static inline void mcs_spin_lock_init (mcs_spinlock_t *lock)
{
    int i;
    
    lock->slock = NULL;
    for (i = 0; i < NR_CPUS; i++) {
        lock->nodes[i].waiting = 0;
        lock->nodes[i].next = NULL;
    }
}
/*****************************************************************************
 �� �� ��  : mcs_spin_lock
 ��������  : MCS������
 �������  : mcs_spinlock_t *lock
 �������  : ��
 �� �� ֵ     : ��
 ���ú���  : 1) raw_smp_processor_id
                           2) xchg
 ��������  :  
 
 �޸���ʷ      :
  1.��    ��   : 2012��1��10
    
    �޸�����   : �����ɺ���
*****************************************************************************/
static inline void mcs_spin_lock(mcs_spinlock_t *lock)
{
    int cpu;
    mcs_lock_node *me;
    mcs_lock_node *tmp;
    mcs_lock_node *pre;
    
    cpu = raw_smp_processor_id();
    me = &(lock->nodes[cpu]);
    tmp = me;
    me->next = NULL;

    pre = xchg(&lock->slock, tmp);
    if (pre == NULL) {
        /* mcs_lock is free */
        return;
    }

    me->waiting = 1;
    smp_wmb();
    pre->next = me;
    
    while (me->waiting) {
        cpu_relax();
    }   
}
/*****************************************************************************
 �� �� ��  : mcs_spin_unlock
 ��������  : MCS������
 �������  : mcs_spinlock_t *lock
 �������  : ��
 �� �� ֵ     : ��
 ���ú���  : 1) raw_smp_processor_id
                           2) cmpxchg
 ��������  :  
 
 �޸���ʷ      :
  1.��    ��   : 2012��1��10
    
    �޸�����   : �����ɺ���
*****************************************************************************/
static inline void mcs_spin_unlock(mcs_spinlock_t *lock)
{
    int cpu;
    mcs_lock_node *me;
    mcs_lock_node *tmp;
    
    cpu = raw_smp_processor_id();
    me = &(lock->nodes[cpu]);
    tmp = me;

    if (me->next == NULL) {
        if (cmpxchg(&lock->slock, tmp, NULL) == me) {
            /* mcs_lock I am the last. */
            return;
        }
        while (me->next == NULL)
            continue;
    }

    /* mcs_lock pass to next. */
    me->next->waiting = 0;
}

#define mcs_spin_lock_irqsave(lock, flags) \
    do {                        \
        local_irq_save(flags);  \
        mcs_spin_lock(lock);    \
    } while (0)

#define mcs_spin_unlock_irqrestore(lock, flags) \
    do {                            \
        mcs_spin_unlock(lock);    \
        local_irq_restore(flags);   \
    } while (0)




#endif
#endif /* DESC("������") */
/** @} */


/** \addtogroup VOS_MUTEX ������
    ע��:  init��destroy��������ʹ�ã������ʹ������Windows(����)�ϻ���ھ��й©
    @{ 
*/
#if DESC("������")
#if defined(WIN32) || defined(_PCLINT_)

/** \brief �������Ͷ��� */
typedef struct 
{
    HANDLE hMutex;
} LVOS_MUTEX_S;

#elif defined(__LINUX_USR__)
typedef pthread_mutex_t LVOS_MUTEX_S;
#elif defined(__KERNEL__)
typedef struct semaphore LVOS_MUTEX_S;
#endif

#if defined(WIN32) || defined(_PCLINT_) || defined(__KERNEL__)

void LVOS_mutex_init_inner(LVOS_MUTEX_S *v_pMutex, OSP_U32 v_uiPid);
/** \brief ��ʼ�������� */
#define LVOS_mutex_init(v_pMutex) LVOS_mutex_init_inner(v_pMutex, MY_PID)

/** \brief ���������� */
void LVOS_mutex_lock(LVOS_MUTEX_S *v_pMutex);

/** \brief ���������� */
void LVOS_mutex_unlock(LVOS_MUTEX_S *v_pMutex);

void LVOS_mutex_destroy_inner(LVOS_MUTEX_S *v_pMutex, OSP_U32 v_uiPid);
/** \brief ���ٻ����� */
#define LVOS_mutex_destroy(v_pMutex) LVOS_mutex_destroy_inner(v_pMutex, MY_PID)

#else
#define LVOS_mutex_init(v_mutex)     pthread_mutex_init(v_mutex, NULL)
#define LVOS_mutex_lock(v_mutex)     pthread_mutex_lock(v_mutex)
#define LVOS_mutex_unlock(v_mutex)   pthread_mutex_unlock(v_mutex)
#define LVOS_mutex_destroy(v_mutex)  pthread_mutex_destroy(v_mutex)
#endif

#endif /* DESC("������") */
/** @} */



/** \addtogroup VOS_SEMA �ź���
    ע��: ����ʹ���ź��������⣬��ʹ�û�����\n
    ע��:  init��destroy��������ʹ�ã������ʹ������Windows(����)�ϻ���ھ��й©
    @{ 
*/
#if DESC("�ź���")
#if defined(WIN32) || defined(_PCLINT_)

/** \brief �ź������Ͷ��� */
typedef struct 
{
    HANDLE hHandle;
    atomic_t count;
} LVOS_SEMAPHORE_S;

#elif defined(__LINUX_USR__)
typedef sem_t LVOS_SEMAPHORE_S;
#elif defined(__KERNEL__)
typedef struct semaphore LVOS_SEMAPHORE_S;
#endif

#if defined(WIN32) || defined(_PCLINT_) || defined(__KERNEL__)


void LVOS_sema_init_inner(LVOS_SEMAPHORE_S *v_pSema, OSP_S32 v_iVal, OSP_U32 v_uiPid);
/** \brief ��ʼ���ź��� */
#define LVOS_sema_init(v_pSema, v_iVal) LVOS_sema_init_inner(v_pSema, v_iVal, MY_PID)

/** \brief �ź���down */
void LVOS_sema_down(LVOS_SEMAPHORE_S *v_pSema);

/** \brief �ź���up */
void LVOS_sema_up(LVOS_SEMAPHORE_S *v_pSema);

void LVOS_sema_destroy_inner(LVOS_SEMAPHORE_S *v_pSema, OSP_U32 v_uiPid);
/** \brief �����ź��� */
#define LVOS_sema_destroy(v_pSema) LVOS_sema_destroy_inner(v_pSema, MY_PID)

#else
#define LVOS_sema_init(sem, val)    sem_init(sem, 0, val)
#define LVOS_sema_down(sem)\
do{ \
    int _ret = -1;\
    _ret = sem_wait((sem)); \
    while (0 != _ret && EINTR == errno) \
    { \
        _ret = sem_wait((sem));\
    }\
}while(0)
#define LVOS_sema_up(sem)           sem_post(sem)
#define LVOS_sema_destroy(sem)      sem_destroy(sem)
#endif

#endif /* DESC("�ź���") */
/** @} */

#endif

#endif


