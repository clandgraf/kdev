/*
 *
 * File:    kernel/src/ds/list.h
 * Author:  Christoph Landgraf
 * Purpose: Functions for list_node_t
 *
 */

#include <kernel/ds/list.h>

void list_insert(list_node_t * list, list_node_t * node)
{
    node->next = list;
    node->prev = list->prev;
    list->prev = node;
}

void list_remove(list_node_t * node)
{
    if (node->next)
	node->next->prev = node->prev;

    if (node->prev)
	node->prev->next = node->next;
}
