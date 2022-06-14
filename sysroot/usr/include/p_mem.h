///@file p_mem.h

// This is the header for the physical memory manager. It will mostly handle the lowest level of memory management
// (p_mem stands for physical_memory)

#ifndef _P_MEM_H
#define _P_MEM_H 1

#include <sys/cdefs.h>

#include <kernel/multiboot.h>
#include <stdint.h>
#include <stddef.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif

#define PAGE_SIZE 4096 // How many bytes in a page

// Error codes
#define P_MEM_SUCCESS                0
#define P_MEM_ERROR_PAGE_TAKEN       1
#define P_MEM_ERROR_PAGE_FREE        2
#define ERROR_MMAP_NOT_DETECTED      3

// Writing this line all the time is annoying, converts from index to pointer
#define P_MEM_GET_PTR(index) ((p_mem_descriptor_t*) (global_p_mem_descriptors + ((index) * sizeof(p_mem_descriptor_t))))

struct p_mem_descriptor {
    void* addr;             // Beginning of the place in memory this describes
    size_t pages;           // How many pages are taken up
    uint8_t free;           // If area described is free or not
    uint8_t remove_entry;   // Used for list cleaning
};
typedef struct p_mem_descriptor p_mem_descriptor_t;

/**
 * Initializes physical memory manager
 * 
 * @param[in] mbd Pointer to multiboot information structure
 * @param[in] magic Magic number provided by multiboot, used to tell if memory information is available
 * @param[in] kernel_end_location The memory location indicating the end of the kernel
 * @param[out] code Code indicating success or details of failure
 */
int p_mem_init(multiboot_info_t *mbd, void* kernel_end_location);

/**
 * Allocates the number of page frames requested starting at the given address
 * 
 * Address is rounded to a lower page boundary
 * 
 * @param[in] addr Address of the page to be allocated
 * @param[in] pages How many pages to allocate
 * @param[out] code Code indicating success or details of failure
 */
int palloc(void* addr, uint32_t pages);

/**
 * Frees the number of page frames requested stating at the given address
 * 
 * Address is rounded to a lower page boundary
 * 
 * @param[in] addr Address of the page frame to be freed
 * @param[in] pages How many pages to free
 * @param[out] code Code indicating success or details of failure
 */
int pfree(void* addr, uint32_t pages);

/**
 * Gets the p_mem_descriptor for the specified address
 * 
 * Returns -1 if the address provided is invalid. Output may be a block containing address
 * 
 * @param[in] addr Address descriptor is wanted of
 * @param[out] desc_ptr Pointer to the descriptor
 */
p_mem_descriptor_t *get_descriptor(void* addr);

/**
 * Cleans the memory list, combines entries, etc.
 */
void p_mem_clean_list();

// Globals
extern unsigned int global_p_mem_descriptor_size;
extern size_t global_num_p_mem_descriptors;
extern p_mem_descriptor_t *global_p_mem_descriptors;

#ifdef __cplusplus
}
#endif

#endif
