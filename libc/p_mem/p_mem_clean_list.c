#include <p_mem.h>

// remove when function done
#include <stdio.h>

// Attempts to combine the specified entry with the entry under it
void combine_entries(int entry) {
	if (entry > global_num_p_mem_descriptors) {
		return;
	}

	p_mem_descriptor_t *desc = P_MEM_GET_PTR(entry);
	p_mem_descriptor_t *desc_high = P_MEM_GET_PTR(entry + 1);

	//printf("%d == %d, %p/%p\n", desc->free, desc_low->free, desc, desc_low);
	if (desc->free == desc_high->free) {
		desc_high->pages += desc->pages;
		desc_high->addr = desc->addr;
		desc->remove_entry = 1;
	}
}

void copy_entry(int src_i, int dest_i) {
	p_mem_descriptor_t *dest = P_MEM_GET_PTR(dest_i);
	p_mem_descriptor_t *src = P_MEM_GET_PTR(src_i);

	dest->addr = src->addr;
	dest->pages = src->pages;
	dest->free = src->free;
	dest->remove_entry = src->remove_entry;
}

// Everything above index is shifted down amount entries (called down because it's moving everything down in memory)
// Go from top to avoid issues
void shift_down(int index, int amount) {
	unsigned int i;
	unsigned int val = (global_num_p_mem_descriptors) - index + 1;
	for (i = 0; i < val; i++) {
		if ((i + index) - amount < 0 || index + i > global_num_p_mem_descriptors) {
			continue;
		}
		copy_entry((i + index), (i + index) - amount);
	}
}

// I know this is a mess but it's only so bad so it's more efficient (moves entries down as many free spaces as are available)
void compress_list() {
	int i;
	p_mem_descriptor_t *curr_desc;
	// [0] = beginning index, [1] = how many indexes can be removed
	size_t entries_remove[global_num_p_mem_descriptors][2];
	uint16_t remove_num = 0;
	unsigned int acc = 0;
	// Loop through all entries
	for (i = 0; i < global_num_p_mem_descriptors; i++) {
		curr_desc = P_MEM_GET_PTR(i);
		// If this entry should be removed
		if (curr_desc->remove_entry == 1) {
			// While the next entry is to be removed, increment j
			uint8_t con = 1;
			int j = 0;
			while (con) {
				j++;
				con = (P_MEM_GET_PTR(i + j)->remove_entry == 1);
			}

			// Set attributes
			curr_desc->remove_entry = 0;
			entries_remove[remove_num][0] = i;
			entries_remove[remove_num][1] = j;
			remove_num++;
			acc += j;
			i += j - 1;
		}
	}

	for (i = remove_num - 1; i >= 0; i--) {
		shift_down(entries_remove[i][0] + entries_remove[i][1], entries_remove[i][1]);
	}

	global_num_p_mem_descriptors -= acc;
}

void p_mem_clean_list() {
	unsigned int i;
	for (i = 0; i < global_num_p_mem_descriptors - 1; i++) {
		combine_entries(i);
	}
	compress_list();
}