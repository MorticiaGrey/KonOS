#include <math.h>

double pow(double x, double y) {
	if (x + y == 0) {
		errno = EDOM;
		return 0;
	}
	int i;
	for (i = 0; i < y; i++) {
		x = x * x;
	}
	return x;
}