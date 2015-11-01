#include <stddef.h> /* Almost forgot to add these essential headers! */
#include <stdint.h> /* We can include these because they come with the compiler */

#include "util/string.h"
#include "util/stdio.h"
#include "video.h"

int kernel_main() {
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
	printf("Exiting...");

	return 0;
}
