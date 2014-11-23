/*
 *
 * File:    libc/src/string/memcmp.c
 * Author:  Christoph Landgraf
 * Purpose: Provides the libc function memcmp
 *
 */

#include <string.h>

int memcmp(const void * s1, const void * s2, size_t n)
{
    const uint8_t * s1_ = (const uint8_t *) s1;
    const uint8_t * s2_ = (const uint8_t *) s2;

    while (n-- > 0) {
	if (*s1_ != *s2_)
	    return *s1_ - *s2_;
    }

    return 0;
}
