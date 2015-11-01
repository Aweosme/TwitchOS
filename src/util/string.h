#include <stddef.h>
#include <stdint.h>

#ifndef TWITCHOS_STRING_H
#define TWITCHOS_STRING_H

/**
 * Get the length of the given string
 */
size_t strlen(const char *str);

/**
 * Copies a block of memory from one location to another
 */
void *memcpy(void *dest, const void *src, int count);

/**
 * Sets a block of memory to a single value
 */
void *memset(void *dest, char val, int count);

/**
 * Moves a block of memory from one location to another
 */
void* memmove(void* dest, const void* src, size_t num);

#endif //TWITCHOS_STRING_H
