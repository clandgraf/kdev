/*
 *
 * File:    libc/src/string/memset.c
 * Author:  Christoph Landgraf
 * Purpose: Fill a memory area with a value. 
 *
 */

#include <string.h>

void * memset(void * addr, int value, size_t n)
{
    uint8_t * addr_ = addr;
    uint8_t value_ = value;

    while (n-- > 0)
	*addr_++ = value_;

    return addr;
}
