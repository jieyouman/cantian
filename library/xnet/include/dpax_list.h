/**
* Copyright(C), 2014 - 2015, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
*/

/**
* @file dpax_list.h
* @brief ���������������ӿ�
* @verbatim 
   �������������������������ӿ�
   Ŀ���û���SPA,POOL
   ʹ��Լ����NA
   ����Ӱ��: no
@endverbatim
*/

#ifndef __DPAX_LIST_H__
#define __DPAX_LIST_H__

#include "vos_win/vos/lvos_list.h"

typedef struct list_head list_head_t;

#if 0
/**
 *@defgroup  osax_list �������
 *@ingroup osax
*/
#include "dp_base.h"

#ifdef WIN32

#include "lvos_list.h"

#else

#include <unistd.h>
#include <errno.h>
#include <stddef.h>
#include "dpax_segment.h"
#include "dpax_macro.h"

#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#ifdef WIN32

#define DPAX_INIT_LIST_HEAD		INIT_LIST_HEAD
#define dpax_list_for_each		list_for_each
#define dpax_list_for_each_safe	list_for_each_safe
#define dpax_list_entry			list_entry
#define dpax_list_add			list_add
#define dpax_list_add_tail		list_add_tail
#define dpax_list_del_init		list_del_init
#define dpax_list_del			list_del
#define dpax_list_for_del_each	list_for_del_each
#define dpax_list_move			list_move
#define dpax_list_move_tail		list_move_tail
#define dpax_list_empty			list_empty
#define dpax_list_splice		list_splice
#define dpax_list_splice_init	list_splice_init
#define dpax_list_for_each_entry	list_for_each_entry

 #define dpax_list_first_entry(ptr, type, member) \
    dpax_list_entry((ptr)->next, type, member)

 #define dpax_list_next_entry(pos, type, member) \
    dpax_list_entry((pos)->member.next, type, member)

#define dpax_list_for_each_entry_safe(pos, n, type, head, member) /*lint -save -e26*/  \
    for (pos = dpax_list_entry((head)->next, type, member),  \
        n = dpax_list_entry(pos->member.next, type, member); \
        &pos->member != (head);         \
        pos = n, n = dpax_list_entry(n->member.next, type, member)) /*lint -restore*/

#define dpax_list_for_each_entry_reverse(pos, type, head, member)      \
    for (pos = dpax_list_entry((head)->prev, type, member);  \
        &pos->member != (head);         \
        pos = dpax_list_entry(pos->member.prev, type, member))

#define dpax_list_for_each_entry_safe_reverse(pos, n, type, head, member)       \
    for (pos = dpax_list_entry((head)->prev, type, member),  \
        n = dpax_list_entry(pos->member.prev, type, member); \
        &pos->member != (head);                                    \
        pos = n, n = dpax_list_entry(n->member.prev, type, member))

#define dpax_list_for_each_entry_continue(pos, type, head, member)     \
    for (pos = dpax_list_entry(pos->member.next, type, member);  \
        &pos->member != (head);                 \
        pos = dpax_list_entry(pos->member.next, type, member))

#define dpax_list_for_del_all(pos, type, listHead, name)  \
do {                                                    \
    dpax_list_for_del_each(pos, listHead) {               \
        name = dpax_list_entry(pos, type, listNode);      \
        dpax_list_del(pos);                               \
        free(name);                                     \
    }                                                   \
} while(0)

#else

#ifndef LIST_POISON1
#define LIST_POISON1  ((void *) 0x00100100)
#endif
#ifndef LIST_POISON2
#define LIST_POISON2  ((void *) 0x00200200)
#endif
/**
* @brief 
  ��������: ����ṹ����
  ʹ��Լ��: NA
  ����Ӱ��: no
*/
struct list_head {
        struct list_head *next, *prev;   /**< ǰ������ָ��  */
};

typedef struct list_head list_head_t;

