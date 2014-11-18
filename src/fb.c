/*
 *
 * File:   fb.c
 * Author: Christoph Landgraf
 *
 */

#include <stddef.h>
#include <stdint.h>

#include "fb.h"

static const size_t FB_WIDTH  = 80;
static const size_t FB_HEIGHT = 25;

size_t      fb_row;
size_t      fb_column;

fb_attrib_t fb_attrib;  /* Stores the current attributes used */
fb_cell_t * fb_buffer;  /* Stores the RAM Area for Text-Mode */


#define FB_INDEX(x, y) (y * FB_WIDTH + x)


fb_attrib_t fb_make_attrib(fb_color_t foreground, fb_color_t background)
{
  return foreground | background << 4;
}


fb_cell_t fb_make_cell(char c, fb_attrib_t color)
{
  uint16_t chr16 = c;
  uint16_t col16 = color;

  return chr16 | col16 << 8;
}


void fb_clear()
{
  for (size_t y = 0; y < FB_HEIGHT; y++)
    for (size_t x = 0; x < FB_WIDTH; x++)
      fb_buffer[FB_INDEX(x, y)] = 
	fb_make_cell(' ', fb_make_attrib(COLOR_LIGHT_GREY, COLOR_BLACK));

  fb_row = 0;
  fb_column = 0;
}


/* Initialize the Framebuffer */
void fb_init()
{
  fb_attrib = fb_make_attrib(COLOR_LIGHT_GREY, COLOR_BLACK);
  fb_buffer = (uint16_t *) 0xB8000;    // TODO this might be different for monochrome screens
  fb_clear();
}


void fb_setcolor(fb_attrib_t attrib)
{
  fb_attrib = attrib;
}


void fb_setcellat(char c, fb_attrib_t attrib, int x, int y)
{
  fb_buffer[FB_INDEX(x, y)] = fb_make_cell(c, attrib);
}


void fb_putchar(char c)
{
  fb_setcellat(c, fb_attrib, fb_row, fb_column);

  if (++fb_row == FB_WIDTH) {
    fb_row = 0;
    if (++fb_column == FB_HEIGHT)
      fb_column = 0;
  }
}

void fb_writestr(const char * str)
{
  while (*str)
    fb_putchar(*str++);
}
