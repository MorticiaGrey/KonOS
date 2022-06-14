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
 * Value returns non-negative number, x cannot be negative. If x is not a perfect root return value is rounded down because square roots are difficult to do, will be fixed eventually
 * 
 * @param[in] x The value to compute the square root of
 * @param[out] val The square root
 */
double sqrt(double x);

//----------------------------------- (remove later) Implementing this when I need floats

/**
 * Computes the smallest integer value higher than x
 * 
 * @param[in] x Value to be processed
 * @param[out] val Smallest integer value higher than x
 */
//double ceil(double x);

/**
 * Computes the largest integer value not greater than x
 * 
 * @param[in] x Value to be processd
 * @param[out] val Largest integer value not greater than x
 */
//double floor(double x);

/**
 * Rounds to nearest integer
 * 
 * @param[in] x Value to round
 * @param[out] val Rounded value
 */
//double round(double x);

#ifdef __cplusplus
}
#endif

#endif
