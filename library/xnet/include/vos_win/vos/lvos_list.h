/******************************************************************************

                  ��Ȩ���� (C), 2008-2008, ��Ϊ�������˿Ƽ����޹�˾

 ******************************************************************************
  �� �� ��   : lvos_list.h
  �� �� ��   : ����
  ��    ��   : x00001559
  ��������   : 2008��6��4��
  ����޸�   :
  ��������   : ��������궨��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2008��6��4��
    ��    ��   : x00001559
    �޸�����   : �����ļ�

******************************************************************************/
/**
    \file  lvos_list.h
    \brief ��������궨�壬�޵������������ƣ������������ж�������
    \note  ֧��windows/linux_kernel/linux_user

    \date 2008-08-19
*/

/** \addtogroup VOS_LIST �������
    ���������Linux����Ľӿ�Ϊԭ�ͷ�װ
    @{ 
*/

#ifndef __LVOS_LIST_H__
#define __LVOS_LIST_H__

#if defined(__LINUX_USR__) || defined(WIN32) || defined(_PCLINT_)

/*
 * These are non-NULL pointers that will result in page faults
 * under normal circumstances, used to verify that nobody uses
 * non-initialized list entries.
 */
#define LIST_POISON1  ((struct list_head *) 0x00100100)
#define LIST_POISON2  ((struct list_head *) 0x00200200)

/* ע�⣬Linux�û�̬��WIN32��list����û�л�����ʱ��� */
/** \brief list�ڵ�ṹ
*/
struct list_head {
    struct list_head *next, *prev;/* next��ָ�룬prevǰָ�� */
};

/** \brief ����ͷ��ʼ�� */
#define LIST_HEAD_INIT(name) { &(name), &(name) }

/** \brief ����ͷ��ʼ�� */
#define LIST_HEAD(name) \
    struct list_head name = LIST_HEAD_INIT(name)

/** \brief ��ʼ������ͷ
    \param[in] ptr ����ṹָ��
    \return ��
*/
#define INIT_LIST_HEAD(ptr) { \
    (ptr)->next = (ptr); (ptr)->prev = (ptr); \
}



static inline void __list_add(struct list_head *new_head,
                  struct list_head *prev,
                  struct list_head *next)
{
    /* ��ӵ����� */
    next->prev = new_head;
    new_head->next = next;
    new_head->prev = prev;
    prev->next = new_head;
}

/** \brief ����µ�����Ԫ�ص�����ͷ
    \param[in] new_head ���������ṹָ��
    \param[in] head ����ͷ�ṹָ��
    \return ��
*/
static inline void list_add(struct list_head *new_head, struct list_head *head)
{
    /* ��ӵ�����ͷ */
    __list_add(new_head, head, head->next);
}
/*lint -sem(list_add2, custodial(1)) */
static inline void list_add2(void *nodeStruct, uint32_t nodeOffset, struct list_head *head)
{
    list_add((struct list_head *)((char *)nodeStruct + nodeOffset), head);
}

/** \brief ����µ�����Ԫ�ص�����β
    \param[in] new_head ���������ṹָ��
    \param[in] head ����ͷ�ṹָ��
    \return ��
*/
static inline void list_add_tail(struct list_head *new_head, struct list_head *head)
{
    /* ��ӵ�����β */
    __list_add(new_head, head->prev, head);
}
/*lint -sem(list_add_tail2, custodial(1)) */
static inline void list_add_tail2(void *nodeStruct, uint32_t nodeOffset, struct list_head *head)
{
    list_add_tail((struct list_head *)((char *)nodeStruct + nodeOffset), head);
}

static inline void __list_del(struct list_head * prev, struct list_head * next)
{
    /* ������ɾ�� */
    next->prev = prev;
    prev->next = next;
}

/** \brief ������ɾ���ڵ�
    \param[in] entry ��ɾ������ṹָ��
    \return ��
*/
static inline void list_del(struct list_head *entry)
{
    /* ɾ�������¼ */
    __list_del(entry->prev, entry->next);
    entry->next = LIST_POISON1;
    entry->prev = LIST_POISON2;
}

/** \brief �ж������Ƿ�Ϊ��
    \param[in] head ����ͷָ��
    \return ��
*/
static inline int list_empty(struct list_head *head)
{
    /* �ж������Ƿ�Ϊ�� */
    return head->next == head;
}

/** \brief ɾ��ָ������Ԫ�ز���ʼ��
    \param[in] entry ��ɾ������ʼ��������Ԫ��
    \return ��
*/
static inline void list_del_init(struct list_head *entry)
{
    __list_del(entry->prev, entry->next);
    INIT_LIST_HEAD(entry); 
}

/** \brief ת������Ԫ�ص�������ͷ
    \param[in] list �����������ͷ
    \param[in] head �����������ͷ
    \return ��
*/
static inline void list_move(struct list_head *list, struct list_head *head)
{
    __list_del(list->prev, list->next);
    list_add(list, head);
}

/** \brief ת������Ԫ�ص�������β
    \param[in] list �����������ͷ
    \param[in] head �����������ͷ
    \return ��
*/
static inline void list_move_tail(struct list_head *list, struct list_head *head)
{
    __list_del(list->prev, list->next);
    list_add_tail(list, head);
}

