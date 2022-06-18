#include <stdlist.h>

#include <errno.h>

std_list_t curr_list;
int errno = 0;

void* get_list_ptr(uint32_t index) {
	if (index <= curr_list.length) {
		return (curr_list.addr + ((index) * curr_list.entry_size));
	}
	errno = ERANGE;
	return -1;
}