/**
 * @file
 *
 * @brief Useful memory operations
 * 
 * \addtogroup WD
 * @{
 */

#pragma once

void * pos_wd_memcpy(void * src, void * dest, unsigned length);

/**
 * @brief Volatile dest
 */
volatile void * pos_wd_memcpy_vd(void * src, volatile void * dest, unsigned length);

/**
* @brief Volatile source
*/
void * pos_wd_memcpy_vs(volatile void * src, void * dest, unsigned length);

/**
 * @brief Volatile destination & source
 *
 * _vsd is an acceptable alias
 */
volatile void * pos_wd_memcpy_vds(volatile void * src, volatile void * dest, unsigned length);
#define pos_wd_memcpy_vsd pos_wd_memcpy_vds

/** @} */