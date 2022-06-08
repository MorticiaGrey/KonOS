#include <math.h>

double sqrt(double x) {
	if (x < 0) {
		errno = EDOM;
		return 0;
	}

	// This only really wors for perfect roots, otherwise is approximates
	int i = 1;
	while (x > 0) {
		x -= i;
		i += 2;
	}
	return i / 2;
}