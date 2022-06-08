///@file errno.h

#ifndef _P_ERRNO_H
#define _P_ERRNO_H 1

#include <sys/cdefs.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif

extern int errno;

// Constants
#define EDOM   1 // Invalid numeric domain, bad argument in a math function
#define EILSEQ 2 // Illegal byte sequence, not sure exactly when this is used
#define ERANGE 3 // Argument out of range, an argument to a math function is too large/when args generally are too large

/**
 * Gets the human readable string which corresponds to a given error code
 * 
 * @param[in] error Integer representing the error
 * @param[out] error_str The string describing the error
 */
char *strerror(int error);

#ifdef __cplusplus
}
#endif

#endif
