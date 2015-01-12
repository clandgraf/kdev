/*
 *
 * File:    kernel/src/arch/x86/mm.c
 * Author:  Christoph Landgraf
 * Purpose: Memory Management on x86 architecture
 *
 */

#include <stdint.h>
#include <kernel/mm.h>
#include <kernel/panic.h>
#include <kernel/klog.h>

// We address 4GB memory at a page size of 4KiB: 1M Pages.
// Our bitmap must be 1M / 32 = 32k words
#define FRAME_MAP_SIZE 32768

uint32_t frame_map[FRAME_MAP_SIZE];

inline uint32_t mm_frame_is_used(uint32_t frame)
{
    return mm_frame_is_used_(frame / 32, frame % 32);
}

inline uint32_t mm_frame_is_used_(uint32_t idx, uint32_t off)
{
    return frame_map[idx] & (1 << off);
}

inline void mm_frame_set(uint32_t frame)
{
    mm_frame_set_(frame / 32, frame % 32);
}

inline void mm_frame_set_(uint32_t idx, uint32_t off)
{
    frame_map[idx] |= (1 << off);
}

inline void mm_frame_clr(uint32_t frame)
{
    mm_frame_clr_(frame / 32, frame % 32);
}

inline void mm_frame_clr_(uint32_t idx, uint32_t off)
{
    frame_map[idx] &= ~(1 << off);
}


uint32_t mm_alloc_frame(void)
{
    for (uint32_t idx = 0; idx < FRAME_MAP_SIZE; idx++)
        for (uint32_t off = 0; off < 32; off++)
            if (!mm_frame_is_used_(idx, off)) {
                mm_frame_set_(idx, off);
                return idx * 32 + off;
            }

    klog_info("No free frames found.");
    panic();

    // Never reached, compiler does not know
    return 0;
}


void mm_init(mboot_info_t * mbinfo)
{
  // Clear all frames
  for (uint32_t i = 0; i < FRAME_MAP_SIZE; i++)
    frame_map[i] = 0;

  // Set memory map used

  // Set kernel memory used
}
