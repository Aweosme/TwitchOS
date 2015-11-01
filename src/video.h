#include "util/string.h"

#ifndef TWITCHOS_VIDEO_H
#define TWITCHOS_VIDEO_H

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t *terminal_buffer;

/* Hardware text mode color constants. */
enum vga_color {
	COLOR_BLACK,
	COLOR_DARK_BLUE,
	COLOR_DARK_GREEN,
	COLOR_BLUE,
	COLOR_DARK_RED,
	COLOR_PURPLE,
	COLOR_ORANGE,
	COLOR_LIGHT_GRAY,
	COLOR_DARK_GRAY,
	COLOR_LIGHT_BLUE,
	COLOR_GREEN,
	COLOR_AQUA,
	COLOR_RED,
	COLOR_MAGENTA,
	COLOR_YELLOW,
	COLOR_WHITE,
	COLOR_RAINBOW = COLOR_BLUE | COLOR_DARK_RED | COLOR_YELLOW /* lol */
};

/**
 * Initialize video
 */
void init_video();

/**
 * Initialize video with the given foreground and background colors
 */
void init_video_with_colors(enum vga_color, enum vga_color);

/**
 * Set terminal colors using vga_color enum
 */
uint8_t make_color(enum vga_color, enum vga_color);

/**
 * Return a 16 bit number that represents a character and the terminal color
 */
uint16_t make_vgaentry(char, uint8_t);

/**
 * Set the character and color at a given point on screen
 */
void putentryat(char, uint8_t, size_t, size_t);

void clearscreen();

void setcursorpos(int x, int y);

void scrolldown();

void scrollup();

#endif //TWITCHOS_VIDEO_H
