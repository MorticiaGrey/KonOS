#include <p_mem.h>

#include <errno.h>

extern int errno = 0;

// Aligns passed value to a page boundary, behaves like ceil()
void* align(void* addr) {
	if (((unsigned int) addr) % PAGE_SIZE == 0) {
		return addr;
	}
	return addr + (PAGE_SIZE - (((int) addr) % PAGE_SIZE));
}

void mark(p_mem_descriptor_t *desc, uint32_t pages) {

}

void *palloc(void* addr, uint32_t pages) {
	// Get relevant entry
	p_mem_descriptor_t *m_desc = (p_mem_descriptor_t*) addr;

	// Split descriptors
	

	// Don't overlap with already taken pages
	if (pages > desc->pages) {
		errno = ERANGE;
		return -1;
	}


}