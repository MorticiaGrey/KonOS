#include <stdio.h>
#include <stdlib.h>

#include <kernel/tty.h>
#include <kernel/bootdata.h>

#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))
#define MULTIBOOT_HEADER_FLAGS         0x00000003

void kernel_main(void* boot_data) { // TODO: newline character most certainly does not work
	terminal_initialize();
	printf("Kernel Starting...\n");

	// Data from multiboot
	printf("Boot data located at %p...\n", boot_data);

	multiboot_info_t *mbi = (multiboot_info_t*) boot_data;

	char buffer[MAX_ITOA_DIGITS];
	itoa(mbi->flags, buffer, 2);
	printf("Flags set to %s...\n", buffer);

	if (CHECK_FLAG (mbi->flags, 0)) {
		printf("lower 0x%X, upper 0x%X\n", mbi->mem_lower, mbi->mem_upper);
	}

	if (CHECK_FLAG (mbi->flags, 6)) {
		printf("mmap flag set...\n");
		printf("mmap at %p...\n", mbi->mmap_addr);
		memory_map_t *mmap = (memory_map_t*) mbi->mmap_addr;

		//for (mmap = (memory_map_t *) mbi->mmap_addr;
		//	(unsigned long) mmap < mbi->mmap_addr + mbi->mmap_length;
		//	mmap = (memory_map_t *) ((unsigned long) mmap + mmap->size + sizeof (mmap->size)));

		printf("size 0x%X\nlength 0x%X%X\ntype 0x%X", (unsigned) mmap->size, (unsigned) mmap->length_high, (unsigned) mmap->length_low, (unsigned) mmap->type);
	}
}