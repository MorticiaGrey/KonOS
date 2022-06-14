#include <stdlist.h>

extern std_list_t curr_list;
extern int errno = 0;

void* append_list_entry() {
	return add_list_entry(curr_list.length);
}