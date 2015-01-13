/* 
 * 
 * File: kernel/include/mm.h
 * Author: Christoph Landgraf
 * Purpose: Interface for memory management
 * 
 */

#ifndef KERNEL_MM_H_INCLUDED
#define KERNEL_MM_H_INCLUDED

#include <kernel/multiboot.h>

void mm_init(multiboot_info_t * mbinfo);

#endif
