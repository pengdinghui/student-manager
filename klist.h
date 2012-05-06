#pragma once

struct list_head {
		struct list_head *prev;
		struct list_head *next;
	};

#define   LISt_HEAD(head) struct list_head name = LIST_HEAD_INIT(name)

#define   LIST_HEAD_INIT(head) \
		 {&(head), &(head)}


static inline void init_list_head(struct list_head *node)
{
	node->prev = node;
	node->next = node;
}

static inline void __list_add(	struct list_head *back,
				struct list_head *forward,
				struct list_head *node)
{
	node->next = forward;
	node->prev = back;

	forward->prev = node;
	back->next = node;
}


static inline void list_add(struct list_head *head, 
				struct list_head *node)
{
	__list_add(head, head->next, node);
}

static inline void list_add_tail(struct list_head *head, 
				 struct list_head *node)
{
	__list_add(head->prev, head, node);	
}


static inline void list_del(struct list_head *node)
{
	node->prev->next = node->next;
	node->next->prev = node->prev;
}

static inline void list_del_init(struct list_head *node)
{
	list_del(node);
	init_list_head(node);
}


#define offsetof(type, member) \
	((int)(&(((type *)0)->member)))

//#define container_of(ptr, type, member) \
	((type *)((char *)ptr - offsetof(type, member)))

#define container_of(ptr, type, member) \
 ({ const typeof(((type *)0)->member) *mptr = (ptr);\
  (type *)((char *)mptr - offsetof(type, member));})

#define list_for_each(cur, head) \
	for (cur = (head)->next; cur != (head); cur= cur->next)

#define list_for_each_safe(cur, tmp, head) \
	for (cur = (head)->next; (cur != (head)) && \
		((tmp) = (cur)->next); cur = tmp)

#define list_for_each_entry(pos, head, member) \
	for (pos = container_of((head)->next, typeof(*pos),member); &((pos)->list) !=  (head); pos = container_of((pos)->list.next, typeof(*pos), member))
