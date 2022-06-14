#include <errno.h>

char *strerror(int error) {
	switch (error) {
		case 0: return "No error";
		case 1: return "Invalid numeric domain";
		case 2: return "Illegal byte sequence";
		case 3: return "Argument out of range";
		case 4: return "Illegal address";
		default: return "Invalid error code";
	}
}