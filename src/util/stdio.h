#include "string.h"
#include "../video.h" //In the future none of these functions should access the video buffer directly

#ifndef TWITCHOS_STDIO_H
#define TWITCHOS_STDIO_H

/**
 * Write a character to a given point on screen
 */
void putchar(char);

/**
 * Write a string directly to the screen (for now)
 */
void printf(const char *);

/**
 * Convert integer to string
 */
char* itoa(int num, char* ret, int base);

/**
 * Return the absolute value of an integer
 */
unsigned int abs(int num);
  
#endif //TWITCHOS_STDIO_H
