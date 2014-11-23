/*
 *
 * File:    libc/src/include/stdio.h
 * Author:  Christoph Landgraf
 * Purpose: Provides the libc printf function.
 *
 */

#include <stdio.h>
#include <stddef.h>
#include <stdarg.h>

static const char digit_to_char[] = {
    '0', '1', '2', '3', '4', '5', '6', '7', 
    '8', '9', 'a', 'b', 'c', 'd', 'e', 'f',  
};

static size_t print_string(const char * str)
{
    size_t len = 0;
    
    for (; *str; len++, str++)
	putchar(*str);
    
    return len;
}

static size_t print_signed_r(signed int i, unsigned int base)
{
    if (i == 0)
	return 0;

    //TODO this might be problematic due to how % treats negative numbers
    unsigned int cnt = print_signed_r(i / base, base) + 1;
    putchar(digit_to_char[i % base]);
    return cnt;
}

static size_t print_signed(signed int i, unsigned int base)
{
    if (i == 0) {
	putchar('0');
	return 1;
    }

    return print_signed_r(i , base);
}

static size_t print_unsigned_r(unsigned int i, unsigned int base)
{
    if (i == 0)
	return 0;
    
    unsigned int cnt = print_unsigned_r(i / base, base) + 1;
    putchar(digit_to_char[i % base]);
    return cnt;
}

static size_t print_unsigned(unsigned int i, unsigned int base)
{
    if (i == 0) {
	putchar('0');
	return 1;
    }
    
    return print_unsigned_r(i, base);
}

int printf(const char * fmt, ...)
{
    va_list varargs;
    va_start(varargs, fmt);
    
    int cnt = 0;
    while (*fmt) {
	if (*fmt != '%') {
	    // Output character and continue with next
	    putchar(*fmt);
	    cnt++; fmt++;
	    continue;
	}
	
	fmt++;
	
	// Get conversion string, convert and output vararg
	// TODO support flags, field width, precision and length
	switch (*fmt++) {
	case '%':
	    putchar('%');
	    cnt++;
	    break;
	case 's':
	    cnt += print_string(va_arg(varargs, const char *));
	    break;
	case 'd':
	case 'i':
	    cnt += print_signed(va_arg(varargs, signed int), 10);
	    break;
	case 'o':
	    cnt += print_unsigned(va_arg(varargs, unsigned int), 8);
	    break;
	case 'u':
	    cnt += print_unsigned(va_arg(varargs, unsigned int), 10);
	    break;
	case 'x':
	case 'X':
	    cnt += print_unsigned(va_arg(varargs, unsigned int), 16);
	    break;
	}
    }
    
    return cnt;
}