/**
* ����ͷ���ṹ��ʼ��
*/
#define DPAX_LIST_HEAD_INIT(name) { &(name), &(name) }
 
#define DPAX_LIST_HEAD(name) \
        struct list_head name = DPAX_LIST_HEAD_INIT(name)

/** 
 * ����ͷ��ʼ�� 
 */
#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) \
    struct list_head name = LIST_HEAD_INIT(name)

/**
* @brief ��������: ��ʼ������Ԫ�ؽڵ�
* @verbatim
  Ŀ���û�: ����
  ʹ��Լ��: ptr����Ϊ��
  ����Ӱ��: no
@endverbatim

* @param[in]  ptr - ����ڵ�ָ��
* @retval NA
*/
#define DPAX_INIT_LIST_NODE(ptr)   { (ptr)->next = (struct list_head *)LIST_POISON1; (ptr)->prev = (struct list_head *)LIST_POISON2; }

/**
* @brief ��������: �ж�����ڵ��Ƿ��ʼ��
* @verbatim
  Ŀ���û�: ����
  ʹ��Լ��: ptr����Ϊ��
  ����Ӱ��: no
@endverbatim

* @param[in]  ptr - ����ڵ�ָ��
* @retval true  - �ѳ�ʼ��
        false - δ��ʼ��
*/
#define IS_LIST_NODE_INIT(ptr)  ((LIST_POISON1 == (void*)((ptr)->next)) && (LIST_POISON2 == (void*)((ptr)->prev)))

/**
* @brief ��������: ͨ�������ַ��ýṹ��ָ��
* @verbatim
  Ŀ���û�: ����
  ʹ��Լ��: head����Ϊ��
  ����Ӱ��: no
@endverbatim

* @param[in]  _ptr   - �ṹ�������Ա������ָ��
* @param[in]  _type  - �ṹ������
* @param[in]  _memb  - �ṹ�������������
* @retval �ṹ��ָ��
*/
#define dpax_list_entry(_ptr, _type, _memb)   /*lint -e718 -e746 -e78 -e516 */ \
                container_of(_ptr, _type, _memb)   /*lint +e718 +e746 +e78 +e516 */
				
/**
* @brief ��������: ����������
* @verbatim
  Ŀ���û�: ����
  ʹ��Լ��: head����Ϊ��
  ����Ӱ��: no
@endverbatim

* @param[in]  pos    - ����������α�ڵ�
* @param[in]  head  - �����ͷ���
* @retval NA
*/
#define dpax_list_for_each(pos, head) \
    for (pos = (head)->next; pos != (head); pos = pos->next)

/**
* @brief ��������: ����������
* @verbatim
  Ŀ���û�: ����
  ʹ��Լ��: �û����������ڱ���������ɾ������Ԫ�أ����򽫵�����ѭ��
  ����Ӱ��: no
@endverbatim

* @param[in]  pos    - ����������α�ڵ�
* @param[in]  head  - �����ͷ���
* @retval NA
*/
#define dpax_list_for_del_each(pos, head) \
    for (pos = (head)->next; pos != (head); \
            pos = (head)->next)

/**
* @brief ��������: ����������,֧��ɾ������Ԫ��
* @verbatim
  Ŀ���û�: ����
  ʹ��Լ��: head����Ϊ��
  ����Ӱ��: no
@endverbatim

* @param[in]  pos    - ����������α�ڵ�
* @param[in]  n      - ������ʱ����Ľڵ�
* @param[in]  head  - �����ͷ���
* @retval NA
*/
#define dpax_list_for_each_safe(pos, n, head) \
    for (pos = (head)->next, n = pos->next; pos != (head); \
         pos = n, n = pos->next)


/**
* @brief ��������: ��ȡ����ĵ�һ��Ԫ��
* @verbatim
  Ŀ���û�: ����
  ʹ��Լ��: list����Ϊ��
  ����Ӱ��: no
@endverbatim

* @param[in]  ptr    - Ҫȡ��Ԫ�ص�����ͷ
* @param[in]  type  - ������Ƕ��Ľṹ������
* @param[in]  member  - �ṹ�������Ա����
* @retval NA
*/
 #define dpax_list_first_entry(ptr, type, member) \
    dpax_list_entry((ptr)->next, type, member)

