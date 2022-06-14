///@file stdlist.h

/*
    This is a nonstandard c library component, this will not be implemented into libc. This is a utility header because
    the list data structure is very common is OS development and standardizing seems worth the possible hit to portability.
*/

#ifndef _STDLIST_H
#define _STDLIST_H 1

#include <sys/cdefs.h>

#include <stdint.h>
#include <errno.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif

struct std_list {
    void* addr;
    uint32_t length;
    uint32_t entry_size;
    uint32_t max_number_entries;
}
typedef struct std_list std_list_t;

/**
 * Set this variable before calling list functions, global used so I don't have to pass the list to every function call
 */
extern std_list_t curr_list;

/**
 * Gets the pointer to an entry from the index
 * 
 * Checks if index is outside of bounds so other functions don't have to
 * 
 * @param[in] index Index of the entry to get the pointer from
 * @param[out] ptr Pointer to the entry
 */
void* get_list_ptr(uint32_t index);

/**
 * Gets the amount of memory used by the list
 * 
 * @param[out] mem Amount of memory being used
 */
uint32_t get_memory_usage();

/**
 * Copies a list entry from one index to another
 * 
 * @param[in] src Source entry, will be copied to dest
 * @param[in] dest Destination entry, will be copied to
 * @param[out] err Error code, 0 indicates success
 */
int copy_list_entry(uint32_t src, uint32_t dest);

/**
 * Removes an entry from the list
 * 
 * List is compacted after removal, more efficient custom algorithms are suggested for large lists (see p_mem.h)
 * 
 * @param[in] index Index of the entry to be removed
 * @param[out] err Error code, 0 indicates success
 */
int rm_list_entry(uint32_t index);

/**
 * Add an entry to the list at the specified index
 * 
 * Pass curr_list.length to append to end of list. Checks if the new entry will exceed maximum memory
 * 
 * @param[in] index Index the new entry is to be placed at
 * @param[out] ptr Pointer to the new entry
 */
void* add_list_entry(uint32_t index);

/**
 * Appends a list entry to the end of the list
 * 
 * Convenience function, uses add_list_entry(curr_list.length)
 * 
 * @param[out] ptr Pointer to the new entry
 */
void* append_list_entry();

#ifdef __cplusplus
}
#endif

#endif
