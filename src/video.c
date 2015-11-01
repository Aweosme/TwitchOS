#include "video.h"

void init_video_with_colors(enum vga_color fg, enum vga_color bg) {
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = make_color(fg, bg);
	/* 0xB8000 is a VGA text buffer */
	terminal_buffer = (uint16_t *) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = make_vgaentry(' ', terminal_color);
		}
	}
}

void init_video() {
	init_video_with_colors(COLOR_LIGHT_GRAY, COLOR_BLACK);
}

uint8_t make_color(enum vga_color fg, enum vga_color bg) {
	return fg | bg << 4;
}

uint16_t make_vgaentry(char c, uint8_t color) {
	uint16_t c16 = c;
	uint16_t color16 = color;
	return c16 | color16 << 8;
}

void putentryat(char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = make_vgaentry(c, color);
}