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
    node->next = list->next;
    node->prev = list;
    list->next->prev = node;
    list->next = node;
}

void list_remove(list_node_t * node)
{
    node->next->prev = node->prev;
    node->prev->next = node->next;
}
