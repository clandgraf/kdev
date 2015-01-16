/*
 *
 * File:    kernel/src/arch/x86/mm.c
 * Author:  Christoph Landgraf
 * Purpose: Memory Management on x86 architecture
 *          This code assumes a 32bit address space, which is valid for x86 architecture.
 *          Therefore it ignores the upper 32 bit of GRUB memory map fields.
 *
 */

#include <stdint.h>
#include <kernel/mm.h>
#include <kernel/panic.h>
#include <kernel/klog.h>
#include <kernel/arch/x86/linker.h>


// Page Directory Flags
#define PAGING_FLAG_MAPPED    0x01
#define PAGING_FLAG_WRITEABLE 0x02
#define PAGING_FLAG_USERSPACE 0x04
#define PAGING_FLAG_WRITE_THR 0x08
#define PAGING_FLAG_NO_CACHE  0x10
#define PAGING_FLAG_DIRTY     0x20

struct page_dir_entry_struct {
    unsigned int flags        : 9;
    unsigned int flags_free   : 3;
    unsigned int page_tbl_ptr : 20;
    
} __attribute__ ((__packed__));

typedef struct page_dir_entry_struct page_dir_entry_t;

page_dir_entry_t * page_directory;
page_dir_entry_t pd_space[1024];

// We address 4GB memory at a page size of 4KiB: 1M Pages.
// Our bitmap must be 1M / 32 = 32k words
#define FRAME_MAP_SIZE 32768

uint32_t frame_map[FRAME_MAP_SIZE];

inline uint32_t mm_frame_is_used_(uint32_t idx, uint32_t off)
{
    return frame_map[idx] & (1 << off);
}

inline uint32_t mm_frame_is_used(uint32_t frame)
{
    return mm_frame_is_used_(frame / 32, frame % 32);
}

inline void mm_frame_set_(uint32_t idx, uint32_t off)
{
    frame_map[idx] |= (1 << off);
}

inline void mm_frame_set(uint32_t frame)
{
    mm_frame_set_(frame / 32, frame % 32);
}

inline void mm_frame_clr_(uint32_t idx, uint32_t off)
{
    frame_map[idx] &= ~(1 << off);
}

inline void mm_frame_clr(uint32_t frame)
{
    mm_frame_clr_(frame / 32, frame % 32);
}


uint32_t mm_alloc_frame(void)
{
    for (uint32_t idx = 0; idx < FRAME_MAP_SIZE; idx++) {
        if (frame_map[idx] == 0xffffffff)
            continue;

        for (uint32_t off = 0; off < 32; off++)
            if (!mm_frame_is_used_(idx, off)) {
                mm_frame_set_(idx, off);
                return (idx * 32 + off) * 0x1000;
            }
    }

    klog_info("No free frames found.");
    panic();

    // Never reached, but compiler does not know
    return 0;
}

const char * mm_type_strings[] = {
    "undefined",
    "available",
    "reserved",
    "acpi",
    "nvs",
    "badram"
};

extern void mm_enable_paging(void);
extern void mm_load_pagedir(page_dir_entry_t * page_dir);

void mm_map_page_paging_disabled(uint32_t vaddr, uint32_t paddr)
{
    uint32_t page_idx = vaddr / 4096;

    uint32_t page_dir_idx = page_idx / 1024;
    uint32_t page_tbl_idx = page_idx % 1024;

    uint32_t frame_ptr;

    // Allocate Frame for page table and map it
    if (!(page_directory[page_dir_idx].flags & PAGING_FLAG_MAPPED)) {
        frame_ptr = mm_alloc_frame();

        ((uint32_t *)page_directory)[page_dir_idx] =
            (frame_ptr & 0xfffff000) | PAGING_FLAG_MAPPED | PAGING_FLAG_WRITEABLE;
    }
    // or simply retrieve it
    else frame_ptr = ((uint32_t *)page_directory)[page_dir_idx] & 0xfffff000;     

    // Create entry in page_table
    ((uint32_t *)frame_ptr)[page_tbl_idx] =
        (paddr & 0xfffff000) | PAGING_FLAG_MAPPED | PAGING_FLAG_WRITEABLE;

    asm volatile("invlpg %0" : : "m" (*(char*)vaddr));
}

page_dir_entry_t * mm_create_context(void)
{
    page_dir_entry_t * pd = (page_dir_entry_t *) mm_alloc_frame();
    for (int i = 0; i < 1024; i++)
        ((uint32_t *) pd)[i] = 0;

    // TODO create self reference
    
    return pd;
}

void mm_init_mmap(multiboot_info_t * mbinfo)
{
    // First we init all frames used
    for (uint32_t i = 0; i < FRAME_MAP_SIZE; i++)
        frame_map[i] = 0xffffffff;
    
    // Use the mboot mmap to clear free frames
    multiboot_memory_map_t * mmap;
    for (mmap = (multiboot_memory_map_t *) mbinfo->mmap_addr;
         (uint32_t) mmap < mbinfo->mmap_addr + mbinfo->mmap_length;
         mmap = (multiboot_memory_map_t *) ((uint32_t) mmap + mmap->size + sizeof(mmap->size))) {

        klog_info (" base = %08x %08x,"
                   " len = %08x %08x: %s\n",
                   (uint32_t) (mmap->addr >> 32),
                   (uint32_t) (mmap->addr & 0xffffffff),
                   (uint32_t) (mmap->len >> 32),
                   (uint32_t) (mmap->len & 0xffffffff),
                   mm_type_strings[mmap->type]);

        // Clear all frames in mmap entry
        if (mmap->type == MULTIBOOT_MEMORY_AVAILABLE)
            for (uint32_t addr = (mmap->addr & 0xffffffff); 
                 addr < (mmap->addr & 0xffffffff) + (mmap->len & 0xffffffff); 
                 addr += 0x1000) {
		
                mm_frame_clr(addr / 0x1000);
            }
    }
    
    // Now we set the kernel frames used again
    uint32_t addr = KERNEL_START;
    for (addr = KERNEL_START; addr < KERNEL_END; addr += 0x1000)
        mm_frame_set(addr / 0x1000);
}

void mm_init(multiboot_info_t * mbinfo)
{
    klog_info("Initializing memory management\n");

    mm_init_mmap(mbinfo);
    page_directory = mm_create_context();

    klog_info("Kernel Page Directory: 0x%04x %04x\n",
              ((uint32_t) page_directory) >> 16,
              ((uint32_t) page_directory) & 0xffff);

    // Map the kernel
    for (uint32_t addr = KERNEL_START; addr < KERNEL_END; addr += 0x1000)
        mm_map_page_paging_disabled(addr, addr);

    // Map video memory
    for (uint32_t addr = 0xb8000; addr < 0xbffff; addr += 0x1000)
        mm_map_page_paging_disabled(addr, addr);

    // Map multiboot structure
    mm_map_page_paging_disabled((uint32_t) mbinfo, (uint32_t) mbinfo);

    // Load kernel pagedir and enable paging
    mm_load_pagedir(page_directory);
    mm_enable_paging();
}
