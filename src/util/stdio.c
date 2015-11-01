#include "stdio.h"

void putchar(char c) {
	if (c == '\n') {
		terminal_row++;
		terminal_column = 0;
	} else {
		putentryat(c, terminal_color, terminal_column, terminal_row);
		if (++terminal_column == VGA_WIDTH) {
			terminal_column = 0;
			if (++terminal_row == VGA_HEIGHT) {
				terminal_row = 0;
			}
		}
	}
}

void printf(const char *data) {
	size_t datalen = strlen(data);
	for (size_t i = 0; i < datalen; i++)
		putchar(data[i]);
}