/** \brief ͨ�������ַ��ýṹ��ָ��
    \param[in] ptr ����ṹָ��
    \param[in] type �ṹ������
    \param[in] member �ṹ������������ʾ���ֶ�
    \return ��
*/
#define list_entry(ptr, type, member) \
    ((type *)(void *)((char *)(ptr) - offsetof(type, member)))

/** \brief ����������
    \attention ���������в�����ɾ������Ԫ��
    \param[in] pos ��ǰ��ָ�������ڵ�
    \param[in] head ����ͷָ��
    \return ��
*/
#define list_for_each(pos, head) \
    for (pos = (head)->next; pos != (head); \
            pos = pos->next)

/** \brief ��pos����һ���ڵ�, ����������
    \attention ���������в�����ɾ������Ԫ��
    \param[in] pos ָ��������ڵ�
    \param[in] head ����ͷָ��
    \return ��
*/
#define list_for_each_continue(pos, head)\
        for ((pos) = (pos)->next; (pos) != (head); (pos) = (pos)->next)

/** \brief ����������
    \attention �û����������ڱ���������ɾ������Ԫ�أ����򽫵�����ѭ��
    \param[in] pos ��ǰ��ָ�������ڵ�
    \param[in] head ����ͷָ��
    \return ��
*/
#define list_for_del_each(pos, head) \
    for (pos = (head)->next; pos != (head); \
            pos = (head)->next)

/** \brief ����������
    \attention ����������֧���û�����ɾ������Ԫ�أ��û������о����Ƿ�ɾ��
    \param[in] pos ��ǰ��ָ�������ڵ�
    \param[in] n   ѭ����ʱֵ
    \param[in] head ����ͷָ��
    \return ��
*/
#define list_for_each_safe(pos, n, head) for (pos = (head)->next, n = pos->next; pos != (head); pos = n, n = pos->next)

/** \brief ��pos����һ���ڵ㿪ʼ, ����������
    \attention ����������֧���û�����ɾ������Ԫ�أ��û������о����Ƿ�ɾ��
    \param[in] pos ָ��������ڵ�
    \param[in] n   ѭ����ʱֵ
    \param[in] head ����ͷָ��
    \return ��
*/
#define list_for_each_safe_continue(pos, n, head)\
        for ((pos) = (pos)->next, n = (pos)->next; pos != (head); \
             (pos) = n, n = (pos)->next)


#define list_for_each_prev_safe(pos, p, head)\
        for(pos = (head)->prev, p = pos->prev; pos != (head);\
            pos = p, p = pos->prev)

/** \brief ��ǰ��������
    \attention ���������в�����ɾ������Ԫ��
    \param[in] pos ��ǰ��ָ�������ڵ�
    \param[in] head ����ͷָ��
    \return ��
*/
#define list_for_each_prev(pos, head) \
            for (pos = (head)->prev; pos != (head); pos = pos->prev) 

/** \brief ����������������������ڽṹ��ָ��
    \attention ���������в�����ɾ������Ԫ��
    \param[in] pos �������ڽṹ��ָ��
    \param[in] type �ṹ������
    \param[in] head ����ͷָ��
    \param[in] member �ṹ���Ա��
    \return ��
*/
#define list_for_each_entry(pos, type, head, member)\
                for (pos = list_entry((head)->next, type, member);\
                &pos->member != (head);\
                pos = list_entry(pos->member.next, type, member))

#elif defined(__KERNEL__) /* Linux�ں�̬  */
#include <linux/list.h>

/** \brief ����������
    \attention �û����������ڱ���������ɾ������Ԫ�أ����򽫵�����ѭ��
    \param[in] pos ��ǰ��ָ�������ڵ�
    \param[in] head ����ͷָ��
    \return ��
*/
#define list_for_del_each(pos, head) \
    for (pos = (head)->next; pos != (head); \
            pos = (head)->next)

/** \brief ��pos����һ���ڵ�, ����������
    \attention ���������в�����ɾ������Ԫ��
    \param[in] pos ָ��������ڵ�
    \param[in] head ����ͷָ��
    \return ��
*/
#define list_for_each_continue(pos, head)\
        for ((pos) = (pos)->next; (pos) != (head); (pos) = (pos)->next)

/** \brief ��pos����һ���ڵ㿪ʼ, ����������
    \attention ����������֧���û�����ɾ������Ԫ�أ��û������о����Ƿ�ɾ��
    \param[in] pos ָ��������ڵ�
    \param[in] n   ѭ����ʱֵ
    \param[in] head ����ͷָ��
    \return ��
*/
#define list_for_each_safe_continue(pos, n, head)\
        for ((pos) = (pos)->next, n = (pos)->next; pos != (head); \
             (pos) = n, n = (pos)->next)

#else
#error "platform not specify"
#endif

#define INIT_LIST_NODE(ptr)   { (ptr)->next = LIST_POISON1; (ptr)->prev = LIST_POISON2; }

#define IS_LIST_NODE_INIT(ptr)  ((LIST_POISON1 == (ptr)->next) && (LIST_POISON2 == (ptr)->prev))

#endif /* __LVOS_LIST_H__ */

/** @} */

