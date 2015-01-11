/*
 *
 * File:    kernel/src/arch/x86/mm.c
 * Author:  Christoph Landgraf
 * Purpose: Memory Management on x86 architecture
 *
 */

#include <stdint.h>

// We address 4GB memory at a page size of 4KiB: 1M Pages.
// Our bitmap must be 1M / 32 = 32k words
#define FRAME_MAP_SIZE 32768

uint32_t frame_map[FRAME_MAP_SIZE];

inline uint32_t frame_is_used(uint32_t frame)
{
    return frame_map[frame / 32] & (1 << (frame % 32));
}

inline void frame_set(uint32_t frame)
{
    frame_map[frame / 32] |= (1 << (frame % 32));
}

inline void frame_clr(uint32_t frame)
{
    frame_map[frame / 32] &= ~(1 << (frame % 32));
}


void mm_init()
{

}

