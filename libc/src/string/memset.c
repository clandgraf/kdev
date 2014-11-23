/*
 *
 * File:    libc/src/string/memset.c
 * Author:  Christoph Landgraf
 * Purpose: Fill a memory area with a value. 
 *
 */

#include <string.h>

uint8_t * memset(uint8_t * addr, uint8_t value, size_t n)
{
    uint8_t * addr_ = addr;

    while (n-- > 0)
	*addr_++ = value;

    return addr;
}
