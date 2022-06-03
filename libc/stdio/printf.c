#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Print a string of specified length
static bool print(const char* data, size_t length) {
	const unsigned char* bytes = (const unsigned char*) data;
	for (size_t i = 0; i < length; i++)
		if (putchar(bytes[i]) == EOF)
			return false;
	return true;
}

// TODO: Hex field, other data insertion if I feel like it
// This is commented in such psychotic detail so I can modify it effectively since I didn't originally write it (thanks osdev.net)
int printf(const char* restrict format, ...) {
	// Defines data that will be added to format
	va_list parameters;
	va_start(parameters, format);

	// Number of written characters
	int written = 0;

	// Loop processing the format and data additions
	while (*format != '\0') {
		// Amount of available memory
		size_t maxrem = INT_MAX - written;

		// If current character is not % or next character is %
		if (format[0] != '%' || format[1] == '%') {
			// If current character is % skip to next character
			if (format[0] == '%')
				format++;
			// Amount of offset from current format character
			size_t amount = 1;
			// Skip past invalid characters (null characters or %)
			while (format[amount] && format[amount] != '%')
				amount++;
			// If offset exceeds max memory, return an error
			if (maxrem < amount) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			// Print string of length amount, if it returns an error this function also returns an error
			if (!print(format, amount))
				return -1;
			// Format is updated with the amount written in this cycle
			format += amount;
			// Written is updated
			written += amount;
			// Process next character(s)
			continue;
		}

		// Increments format (character being processed) while saving original value
		const char* format_begun_at = format++;

		// If current character is c process a character
		if (*format == 'c') {
			// Go to next character
			format++;
			// Get character from arguments passed to function
			char c = (char) va_arg(parameters, int /* char promotes to int */);
			// If the buffer is full, return error
			if (!maxrem) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			// Print character from arguments
			if (!print(&c, sizeof(c)))
				return -1;
			// Update written
			written++;
		} else if (*format == 's') { // If character is s process a string
			format++;
			// Get string value
			const char* str = va_arg(parameters, const char*);
			// Get length of string
			size_t len = strlen(str);
			// Return error if there's not enough memory
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			// Print string
			if (!print(str, len))
				return -1;
			// Update written
			written += len;
		} else if (*format == 'd' || *format == 'i') { // Print signed decimal integer
			format++;
			char str[MAX_ITOA_DIGITS + 1];
			itoa(((int) va_arg(parameters, int)), str, 10);
			size_t len = strlen(str);
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW
				return -1;
			}
			if (!print(str, len))
				return -1;
			written += len;
		} else if (*format == 'x' || *format == 'X') { // Unsigned hex integer, lower
			format++;
			char str[MAX_ITOA_DIGITS + 1];
			int param = (int) va_arg(parameters, int);
			if (param < 0) {
				param = param * -1;
			}
			itoa(param, str, 16);
			size_t len = strlen(str);
			if (*(format - 1) == 'x') {
				for (int i = 0; i < len; i++) { // itoa defaults to uppercase, convert to lowercase
					str[i] = tolower(str[i]);
				}	
			}
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW
				return -1;
			}
			if (!print(str, len))
				return -1;
			written += len;
		} else if (*format == 'p') {
			format++;
			char str[MAX_ITOA_DIGITS + 1];
			int param = (int) va_arg(parameters, void*);
			itoa(param, str, 16);
			size_t len = strlen(str);
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW
				return -1;
			}
			if (!print("0x", 2) || !print(str, len))
				return -1;
			written += len;
		} else { // Default option, print the rest of the format string without adding data
			// Go back to original place
			format = format_begun_at;
			size_t len = strlen(format);
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(format, len))
				return -1;
			written += len;
			format += len;
		}
	}

	// Stop using parameters
	va_end(parameters);
	// Return the number of written characters
	return written;
}
