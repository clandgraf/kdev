/*
 *
 * File:    string.h
 * Author:  Christoph Landgraf
 * Purpose: Defines the libc function memcpy.
 *
 */

#include <string.h>

void * memcpy(void * dest, void * src, size_t n)
{
    uint8_t * dest_ = (uint8_t *) dest;
    uint8_t * src_  = (uint8_t *) src;

    while (n-- > 0)
	*dest_++ = *src_++;

    return dest;
}
