#include <math.h>

int errno = 0;

double pow(double x, double y) {
	if (x + y == 0) {
		errno = EDOM;
		return 0;
	}
	int i, result = 1;
	for (i = 0; i < y; i++) {
		result *= x;
	}
	return result;
}