#include <stdlist.h>

std_list_t curr_list;
int errno = 0;

void* add_list_entry(uint32_t index) {
	if (index > curr_list.length || index > curr_list.max_number_entries) {
		errno = ERANGE;
		return (void*) 0;
	}

	unsigned int i;
	for (i = index + 1; i < curr_list.length; i++) {
		copy_list_entry(i, i + 1);
	}

	curr_list.length++;

	return get_list_ptr(index);
}