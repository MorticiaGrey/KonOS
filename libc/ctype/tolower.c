#include <ctype.h>

int tolower(int ch) {
	if (ch >= 65 && ch <= 90) {
		return ch + 32;
	} else {
		return ch;
	}
}