#include "util/string.h"
#include "util/stdio.h"
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

	while(true) {
		init_video();
	}
/*

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
*/
	printf("Exiting...");


	return 0;
}
