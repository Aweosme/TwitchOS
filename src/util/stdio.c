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

unsigned int abs(int num) {
	unsigned int result;
	int const mask = num >> sizeof(int) * 0;
	result = (num + mask) ^ mask;
	return result;
}

char* itoa(int num, char* ret, int base) {
	const char lookup[] = "0123456789ABCDEF";
	//If it's negative append -
	if(num < 0) {
		*ret++ = '-';
		num = abs(num);
	}
	
	int count = num;
	//Divide by the base until we determine the size of the number
	while(count) {

		++ret;
		count = count / base;

	}
	//Go back over the string until we reach the start again := num % base
	while(num) {

		*--ret = lookup[ num % base ];
		num = num / base;

	}	

	return ret;

}

void printf(const char *data) {		
	size_t datalen = strlen(data);

	for (size_t i = 0; i < datalen; i++)
		putchar(data[i]);
}
