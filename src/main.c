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
  printf("               ,-.' \--\_\n");
  printf("              ((`-.__\   )\n");
  printf("               \`'    @ (_\n");
  printf("               (        (_)\n");
  printf("              ,'`-._(`-._/\n");
  printf("           ,-'    )&&) ))\n");
  printf("        ,-'      /&&&%-'\n");
  printf("      ,' __  ,- {&&&&/\n");
  printf("     / ,'  \|   |\&&'\\n");
  printf("    (       |   |' \  `--.\n");
  printf("(%--'\   ,--.\   `-.`-._)))\n");
  printf(" `---'`-/__)))`-._)))\n\n");
  printf("Exiting...");

  /*
   * ^^ printf not implemented? It is, look above, lolk :P
   * is putchar implemented? It is, look above xD
   * right xd  FEELS LIKE TOVALDS xD
   * #ForgettingTheCodeAlreadyExists
   * well acutally at least in theory at some point linux kernel and in general linux organization of system started to be overcomplicated comparing
   * to eg. Minix that's why it's not used as good example on Unis, clear UNIX was more straight forward. 
   * Minix kernel takes like 20 seconds to compile and it's made from like... 20 .c files
   *
   * how are you going to display the terminal?
	 * there's something called character device, i dunno how it exactly works but long story short - OS is sending characters, 
   * not pixels, we don't bother with font or stuff like that
   * I see, can it understand the colours? I guess so, but Minix at least doesn't handle colors properly in terminal
   * But duh it's 1998 OS, maybe then VGA standard didn't support colors yet 
   * Ok, I see. The address 0xB8000 used for terminal buffer is a VGA text buffer
   *
   * I guess it's VGA standard to support characters
   *
   * One does not simply work is how the fuck bunch of random people didn't destroy everything yet? It's against rules of internetz
   * I have backups anyway, it's just really nice that nobody has decided to completely be a troll yet
   * (well I mean there were trolls earlier but they're gone now)
   * 
   * Code is looking amazing guys lol
   * What code? :3
   *
   * We don't have character device support yet do we?
   *
   * Check this out:
   * There are interrupts that might do that
   * https://en.wikipedia.org/wiki/INT_10H
   * This is worth reading too:
	 * http://mikeos.sourceforge.net/write-your-own-os.html
   * He implements an OS in 30 lines and it can print output!!
   
   * If it's not zero, we call int 10h (interrupt our code and go to the BIOS), which reads the value in the AH register (0Eh)
   * we set up before. Ah, says the BIOS - 0Eh in the AH register means "print the character in the AL register to the screen!". 
   *
   * I might actually go ahead and try to compile this.
   * Also, we should join a freenode IRC channel.
   * Yeah compile it, I really want to see how it works (upload it to imgur and paste a link here or something)
   * I'm gonna post this to Reddit later lol (but I'm gonna do it when we finish pretty much)
   * Anyone compiling it? 
   
   is there a channel we can join? That would be fuN :) don't have a mic :s
  * I've never done sessions like this but it's really fun ! xD >>>>>>Can anybody hear me?<<<<<< There's an option to do video/voice chat on the right-hand side of this website apparently
  */
  
  /* Verdict:
  can you tell me the steps / tools you used to run it too? also can we make an IRC or decide on a channel
   * So after some work, I got it to compile. And... (Let me upload the image)
   * WOHOOO
   * I'm gonna compile it too
   * Whoops.
   * https://ptpb.pw/GYKO.png There you go.
   * Wow, this is awesome
   * :D
   * SICK MAN ! :D
   * The puppy had lots of backslashes.
   * I had to escape these, also, I didn't know which assembler the boot.asm was for so I quickly wrote my own (identical version but for as) And initialise() never got called
   * I'm proud of you, random internet people. We did well.
   * Note to self: try not to delete the code when copying <-- wanted to try compiling it :P It's okay lol I've been making backups. I'm a random person who trys to program stuff but never gets any ideas
   * Who is the person writing this? What is your background?which one
   *  Me, the guy who compiled and pasted the link, I didn't write most of this, but I've written an OS similar to this before. I'm a software developer.
   *  Oh, and I run archlinux (me too!). I'm 19 << Thank you.
   * The code is from http://wiki.osdev.org/Bare_Bones < I thought it looked familiar :P
   * Nice, I'm a system engineer / security researcher :)  << Thank you
   * I'm a CS and Mathematics student
   * I'm a CS student 21y/o
   * I'm 15 - Okay we did really good guys I'm pretty proud
   * Do we want to keep developing this? We can github it. Yeah :D
   * I'll make the project hold on : Okay, my github is Outlasted :), How long did it last?, sorry..... longer then you xD
   * https://github.com/DonkeyCore/TwitchOS <-- Gonna start putting code in it, make pull requests and do stuff lol
   * The next step of this project would be to actually organize it a bit. Maybe kbuild? Or maybe kbuild is overkill :P
   * Organization would be nice, so how are we gonna organize the file structure? src folder would be obvious
   * src, build, docs, arch/ (for the asm)?
   * Yeah okay
   
   
   * Put the names of everyone who contributed in commit message or readme :)
   * Will do, put all your names or aliases that you want to go by below:
   * DonkeyCore
   * sdsmith
   * Outlasted
   * ob6160
   * kieranellis (github) - i havn't really done much...
   * EliteTK (github account)
   * Alrighty will add you guys to the readme nice :)
   * Thanks you.
   * can we get an Irc set up now?
   You guys are awesome. You too :)
   https://webchat.freenode.net/ #asmosdev
   * Readme updated
   * Let's talk in IRC and keep these comments clean ok
   */
  
  

  
  return 0;

}  
