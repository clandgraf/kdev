/*
 *
 * File:    kernel/include/ds/list.h
 * Author:  Christoph Landgraf
 * Purpose: Interface for doubly linked lists
 *
 */

#ifndef KERNEL_DS_LLIST_H_INCLUDED
#define KERNEL_DS_LLIST_H_INCLUDED

#include <kernel/ds/ds.h>

typedef struct list_node_struct {
    struct list_node_struct * next;
    struct list_node_struct * prev;
    
} list_node_t;

#define LIST_T list_node_t _list_node;

/* Returns the entry at list_node_t ln */
#define list_entry(ln) \
    container_of(ln)

/* Returns the list_node_t of the provided struct */
#define list_node(le) \
    ((le)._list_node)

/* if struct contains a LIST_T entry this will return next entry in this list */
#define list_entry_next(ln) \
    ((ln)->_list_node.next == 0 ? 0 : container_of(__typeof__(*(ln)), (ln)->_list_node.next, _list_node))

/* if struct contains a LIST_T entry this will return previous entry in this list */
#define list_entry_prev(ln) \
    ((ln)->_list_node.prev == 0 ? 0 : container_of(typeof(*(ln)), (ln)->_list_node.prev, _list_node))

void list_insert(list_node_t * list, list_node_t * node);
void list_remove(list_node_t * node);

#endif
