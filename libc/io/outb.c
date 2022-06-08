#include <asm/io.h>

void outb(uint16_t port, uint8_t value) {
	asm volatile ("outb %%al,%%dx": :"d" (port), "a" (value));
}