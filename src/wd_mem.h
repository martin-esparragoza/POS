/**
 * @file
 *
 * @brief      Useful memory operations
 * 
 * @addtogroup WD
 * @{
 */

#pragma once

/**
 * @brief      Simple memcpy
 *
 * @param[in]  src     Data to copy
 * @param[in]  dest    Destination of data
 * @param[in]  len  Length of data to copy
 *
 * @return     dest
 */
void * pos_wd_memcpy(void * src, void * dest, unsigned len);

/**
 * @brief      Simple memcpy with volatile destination
 *
 * @param[in]  src     Data to copy
 * @param[in]  dest    Destination of data (volatile)
 * @param[in]  len     Length of data to copy
 *
 * @return     dest
 */
volatile void * pos_wd_memcpy_vd(void * src, volatile void * dest, unsigned len);

/**
 * @brief      Simple memcpy with volatile source
 *
 * @param[in]  src     Data to copy (volatile)
 * @param[in]  dest    Destination of data
 * @param[in]  len     Length of data to copy
 *
 * @return     dest
 */
void * pos_wd_memcpy_vs(volatile void * src, void * dest, unsigned len);

/**
 * @brief      Simple memcpy with volatile source and destination
 * 
 * `pos_wd_memcpy_vsd` is an acceptable alias
 *
 * @param[in]  src     Data to copy (volatile)
 * @param[in]  dest    Destination of data (volatile)
 * @param[in]  len     Length of data to copy
 *
 * @return     dest (volatile)
 */
volatile void * pos_wd_memcpy_vds(volatile void * src, volatile void * dest, unsigned len);
#define pos_wd_memcpy_vsd pos_wd_memcpy_vds

/**
 * @brief      Fill with value
 *
 * @param[in]  src     Source pointer
 * @param[in]  val     Value to fill
 * @param[in]  len     Number of elements
 *
 * @return     src
 */
void * pos_wd_memset(void * src, unsigned char val, unsigned len);

/** @} */