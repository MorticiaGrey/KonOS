#include <stdio.h>
#include <stdlib.h>
#include <p_mem.h>

#include <kernel/tty.h>

#include <kernel/multiboot.h>

void kernel_main(multiboot_info_t* mbd, multiboot_uint32_t magic, void* kernel_end_location) {
	terminal_initialize();
	//printf("Kernel Starting...\n");

	//printf("Kernel end at %p\n", kernel_end_location);

	// Data from multiboot
	//printf("Boot data located at %p...\n", mbd);

	if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
		printf("Error: Magic not matching (0x%X/0x%X)", magic, MULTIBOOT_BOOTLOADER_MAGIC);
		abort();
	}

	p_mem_init(mbd, kernel_end_location);
}