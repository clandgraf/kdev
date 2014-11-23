/*
 *
 * File:    libc/include/string.h
 * Author:  Christoph Landgraf
 * Purpose: Defines operations on strings 
 *
 */

#ifndef __STRING_H__
#define __STRING_H__

#include <stddef.h>
#include <stdint.h>

/**
 * @brief Returns the length of string \a str.
 *
 * @param str The string whose length to return.
 * @return The length of the string.
 */
size_t strlen(const char * str);

/**
 * @brief Copies \a n bytes from address \a src 
 *        to address \a dst.
 *
 * @param dst The destination address.
 * @param src The source address.
 * @return The destination address.
 */
void * memcpy(void * dst, void * src, size_t n);

/**
 * @brief Copies \a n bytes from address \a src
 *        to address \a dst. The memory regions
 *        may overlap.
 *
 * @param dst The destination address.
 * @param src The source address.
 * @return The destination address.
 */
void * memmove(void * dst, void * src, size_t n);

/**
 * @brief Sets the first \a n bytes at \a addr 
 *        to value \a value.
 *
 * @param addr The address at which to start
 * @param value The value to which the bytes to set
 * @param n The number of bytes to set
 * @return The address.
 */
uint8_t * memset(uint8_t * addr, uint8_t value, size_t n);


#endif
