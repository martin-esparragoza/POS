/**
 * @file
 *
 * @brief      Useful memory operations
 * 
 * <b>Freestanding file</b>
 */

#pragma once
#include <stddef.h>

/**
 * @brief      Simple memcpy
 *
 * @param[in]  dest  Destination of data
 * @param[in]  src   Data to copy
 * @param[in]  len   Length of data to copy
 *
 * @return     Dest
 */
void * memcpy(void * dest, void * src, size_t len);

/**
 * @brief      Simple memcpy with volatile destination
 *
 * @param[in]  dest  Destination of data (volatile)
 * @param[in]  src   Data to copy
 * @param[in]  len   Length of data to copy
 *
 * @return     Dest
 */
volatile void * memcpy_vd(volatile void * dest, void * src, size_t len);

/**
 * @brief      Simple memcpy with volatile source
 *
 * @param[in]  dest  Destination of data
 * @param[in]  src   Data to copy (volatile)
 * @param[in]  len   Length of data to copy
 *
 * @return     dest
 */
void * memcpy_vs(void * dest, volatile void * src, size_t len);

/**
 * @brief      Simple memcpy with volatile source and destination
 * 
 * `wd_memcpy_vsd` is an acceptable alias
 *
 * @param[in]  dest  Destination of data (volatile)
 * @param[in]  src   Data to copy (volatile)
 * @param[in]  len   Length of data to copy
 *
 * @return     dest (volatile)
 */
volatile void * memcpy_vds(volatile void * dest, volatile void * src, size_t len);
#define memcpy_vsd memcpy_vds

/**
 * @brief      Fill with value
 *
 * @param[in]  dest  Destination pointer
 * @param[in]  val   Value to fill
 * @param[in]  len   Number of elements
 *
 * @return     src
 */
void * memset(void * dest, unsigned char val, size_t len);

/** @} */