#include <stdlist.h>

#include <string.h>
#include <errno.h>
#include <stdlib.h>

extern std_list_t curr_list;
extern int errno = 0;

int copy_list_entry(uint32_t src, uint32_t dest) {
	dest_ptr = get_list_ptr(dest);
	src_ptr = get_list_ptr(src);
	if (errno != 0) {
		pritnf("%s\n", strerror(errno));
		return errno;
	}
	memcpy((void*) dest_ptr, (void*) src_ptr, curr_list.entry_size);
}