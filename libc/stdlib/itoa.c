#include <stdlib.h>

#include <string.h>
#include <stdio.h>

// Used to convert digits
static const char *digits = "0123456789ABCDEF\0";

// TODO: THIS NEEDS TO BE IN MATH.H!!! MOVE IT WHEN MATH.H EXISTS!!!
int get_exponent(int base, int exp) {
	int i, result = 1;
    for (i = 0; i < exp; i++)
        result *= base;
    return result;
}

// Convert decimal character, only works on single digits
static char get_character(int val, int base) {
	if (val < 0 || val > base - 1) {
		return 'e';
	}
	char character = digits[val];
	return character;
}

char *itoa(int value, char *buffer, int base) {
	// Length of digits list
	int len = 1;

	int neg = 0;
	if (value < 0) {
		value = value * -1;
		neg = 1;
		buffer[0] = '-';
	}

	// Get length/populate digits list (digits are entered in reverse order)
	int remainder = value;
	int digits[MAX_ITOA_DIGITS + 1]; // Plus one makes room for null terminating character
	while (remainder > base - 1) {
		digits[len] = remainder % base;
		remainder = remainder / base;
		len++;
	}
	digits[len] = value / get_exponent(base, len - 1); // Get and add first digit

	// Insert digits into buffer, separate loop because it's reversed
	int i;
	for (i = len; i > 0; i--) {
		buffer[len - i + neg] = get_character(digits[i], base);
	}

	buffer[len + neg] = '\0';

	return buffer;
}