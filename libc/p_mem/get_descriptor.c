#include <p_mem.h>

#include <errno.h>

extern int errno = 0;

// Make this easier to read
#define CHECK_ADDRESSES(addr, high_addr, low_addr) ((addr) < (high_addr) && (addr) >= (low_addr))

p_mem_descriptor_t *get_descriptor(void* addr) {
	int i;
	p_mem_descriptor_t *desc_high;
	p_mem_descriptor_t *desc;
	for (i = 0; i < global_num_p_mem_descriptors - 1; i++) {
		desc_high = P_MEM_GET_PTR(i + 1);
		desc = P_MEM_GET_PTR(i);
		if (CHECK_ADDRESSES(addr, desc_high->addr, desc->addr)) {
			return desc;
		}
	}
	desc = P_MEM_GET_PTR(global_num_p_mem_descriptors - 1);
	if (CHECK_ADDRESSES(addr, desc->addr + (desc->pages * PAGE_SIZE), desc->addr)) {
		return desc;
	} else {
		errno = EILADD;
		return -1;
	}
}