/**
* @brief ��������: ��ȡ����ڵ����һ��Ԫ��
* @verbatim
  Ŀ���û�: ����
  ʹ��Լ��: list����Ϊ��
  ����Ӱ��: no
@endverbatim

* @param[in]  pos    - ����������α�ڵ�
* @param[in]  type  - ������Ƕ��Ľṹ������
* @param[in]  member  - �ṹ�������Ա����
* @retval NA
*/
 #define dpax_list_next_entry(pos, type, member) \
    dpax_list_entry((pos)->member.next, type, member)

/**
* @brief ��������: ������������ȡ�������ڽṹ��ָ��
* @verbatim
  Ŀ���û�: ����
  ʹ��Լ��: head����Ϊ��
  ����Ӱ��: no
@endverbatim

* @param[in]  pos    - ����������α�ڵ�
* @param[in]  head  - �����ͷ���
* @param[in]  member  - �ṹ�������Ա����
* @retval NA
*/
#define dpax_list_for_each_entry(pos, type, head, member)                          \
    for (pos = dpax_list_entry((head)->next, type, member);      \
         &pos->member != (head);                                    \
         pos = dpax_list_entry(pos->member.next, type, member))

/**
* @brief ��������: ������������ȡ�������ڽṹ��ָ�룬����������֧��ɾ������
* @verbatim
  Ŀ���û�: ����
  ʹ��Լ��: head����Ϊ��
  ����Ӱ��: no
@endverbatim

* @param[in]  pos    - ����������α�ڵ�
* @param[in]  head  - �����ͷ���
* @param[in]  n      - �������ڽṹ�建��ڵ�
* @param[in]  member  - �ṹ�������Ա����
* @retval NA
*/
#define dpax_list_for_each_entry_safe(pos, n, type, head, member) /*lint -save -e26*/  \
    for (pos = dpax_list_entry((head)->next, type, member),  \
        n = dpax_list_entry(pos->member.next, type, member); \
        &pos->member != (head);         \
        pos = n, n = dpax_list_entry(n->member.next, type, member)) /*lint -restore*/


/**
* @brief ��������: ��ǰ����������ȡ�������ڽṹ��ָ��
* @verbatim
  Ŀ���û�: ����
  ʹ��Լ��: head����Ϊ��, ���������в�֧��ɾ������
  ����Ӱ��: no
@endverbatim

* @param[in]  pos    - ����������α�ڵ�
* @param[in]  head  - �����ͷ���
* @param[in]  member  - �ṹ�������Ա����
* @retval NA
*/
#define dpax_list_for_each_entry_reverse(pos, type, head, member)      \
    for (pos = dpax_list_entry((head)->prev, type, member);  \
        &pos->member != (head);         \
        pos = dpax_list_entry(pos->member.prev, type, member))
		
/**
* @brief ��������: ��ǰ����������ȡ�������ڽṹ��ָ�룬����������֧��ɾ������
* @verbatim
  Ŀ���û�: ����
  ʹ��Լ��: head����Ϊ��
  ����Ӱ��: no
@endverbatim

* @param[in]  pos    - ����������α�ڵ�
* @param[in]  n      - �������ڽṹ�建��ڵ�
* @param[in]  head  - �����ͷ���
* @param[in]  member  - �ṹ�������Ա����
* @retval NA
*/
#define dpax_list_for_each_entry_safe_reverse(pos, n, type, head, member)       \
    for (pos = dpax_list_entry((head)->prev, type, member),  \
        n = dpax_list_entry(pos->member.prev, type, member); \
        &pos->member != (head);                                    \
        pos = n, n = dpax_list_entry(n->member.prev, type, member))

