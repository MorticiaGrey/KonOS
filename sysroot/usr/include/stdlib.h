#ifndef _STDLIB_H
#define _STDLIB_H 1

#include <sys/cdefs.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_ITOA_DIGITS 64 /// Maximum number of digits itoa is able to convert into a string

__attribute__((__noreturn__))
void abort(void);
/**
 * Converts a value from an integer to a string with the base provided
 * 
 * The base is set to 10 by default, the default value will be used in case an invalid base is passed. Can only print 64 digits at a time.
 * 
 * @param[in] value The value to be converted
 * @param[in] str The string buffer for the value to be written to
 * @param[in] base Base of the number the string is output as (i.e. binary, decimal, hex, etc.)
 * @param[out] str Pointer to the buffer. Doesn't need to be used as the buffer is already modified.
 */
char *itoa(int, char*, int);

#ifdef __cplusplus
}
#endif

#endif
