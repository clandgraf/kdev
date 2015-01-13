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
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

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

static char * itoa(signed int value, char * buffer, uint8_t base)
{
    char tmp[64];

    char * b1 = &tmp[0]; 
    char * b2 = buffer;

    bool sign = (value < 0 && base == 10);
    if (sign)
        value = -value;

    do {
        *(b1++) = digit_to_char[value % base];
        value /= base;
    } while (value > 0);

    if (sign)
        *(b1++) = '-';
    
    while ((*(b2++) = *(--b1)))
        ;

    return buffer;
}

static char * utoa(uint32_t value, char * buffer, uint8_t base)
{
    char tmp[64];

    char * b1 = &tmp[0]; 
    char * b2 = buffer;

    // Write to tmp
    *b1 = '\0';
    b1++;
    
    do {
        *(b1++) = digit_to_char[value % base];
        value /= base;
    } while (value > 0);

    while ((*(b2++) = *(--b1)))
        ;

    return buffer;
}

static void pad(signed int pad_width, bool pad_zero)
{
    char p = pad_zero ? '0' : ' ';
    while (pad_width-- > 0)
        putchar(p);
}

int printf(const char * fmt, ...)
{
    va_list varargs;
    va_start(varargs, fmt);

    static char buffer[64];
    static uint32_t uint;
    static signed int sint;
    
    int cnt = 0;
    while (*fmt) {
        bool pad_zero = false;
        uint32_t padding = 0;

        // Output character and continue with next
	if (*fmt != '%') {
	    putchar(*fmt);
	    cnt++; fmt++;
	    continue;
	}
	
	fmt++;
	
	// Read conversion string, convert and output vararg
next:	switch (*fmt) {
	case '%':
	    putchar('%');
	    cnt++;
	    break;

        // Zero Pad Flag and Width
        case '0':
            if (padding == 0) {
                pad_zero = true;
                fmt++;
                goto next;
            }
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            padding = padding * 10 + ((*fmt) - '0');
            fmt++;
            goto next;

	case 'd':
	case 'i':
            sint = va_arg(varargs, signed int);
            itoa(sint, &buffer[0], 10);
            // TODO apply padding
	    cnt += print_string(&buffer[0]);
	    break;
	case 'o':
            uint = va_arg(varargs, uint32_t);
            utoa(uint, &buffer[0], 8);
            pad(padding - strlen(&buffer[0]), pad_zero);
            cnt += print_string(&buffer[0]);
	    break;
	case 'u':
            uint = va_arg(varargs, uint32_t);
            utoa(uint, &buffer[0], 10);
            pad(padding - strlen(&buffer[0]), pad_zero);
	    cnt += print_string(&buffer[0]);
	    break;
	case 'x':
	case 'X':
            uint = va_arg(varargs, uint32_t);
            utoa(uint, &buffer[0], 16);
            pad(padding - strlen(&buffer[0]), pad_zero);
	    cnt += print_string(&buffer[0]);
	    break;

	case 's':
	    cnt += print_string(va_arg(varargs, const char *));
	    break;
        }

        fmt++;
    }
    
    va_end(varargs);
    
    return cnt;
}
