/*
 *
 * File:    kernel/include/multiboot.h
 * Author:  Christoph Landgraf
 * Purpose: Defines structures and functions for reading 
 *          the multiboot header from GRUB.
 */

#ifndef KERNEL_MULTIBOOT_H_INCLUDED
#define KERNEL_MULTIBOOT_H_INCLUDED

#include <stdint.h>

struct mboot_info {
    uint32_t flags;
    
    uint32_t mem_lo;
    uint32_t mem_hi;

    uint32_t boot_dev;

    uint32_t cmd_line;

    uint32_t mods_count;
    uint32_t mods_addr;
    
    uint16_t syms;

    uint32_t mmap_length;
    uint32_t mmap_addr;

    uint32_t drives_length;
    uint32_t drives_addr;

    uint32_t config_table;
    
    uint32_t bootloader_name;

    uint32_t apm_table;

    uint32_t vbe_control_info;
    uint32_t vbe_mode_info;
    uint16_t vbe_mode;
    uint16_t vbe_interface_seg;
    uint16_t vbe_interface_off;
    uint16_t vbe_interface_len;
};

typedef struct mboot_info mboot_info_t;

#endif