/**
* @brief ��������: �ӵ�ǰ�ڵ㴦��������������ȡ�������ڽṹ��ָ��
* @verbatim
  Ŀ���û�: ����
  ʹ��Լ��: head����Ϊ�գ�posָ�벻��Ϊ�գ����������в�֧��ɾ������
  ����Ӱ��: no
@endverbatim

* @param[in]  pos    - ����������α�ڵ�
* @param[in]  head  - �����ͷ���
* @param[in]  member  - �ṹ�������Ա����
* @retval NA
*/
#define dpax_list_for_each_entry_continue(pos, type, head, member)     \
    for (pos = dpax_list_entry(pos->member.next, type, member);  \
        &pos->member != (head);                 \
        pos = dpax_list_entry(pos->member.next, type, member))

/** * @brief ��ʼ������ͷ
 * @param[in] ptr ����ṹָ��
   \return ��
*/
#define INIT_LIST_HEAD(ptr) { \
        (ptr)->next = (ptr); (ptr)->prev = (ptr); \
    }


/**
* @brief ��������: ��ʼ������ͷ������ͷ��ǰ���ͺ����ڵ㶼ָ������
* @verbatim
  Ŀ���û�: ����
  ʹ��Լ��: ������list����Ϊ��
  ����Ӱ��: no
@endverbatim

* @param[in]  list    - ����ָ��
* @retval NA
*/
static inline void DPAX_INIT_LIST_HEAD(struct list_head *list)
{
    list->next = list;
    list->prev = list;
}

static inline void __list_add(struct list_head *newnode,
			           struct list_head *prev,
			           struct list_head *next)
{
	next->prev = newnode;
	newnode->next = next;
	newnode->prev = prev;
	prev->next = newnode;
}

/**
* @brief ��������: ����µ�����Ԫ�ص�����ͷ
* @verbatim
  Ŀ���û�: ����
  ʹ��Լ��: newnode��head����Ϊ��
  ����Ӱ��: no
@endverbatim

* @param[in]  newnode    - ���������ṹָ��
* @param[in]  head  - ����ͷ�ṹָ��
* @retval NA
*/
static inline void dpax_list_add(struct list_head *newnode, struct list_head *head)
{

#if (defined DPAX_DEBUG_SUPPORT)
    if (!IS_LIST_NODE_INIT(newnode))
    {
        DPAX_DBG_PANIC();
    }
#endif

    __list_add(newnode, head, head->next);
}

/**
* @brief ��������: ����µ�����Ԫ�ص�����β
* @verbatim
  Ŀ���û�: ����
  ʹ��Լ��: newnode��head����Ϊ��
  ����Ӱ��: no
@endverbatim

* @param[in]  newnode    - ���������ṹָ��
* @param[in]  head  - ����ͷ�ṹָ��
* @retval NA
*/
static inline void dpax_list_add_tail(struct list_head *newnode, struct list_head *head)
{
#if (defined DPAX_DEBUG_SUPPORT)
    if (!IS_LIST_NODE_INIT(newnode))
    {
        DPAX_DBG_PANIC();
    }
#endif
    __list_add(newnode, head->prev, head);
}

static inline void dpax_list_insert(struct list_head* new_node, struct list_head* prev_node, struct list_head* next_node)
{
    __list_add(new_node, prev_node, next_node);
}


static inline void __list_del(struct list_head * prev, struct list_head * next)
{
    next->prev = prev;
    prev->next = next;
}

/**
* @brief ��������: ������ɾ���ڵ�
* @verbatim
  Ŀ���û�: ����
  ʹ��Լ��: entry����Ϊ��
  ����Ӱ��: no
@endverbatim

* @param[in]  entry    - ��ɾ��������ڵ�
* @retval NA
*/
static inline void dpax_list_del(struct list_head *entry)
{
#if (defined DPAX_DEBUG_SUPPORT)
    if (IS_LIST_NODE_INIT(entry))
    {
        DPAX_DBG_PANIC();
    }
#endif    
    __list_del(entry->prev, entry->next);
    DPAX_INIT_LIST_NODE(entry);
}

