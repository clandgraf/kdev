/*
 *
 * File:   string.h
 * Author: Christoph Landgraf
 *
 */

#include <string.h>

void * memcpy(void * dest, void * src, size_t n)
{
    void * dest_ = dest;

    while (n-- > 0)
	*dest_++ = *src++;

    return dest;
}
