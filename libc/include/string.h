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
 * @brief Searches the first \a n bytes at \a addr for the first occurence of \a chr
 *
 * @param addr The address at which to start the search.
 * @param chr The character to search for.
 * @param n The number of bytes to search.
 * @return The address at which \a chr occured first, or NULL if \a chr was not found.
 */
void * memchr(const void * addr, int chr, size_t n);

/**
 * @brief Compare to memory regions.
 *
 * @param s1 The offset of the first region.
 * @param s2 The offset of the second region.
 * @param n The length of the two regions.
 * @return 0 if regions are equal, negative if first region 
 *         is smaller, positive if first region is larger.
 */
int memcmp(const void * s1, const void * s2, size_t n);

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
void * memset(void * addr, int value, size_t n);

/**
 * @brief Appends string \a src to string \a dest.
 *
 * @param dest The string to which \a src is appended
 * @param src The string that is appended to \a dest.
 * @return \a dest.
 */
char * strcat(char * dest, const char * src);

/**
 * @brief Searches for the first occurence of \a c in \a str.
 *
 * @param str The string in which to search.
 * @param c The character for which to search.
 * @return NULL if \a c is not found, else the address 
 *         of the first occurence.
 */
char * strchr(const char * str, int c);

/**
 * @brief Compares two strings.
 *
 * @param str1 The first string.
 * @param str2 The second string.
 * @return an integer less than, greater than or equal to 0 if 
 *         \a str1 is less than, greater than or matches \a str2.
 */
int strcmp(const char * str1, const char * str2);

/**
 * @brief Copies a string to a buffer.
 *
 * @param dest the buffer to copy to.
 * @param src the string to copy.
 * @return a pointer to the buffer copied to.
 */
char * strcpy(char * dest, const char * src);

/**
 * @brief Returns the length of string \a str.
 *
 * @param str The string whose length to return.
 * @return The length of the string.
 */
size_t strlen(const char * str);

#endif
