#include <p_mem.h>

#include <kernel/multiboot.h>
#include <stdlib.h>
#include <stdio.h>

unsigned int global_p_mem_descriptor_size = sizeof(p_mem_descriptor_t);
size_t global_num_p_mem_descriptors = 0;
p_mem_descriptor_t *global_p_mem_descriptors = NULL;

// Aligns passed value to a page boundary, behaves like ceil()
void* align(void* addr) {
	if (((unsigned int) addr) % PAGE_SIZE == 0) {
		return addr;
	}
	return addr + (PAGE_SIZE - (((int) addr) % PAGE_SIZE));
}

int p_mem_init(multiboot_info_t *mbd, void* kernel_end_location) {
	// Check for valid memory map
	if (!CHECK_FLAG(mbd->flags, 6)) {
		printf("Error: No memory map detected");
		abort();
	}

	// Initialize globals
	global_p_mem_descriptor_size = sizeof(p_mem_descriptor_t);
	global_num_p_mem_descriptors = 0;
	global_p_mem_descriptors = (p_mem_descriptor_t*) kernel_end_location;

	// Loop through memory map
	unsigned int i;
	int j;
	for (i = 0, j = 0; i < mbd->mmap_length; i += sizeof(multiboot_memory_map_t), j++) {
		multiboot_memory_map_t *mmmt = (multiboot_memory_map_t*) (mbd->mmap_addr + i);

		p_mem_descriptor_t *curr_desc = P_MEM_GET_PTR(j);

		curr_desc->addr = (void*) mmmt->addr;
		curr_desc->pages = mmmt->len / PAGE_SIZE; // Len is in bytes
		curr_desc->free = mmmt->type == MULTIBOOT_MEMORY_AVAILABLE;
		curr_desc->remove_entry = 0;

		if (mmmt->len % PAGE_SIZE > 0) {
			curr_desc->pages++;
		}

		//printf("%d pages, at %p, %s\n", curr_desc->pages, curr_desc->addr, curr_desc->free == 1 ? "(Free)" : " ");
	}
	global_num_p_mem_descriptors = j;

	// Make sure mem <1M isn't used for anything, will be updated to actual palloc function later
	// Remember to separate list entries under/over 1M when updating
	for (i = 0; i < global_num_p_mem_descriptors; i++) {
		p_mem_descriptor_t *desc = P_MEM_GET_PTR(i);
		// Align addresses on page boundaries
		desc->addr = align(desc->addr);
		// Don't allocate memory under 1M
		if (desc->addr < 0x100000) {
			desc->free = 0;
		}
	}

	p_mem_clean_list();

	// Testing, remove later
	for (i = 0; i < global_num_p_mem_descriptors; i++) {
		p_mem_descriptor_t *desc = P_MEM_GET_PTR(i);
		printf("%p, %p: %d, %d\n", desc, desc->addr, desc->pages, desc->free);
	}

	return P_MEM_SUCCESS;
}