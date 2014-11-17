/*
 * File:   fb.h
 * Author: Christoph Landgraf
 *
 * Source: http://en.wikipedia.org/wiki/VGA-compatible_text_mode
 *
 */

#ifndef __FB_H__
#define __FB_H__


/* Color Attributes for VGA mode */

typedef enum fb_color {
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
} fb_color_t;


void fb_clear();
void fb_init();


#endif
