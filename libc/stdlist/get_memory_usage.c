#include <stdlist.h>

extern std_list_t curr_list;

uint32_t get_memory_usage() {
	return curr_list.entry_size * curr_list.length;
}