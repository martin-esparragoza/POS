/**
 * @file
 * 
 * @brief      SD handle
 * 
 * @addtogroup WD
 * @{
 * 
 * @addtogroup DEV
 * @{
 * 
 * @defgroup   EMMC
 * Extended multimedia controller driver
 * @{
 * 
 * This driver has been implemented through someone elses code as documentation (BECAUSE SOME PEOPLE CAN'T RELEASE GIVEN DOCUMENTATION) <br>
 * Thank you Zoltan Baldaszti :) <br>
 * Otherwise written through the only given docs (SoC documentation that gives its minimal EMMC stuffs)
 * @see        <a href = "https://github.com/bztsrc/raspi3-tutorial/blob/master/0B_readsector/sd.c">Reference used</a>
 */

#pragma once
#include <stdint.h>

#define WD_DEV_EMMC_BASE           0x00300000
#define WD_DEV_EMMC_ARG2           (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0x00)))
#define WD_DEV_EMMC_BLKSIZECNT     (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0x00)))
#define WD_DEV_EMMC_ARG1           (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0x08)))
#define WD_DEV_EMMC_CMDTM          (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0x0C)))
#define WD_DEV_EMMC_RESP0          (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0x10)))
#define WD_DEV_EMMC_RESP1          (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0x14)))
#define WD_DEV_EMMC_RESP2          (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0x18)))
#define WD_DEV_EMMC_RESP3          (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0x1C)))
#define WD_DEV_EMMC_DATA           (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0x20)))
#define WD_DEV_EMMC_STATUS         (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0x24)))
#define WD_DEV_EMMC_CONTROL0       (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0x28)))
#define WD_DEV_EMMC_CONTROL1       (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0x2C)))
#define WD_DEV_EMMC_INTERRUPT      (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0x30)))
#define WD_DEV_EMMC_IRPT_MASK      (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0x34)))
#define WD_DEV_EMMC_IRPT_EN        (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0x38)))
#define WD_DEV_EMMC_CONTROL2       (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0x3C)))
#define WD_DEV_EMMC_FORCE_IRPT     (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0x50)))
#define WD_DEV_EMMC_BOOT_TIMEOUT   (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0x70)))
#define WD_DEV_EMMC_DBG_SEL        (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0x74)))
#define WD_DEV_EMMC_EXRDFIFO_CFG   (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0x80)))
#define WD_DEV_EMMC_EXRDFIFO_EN    (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0x84)))
#define WD_DEV_EMMC_TUNE_STEP      (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0x88)))
#define WD_DEV_EMMC_TUNE_STEPS_STD (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0x8C)))
#define WD_DEV_EMMC_TUNE_STEPS_DDR (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0x90)))
#define WD_DEV_EMMC_SPI_INT_SPT    (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0xF0)))
#define WD_DEV_EMMC_SLOTISR_VER    (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0xFC)))

enum wd_dev_emmc_errc {
    WD_DEV_EMMC_ERRC_NONE,
    WD_DEV_EMMC_ERRC_FAIL_NO_CLOCK,
    WD_DEV_EMMC_ERRC_FAIL_SET_CLOCK
};

/**
 * @brief      Turn error code into string
 * 
 * No checks are done. Correct error codes should be always returned.
 *
 * @param[in]  errc  Error code returned from func
 *
 * @return     Pointer to error string (STATIC)
 */
const char * wd_dev_emmc_errctostr(enum wd_dev_emmc_errc errc);

/**
 * @brief      Inits the EMMC
 *
 * @return     Error code
 */
enum wd_dev_emmc_errc wd_dev_emmc_init();