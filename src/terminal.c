#include "terminal.h"
//#include "util/string.h"

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

void setcolor(uint8_t color) {
	terminal_color = color;
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

void newline(unsigned int num) {
	for(int i = 0; i < num; i++) {
		printf("\n");
	}
}

void clearscreen() {
	for(size_t i  = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
		terminal_buffer[i] = terminal_color;
	}
	terminal_row = 0;
	terminal_column = 0;
}

void setcursorpos(int x, int y) {
	terminal_row = x;
	terminal_column = y;
}

void scrolldown() {
	memcpy(terminal_buffer, terminal_buffer + 80, sizeof(uint16_t) * VGA_WIDTH * (VGA_HEIGHT-1));
	for(int i = 80*24; i < (80*25); i++) {
		terminal_buffer[i] = make_vgaentry(' ', terminal_color);
	}
}


void scrollup() {
	memmove(terminal_buffer + 80, terminal_buffer, sizeof(uint16_t) * 80 * 24);
	for(int i = 0; i < 80; i++) {
		terminal_buffer[i] = make_vgaentry(' ', terminal_color);
	}
}
