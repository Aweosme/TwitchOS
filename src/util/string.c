#include "string.h"

size_t strlen(const char *str) {
	size_t ret = 0;
	while (str[ret] != 0) {
		ret++;
	}
	return ret;
}

void *memcpy(void *dest, const void *src, int count)
{
	const char *sp = (const char *)src;
	char *dp = (char *)dest;
	for(; count != 0; count--) *dp++ = *sp++;
	return dest;
}

void *memset(void *dest, char val, int count)
{
	char *temp = (char *)dest;
	for( ; count != 0; count--) *temp++ = val;
	return dest;
}

void* memmove(void* dest, const void* src, size_t num) {
	if (dest > src) {
		uint8_t* src_8 = ((uint8_t*) src) + num - 1;
		uint8_t* dest_8 = ((uint8_t*) dest) + num - 1;
		while (num--) {
			*dest_8-- = *src_8--;
		}

	} else {
		uint8_t* src_8 = (uint8_t*) src;
		uint8_t* dest_8 = (uint8_t*) dest;
		while (num--) {
			*dest_8++ = *src_8++;
		}
	}

	return dest;
}