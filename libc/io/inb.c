#include <asm/io.h>

uint8_t inb(uint16_t port) {
	uint8_t retval;
	asm volatile ("inb %%dx, %%al":"=a" (retval):"d" (port));
	return retval;
}