#include <stddef.h> /* Almost forgot to add these essential headers! */
#include <stdint.h> /* We can include these because they come with the compiler */

/* Hardware text mode color constants. */
enum vga_color { /* Why does an _ENUM_ need = 0x0..0xF, it's guaranteed to start at 0 and increment by 1*/
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

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

uint8_t make_color(enum vga_color fg, enum vga_color bg) { /* This is how we can make our awesome 16 terminal colors yay */
	return fg | bg << 4;
}

uint16_t make_vgaentry(char c, uint8_t color) {
	uint16_t c16 = c;
	uint16_t color16 = color;
	return c16 | color16 << 8;
}

size_t strlen(const char* str) { /* There are no standard libraries, we do everything ourselves yay */
	size_t ret = 0;
	while(str[ret] != 0)
		ret++;
	return ret;
}

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;


void initialize() {
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = make_color(COLOR_LIGHT_GRAY, COLOR_BLACK);
	/* 0xB8000 is a VGA text buffer */
	terminal_buffer = (uint16_t*) 0xB8000;
	for(size_t y = 0; y < VGA_HEIGHT; y++) {
		for(size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = make_vgaentry(' ', terminal_color);
		}
	}
}

void setcolor(uint8_t color) {
	terminal_color = color;
}

void putentryat(char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = make_vgaentry(c, color);
}

void clearscreen() {
	for(size_t i  = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
		terminal_buffer[i] = terminal_color;
	}
	terminal_row = 0;
	terminal_column = 0;
}

void putchar(char c) {
	if(c == '\n') {
		terminal_row++;
		terminal_column = 0;
	} else {
		putentryat(c, terminal_color, terminal_column, terminal_row);
		if(++terminal_column == VGA_WIDTH) {
			terminal_column = 0;
			if(++terminal_row == VGA_HEIGHT) {
				terminal_row = 0;
			}
		}
	}
}

void printf(const char* data) {
	size_t datalen = strlen(data);
	for(size_t i = 0; i < datalen; i++)
		putchar(data[i]);
}

int kernel_main() {
	initialize();
	printf("Hello, World!\n\n");
	printf("Puppy:\n\n");
	printf("                          ,--.\n");
	printf("                   _/ <`-'\n");
	printf("               ,-.' \\--\\_\n");
	printf("              ((`-.__\\   )\n");
	printf("               \\`'    @ (_\n");
	printf("               (        (_)\n");
	printf("              ,'`-._(`-._/\n");
	printf("           ,-'    )&&) ))\n");
	printf("        ,-'      /&&&%-'\n");
	printf("      ,' __  ,- {&&&&/\n");
	printf("     / ,'  \\|   |\\&&'\\\n");
	printf("    (       |   |' \\  `--.\n");
	printf("(%--'\\   ,--.\\   `-.`-._)))\n");
	printf(" `---'`-/__)))`-._)))\n\n");
	clearscreen();
	printf("Exiting...");



	return 0;

}
