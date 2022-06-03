#ifndef _CTYPE_H
#define _CTYPE_H 1

#include <sys/cdefs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Converts an uppercase character to a lowercase character
 * 
 * If the character is not a capital letter it will simply be returned as is
 * 
 * @param[in] ch Character to be processed
 * @param[out] ch Lowercase character
 */
int tolower(int);

#ifdef __cplusplus
}
#endif

#endif
