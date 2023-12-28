/**
 * @file
 *
 * @brief      Clock cycle related functions
 *
 * Used for easy delays for now <br>
 * <b>Freestanding file</b>
 *
 * @addtogroup WD
 * @{
 */

#include <stdint.h>

/**
 * @brief      Run that many clock cycles (branch instructions) before returning
 * 
 * This is NOT my code! I have stolen it.
 *
 * @param[in]  count  # of clock cycles to execute
 */
void delay_cycles(unsigned long count);

/** @} */