///@file stdflag.h

#ifndef _STDFLAG_H
#define _STDFLAG_H 1

#include <sys/cdefs.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif

#define P_MEM_CHECK_FLAG(flags, bit) ((flags) & (1 << (bit)))
#define SET_FLAG(flags, bit) ((flags) | (1 << bit))

#ifdef __cplusplus
}
#endif

#endif