/**
 * @file
 *
 * @brief      Standard io (like printf) for us
 * 
 * Buffered support is for CHUMPS! This is for debugging anyway. It should be primitive.
 * 
 * @addtogroup WD
 * @{
 * 
 * @defgroup   STDIO
 * Standard IO
 * @{
 */

#pragma once
#include <stdbool.h>

/**
 * @brief      Fprintf
 * 
 * Supports:
 *  %d - Signed uintmax_t
 *  %b - Binary uintmax_t
 *  %x - Hex uintmax_t
 *  %s - String
 *
 * @param[in]  write_char  Character print function
 * @param[in]  format      Fstring
 * @param[in]  vargs       Data format
 */
void wd_fprintf(void (* const write_char)(char), const char * format, ...);

/**
 * @}
 * @}
 */
