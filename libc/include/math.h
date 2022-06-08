///@file math.h

#ifndef _MATH_H
#define _MATH_H 1

#include <sys/cdefs.h>

#include <errno.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Returns 2^x
 * 
 * Range error occurs if x is too large
 * 
 * @param[in] x Power of two to find
 * @param[out] val Value reached
 */
double exp2(double x);

/**
 * Returns the absolute value of x
 * 
 * @param[in] x Value to compute absolute value from
 * @param[out] val Absolute value
 */
double fabs(double x);

/**
 * Returns the value of x^y
 * 
 * @param[in] x Base
 * @param[in] y Power
 * @param[out] val Value computed
 */
double pow(double x, double y);

/**
 * Returns the square root of x
 * 
 * Value returns non-negative number, x cannot be negative
 * 
 * @param[in] x The value to compute the square root of
 * @param[out] val The square root
 */
double sqrt(double x);

#ifdef __cplusplus
}
#endif

#endif
