/*
 * File:    fb.h
 * Author:  Christoph Landgraf
 * Purpose: Definitions for VGA Text Mode
 *
 * Source: http://en.wikipedia.org/wiki/VGA-compatible_text_mode
 *
 * TODO: split general function definitions from VGA specific stuff
 *
 */

#ifndef __VGA_TEXT_MODE_H__
#define __VGA_TEXT_MODE_H__

#include <stdint.h>

typedef enum vga_tm_color {       /* Color Attributes for VGA mode */
    COLOR_BLACK         = 0x0,
    COLOR_BLUE          = 0x1,
    COLOR_GREEN         = 0x2,
    COLOR_CYAN          = 0x3,
    COLOR_RED           = 0x4,
    COLOR_MAGENTA       = 0x5,
    COLOR_BROWN         = 0x6,
    COLOR_LIGHT_GREY    = 0x7,
    
    COLOR_DARK_GREY     = 0x8,
    COLOR_LIGHT_BLUE    = 0x9,
    COLOR_LIGHT_GREEN   = 0xA,
    COLOR_LIGHT_CYAN    = 0xB,
    COLOR_LIGHT_RED     = 0xC,
    COLOR_LIGHT_MAGENTA = 0xD,
    COLOR_LIGHT_BROWN   = 0xE,
    COLOR_WHITE         = 0xF,
} vga_tm_color_t;

typedef uint8_t  vga_tm_attrib_t; /* Attribute type. Combines Foreground and Background Color */
typedef uint16_t vga_tm_cell_t;   /* Cell type. Combines Attribute and Character */

#include <kernel/console.h>

#endif
