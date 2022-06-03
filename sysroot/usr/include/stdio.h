///@file stdio.h

#ifndef _STDIO_H
#define _STDIO_H 1

#include <sys/cdefs.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Prints data to the terminal
 * 
 * @param[in] format String containing the format information for other data and the string printed with it
 * @param[in] ... Data to be printed in the string
 * @param[out] written_characters Number of characters written
 */
int printf(const char* __restrict, ...);

/**
 * Prints single character to terminal
 * 
 * @param[in] ic ASCII code for character to be printed
 * @param[out] ic Input value is returned
 */
int putchar(int);

/**
 * Prints a string to the terminal without any modification
 * 
 * @param[in] string String to be printed
 * @param[out] printf_code Returns output from printf call
 */
int puts(const char*);

#ifdef __cplusplus
}
#endif

#endif
