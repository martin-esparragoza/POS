/**
 * @file
 *
 * @brief      Standard io (like printf) for us
 * 
 * Buffered support is for CHUMPS! This is for debugging anyway. It should be primitive.
 * 
 * @addtogroup WD
 * ${
 * 
 * @defgroup   STDIO
 * Standard IO
 * @{
 */

#pragma once

void wd_printf(const char * format, void (* write_char)(char data), ...);

/**
 * @}
 * @]
 */
