/**
 * @file
 *
 * @brief Time or clock cycle related functions
 *
 * Used for easy delays for now
 *
 * \addtogroup WD
 * @{
 */

#include <stdint.h>

/**
 * @brief Run that many clock cycles before returning
 * 
 * @param count # of clock cycles to execute
 */
void pos_wd_delay(uint32_t count);

/** @} */