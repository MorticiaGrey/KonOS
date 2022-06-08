///@file io.h

#ifndef _IO_H
#define _IO_H 1

#include <sys/cdefs.h>
#include <stdint.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Sends the specified value on the IO bus to the specified port
 * 
 * @param[in] port The port to send data on
 * @param[in] value The value that's sent
 */
void outb(uint16_t, uint8_t);
/**
 * Receives data from IO on specified port
 * 
 * @param[in] port Port to receive data from
 * @param[out] value Value received
 */
uint8_t inb(uint16_t);

#ifdef __cplusplus
}
#endif

#endif
