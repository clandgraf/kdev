/*
 *
 * File:    kernel/include/ds/llist.h
 * Author:  Christoph Landgraf
 * Purpose: Interface for doubly linked lists
 *
 */

#ifndef KERNEL_DS_LLIST_H_INCLUDED
#define KERNEL_DS_LLIST_H_INCLUDED

typedef struct llist_node {
    struct llist_node * next;
    struct llist_node * prev;
    
} llist_node_t;

typedef llist_node_t * list_head;

#define LLIST_T llist_node_t _list_node;

#define llist_next(ln) \
    ((ln)->_list_node.next == 0 ? 0 : container_of(typeof(*(ln)), (ln)->_list_node.next, _list_node))

#define llist_prev(ln) \
    ((ln)->_list_node.prev == 0 ? 0 : container_of(typeof(*(ln)), (ln)->_list_node.prev, _list_node))

#endif
