/*
 *
 * File:    kernel/include/ds/ds.h
 * Author:  Christoph Landgraf
 * Purpose: Definitions for implementation of generic 
 *          data structures
 *
 */

#ifndef KERNEL_DS_DS_H_INCLUDED
#define KERNEL_DS_DS_H_INCLUDED

#include <stddef.h>

/*
  Base Macro for generic data structures inspired by Linux.

  container_of returns a pointer to the enclosing structure object of
  structure member ds. Parameter member must be the identifier of member 
  ds in the definition of the enclosing structure and parameter ds_type 
  must be the type name of the enclosing structure.

  Example (though a better one is the list implementation in llist.h): 

    typedef struct enclosing_type_struct {
      int i;
      int _ds_node;
    } enclosing_type;

    enclosing_type et;

    container_of(enclosing_type, &et._ds_node, _ds_node) == &et
 */
#define container_of(ds_type, ds, member) \
    ((ds_type *)((void *)ds - (void *)offsetof(ds_type, member)))

#endif
