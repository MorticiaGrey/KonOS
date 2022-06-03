#include <stddef.h>

struct multiboot_tag {
	size_t type;
	size_t size;
};

typedef struct elf_section_header_table
{
	unsigned long num;
	unsigned long size;
	unsigned long addr;
	unsigned long shndx;
} elf_section_header_table_t;

typedef struct memory_map {
	size_t size;
	size_t base_addr_low;
	size_t base_addr_high;
	size_t length_low;
	size_t length_high;
	size_t type;
} memory_map_t;

typedef struct multiboot_info {
	size_t flags;
	size_t mem_lower;
	size_t mem_upper;
	size_t boot_device;
	size_t cmdline;
	size_t mods_count;
	size_t mods_addr;
	elf_section_header_table_t elf_sec;
	size_t mmap_length;
	size_t mmap_addr;
} multiboot_info_t;