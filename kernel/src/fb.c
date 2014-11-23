/*
 *
 * File:   kernel/src/fb.c
 * Author: Christoph Landgraf
 *
 */

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/fb.h>
#include <kernel/arch/i386/io.h>

static const size_t VGA_CRTC_CTRL = 0x3d4;
static const size_t VGA_CRTC_DATA = 0x3d5;

static const size_t VGA_CURSOR_HI = 0x0e;
static const size_t VGA_CURSOR_LO = 0x0f;

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


void fb_setcursor(int row, int col)
{
    uint16_t idx = FB_INDEX(col, row);
    
    outb(VGA_CRTC_CTRL, VGA_CURSOR_LO); // Select low port
    outb(VGA_CRTC_DATA, (uint8_t) idx & 0xff);

    outb(VGA_CRTC_CTRL, VGA_CURSOR_HI); // Select hi port
    outb(VGA_CRTC_DATA, (uint8_t) (idx >> 8) & 0xff);
}


void fb_clear()
{
    for (size_t y = 0; y < FB_HEIGHT; y++)
	for (size_t x = 0; x < FB_WIDTH; x++)
	    fb_buffer[FB_INDEX(x, y)] = 
		fb_make_cell(' ', fb_make_attrib(COLOR_LIGHT_GREY, COLOR_BLACK));

    fb_row = 0;
    fb_column = 0;

    fb_setcursor(fb_row, fb_column);
}


/* Initialize the Framebuffer */
void fb_init()
{
    fb_attrib = fb_make_attrib(COLOR_LIGHT_GREY, COLOR_BLACK);
    fb_buffer = (uint16_t *) 0xB8000;    // TODO this is different for monochrome screens
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


void fb_newline()
{
    fb_column = 0;
    if (++fb_row == FB_HEIGHT) {
	// Make room for new row
	memmove(fb_buffer,
		fb_buffer + FB_INDEX(0, 1),
		FB_WIDTH * (FB_HEIGHT - 1) * 2);
	fb_row--;

	// Clear new row
	for (unsigned int x = 0; x < FB_WIDTH; x++)
	    fb_setcellat(' ', fb_attrib, x, fb_row);
    }
}


void fb_putchar(char c)
{
    if (c == '\n')
	fb_newline();
    else {
	fb_setcellat(c, fb_attrib, fb_column, fb_row);

	if (++fb_column == FB_WIDTH)
	    fb_newline();
    }

    fb_setcursor(fb_row, fb_column);
}
