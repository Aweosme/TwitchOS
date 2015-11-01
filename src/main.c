#include "util/string.h"
#include "util/stdio.h"
#include "mem/gdt.h"
#include "video.h"

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
	init_video();

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
//	clearscreen();
	char* thing;
	itoa(42, thing, 10);
	printf(thing);
	int count = 0;
	while (true) {

		while (count < 5) {

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