/**
 * list_empty - tests whether a list is empty
 * @head: the list to test.
 */
static inline int list_empty(const struct list_head *head)
{
	return head->next == head;
}


static inline list_head_t* dpax_list_get_first(list_head_t* head)
{
    return list_empty(head) ? NULL : head->next;
}

static inline list_head_t* dpax_list_get_tail(list_head_t* head)
{

    return  (head->prev == head) ? NULL : head->prev;
}

static inline list_head_t* dpax_list_del_first(list_head_t* head)
{
    list_head_t* ret = NULL;

    ret = head->next;
    if (ret == head)
    {
        /* the list is free */
        return NULL;
    }
    else
    {
        dpax_list_del(ret);
    }

    return ret;
}



/**
* @brief ��������: ���ڵ������ɾ�������³�ʼ���ýڵ�
* @verbatim
  Ŀ���û�: ����
  ʹ��Լ��: entry����Ϊ��
  ����Ӱ��: no
@endverbatim

* @param[in]  entry    - ��ɾ��������ڵ�
* @retval NA
*/
static inline void dpax_list_del_init(struct list_head *entry)
{
#if (defined DPAX_DEBUG_SUPPORT)
    if (IS_LIST_NODE_INIT(entry))
    {
        DPAX_DBG_PANIC();
    }
#endif   

    __list_del(entry->prev, entry->next);
    DPAX_INIT_LIST_HEAD(entry);
}

static inline list_head_t* dpax_list_del_tail(list_head_t* head)
{
    list_head_t* ret;

    ret = head->prev;
    if (ret == head)
    {
        /* the list is free */
        return NULL;
    }
    else
    {
        dpax_list_del(ret);
    }

    return ret;
}



#define dpax_list_for_del_all(pos, type, listHead, name)  \
do {                                                    \
    dpax_list_for_del_each(pos, listHead) {               \
        name = dpax_list_entry(pos, type, listNode);      \
        dpax_list_del(pos);                               \
        free(name);                                     \
    }                                                   \
} while(0)

/**
* @brief ��������: ����ǰ����ڵ��ƶ�������ͷ
* @verbatim
  Ŀ���û�: ����
  ʹ��Լ��: list��Ϊ�գ�head��Ϊ��
  ����Ӱ��: no
@endverbatim

* @param[in]  list    - ��ǰ��Ҫ�ƶ��Ľڵ�ָ��
* @param[in]  head  - ����ͷָ��
* @retval NA
*/
static inline void dpax_list_move(struct list_head *list, struct list_head *head)
{
    dpax_list_del(list);
    dpax_list_add(list, head);
}

/**
* @brief ��������: ����ǰ����ڵ��ƶ�������β
* @verbatim
  Ŀ���û�: ����
  ʹ��Լ��: list��Ϊ�գ�head��Ϊ��
  ����Ӱ��: no
@endverbatim

* @param[in]  list    - ��ǰ��Ҫ�ƶ��Ľڵ�ָ��
* @param[in]  head  - ����ͷָ��
* @retval NA
*/
static inline void dpax_list_move_tail(struct list_head *list, struct list_head *head)
{
    dpax_list_del(list);
    dpax_list_add_tail(list, head);
}

/**
* @brief ��������: �ж������Ƿ�Ϊ��
* @verbatim
  Ŀ���û�: ����
  ʹ��Լ��: head��Ϊ��
  ����Ӱ��: no
@endverbatim

* @param[in]  head  - ����ͷָ��
* @retval NA
*/
static inline int dpax_list_empty(const struct list_head *head)
{
    return head->next == head;
}

