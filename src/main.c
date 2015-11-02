#include "util/string.h"
#include "util/stdio.h"
#include "descriptor_tables/gdt.h"
#include "descriptor_tables/idt.h"
#include "terminal.h"

#define true 1
#define false 0

//THIS IS BAD :(
void sleep(unsigned long delay) {
	for (unsigned long i = 0; i < delay; i++) {
		__asm__ __volatile__ ("nop");
	}
}

int kernel_main() {
	init_gdt();
	init_idt();
	init_video();
	
	setcolor(make_color(COLOR_GREEN, COLOR_BLACK));
	printf("Hello, World!");
	newline(5);
	setcolor(make_color(COLOR_ORANGE, COLOR_BLACK));
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

	int count = 0;
	
	//Some delay before bouncing
	while (count < 10) {
            sleep(100000000);
            count++;
        }
	count = 0;
    while (true) {

        while (count < 5) {
            sleep(100000000);
            scrolldown();
            count++;
        }

        while (count < 10) {
            sleep(100000000);
            scrollup();
            count++;

        }

        if (count % 10 == 0) {
            count = 0;
        }

    }
	printf("Exiting...");


	return 0;
}
