#include <stdio.h>

#include <kernel/tty.h>

void kernel_main(void* boot_data) { // TODO: newline character most certainly does not work
	terminal_initialize();
	printf("Kernel Starting...\n");

	printf("Boot data at %p", boot_data);
}