/**
* @brief ��������: �жϱ�ͷ��ǰһ�����ͺ�һ������Ƿ�Ϊ�䱾�����ͬʱ�����򷵻�false�����򷵻�ֵΪtrue��
* @verbatim
  Ŀ���û�: ����
  ʹ��Լ��: head��Ϊ��
  ����Ӱ��: no
@endverbatim

* @param[in]  head  - ����ͷָ��
* @retval NA
*/
static inline int dpax_list_empty_careful(const struct list_head *head)
{
	struct list_head *next = head->next;
	return (next == head) && (next == head->prev);
}

/**
* @brief ��������: �жϵ�ǰ�ڵ��Ƿ�Ϊ��ĩ�ڵ�
* @verbatim
  Ŀ���û�: ����
  ʹ��Լ��: list��Ϊ��
  ����Ӱ��: no
@endverbatim

* @param[in]  list    - ��ǰ�ڵ�ָ��
* @param[in]  head  - ����ͷָ��
* @retval NA
*/
static inline int dpax_list_is_last(const struct list_head *list,
                const struct list_head *head)
{
    return list->next == head;
}

#define INIT_LIST_NODE(ptr)   { (ptr)->next = (struct list_head *)LIST_POISON1; (ptr)->prev = (struct list_head *)LIST_POISON2; }



/**
* @brief ��������: ��ǰ��������
* @verbatim
	Ŀ���û�: ����
	ʹ��Լ��: ���������в�����ɾ������Ԫ��
	����Ӱ��: no
@endverbatim
* @param[in]  pos	  - ��ǰ��ָ�������ڵ�
* @param[in]  head	 - ����ͷָ��
* @retval NA
*/
#define dpax_list_for_each_prev(pos, head) \
            for (pos = (head)->prev; pos != (head); pos = pos->prev) 

/**
* @brief ��������: ��������
* @verbatim
	Ŀ���û�: ����
	ʹ��Լ��: list��Ϊ�գ�head��Ϊ�գ�����������֧���û�����ɾ������Ԫ�أ��û������о����Ƿ�ɾ��
	����Ӱ��: no
@endverbatim
* @param[in]  pos	  - ��ǰ��ָ�������ڵ�
* @param[in]  p	  - ѭ����ʱֵ
* @param[in]  head	 - ����ͷָ��
* @retval NA
*/           
#define dpax_list_for_each_prev_safe(pos, p, head)\
                        for(pos = (head)->prev, p = pos->prev; pos != (head);\
                            pos = p, p = pos->prev)

/*����dsware ����*/
static inline void dpax_list_replace(list_head_t* old_node, list_head_t* new_node)
{
    new_node->next = old_node->next;
    new_node->next->prev = new_node;
    new_node->prev = old_node->prev;
    new_node->prev->next = new_node;
    DPAX_INIT_LIST_HEAD(old_node);
}

/*����dsware ����*/
static inline int dpax_list_check_in_queue(list_head_t* node)
{
    if ((node->next == node) && (node->prev == node))
    {
        return 0;
    }

    return 1;
}

/*����dsware ����*/
static inline void dpax_list_merge(list_head_t *first_list, list_head_t *second_list)
{
    if (dpax_list_empty(second_list))
    {
        return;
    }

    if (dpax_list_empty(first_list))
    {
        dpax_list_replace(second_list, first_list);
        return;
    }

    list_head_t *first_list_end = first_list->prev;
    list_head_t *second_list_begin = second_list->next;
    list_head_t *second_list_end = second_list->prev;

    first_list_end->next = second_list_begin;
    second_list_begin->prev = first_list_end;
    second_list_end->next = first_list;
    first_list->prev = second_list_end;

    DPAX_INIT_LIST_HEAD(second_list);
}

/*����dsware ����*/
static inline int dpax_list_node_is_tail(list_head_t* node, list_head_t* head)
{
    if (node == head->prev)
    {
        return 1;
    }

    return 0;
}

/*����dsware ����*/
static inline int dpax_list_node_is_first(list_head_t* node, list_head_t* head)
{
    if (node == head->next)
    {
        return 1;
    }

    return 0;
}


#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif

#endif 
