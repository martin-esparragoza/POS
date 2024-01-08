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
#include "wd_dev.h"
#include <stdint.h>

#define WD_DEV_EMMC_BASE                      WD_DEV_BASE + 0x00300000

#define WD_DEV_EMMC_ARG2                      (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0x00)))

#define WD_DEV_EMMC_BLKSIZECNT                (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0x00)))
#define WD_DEV_EMMC_BLKSIZECNT_BLKCNT         0xFFFF0000
#define WD_DEV_EMMC_BLKSIZECNT_BLKCNT_S       16
#define WD_DEV_EMMC_BLKSIZECNT_BLKSIZE        0x000003FF
#define WD_DEV_EMMC_BLKSIZECNT_BLKSIZE_S      0
#define WD_DEV_EMMC_BLKSIZECNT_MSK            0xFFFF03FF

#define WD_DEV_EMMC_ARG1                      (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0x08)))

#define WD_DEV_EMMC_CMDTM                     (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0x0C)))
#define WD_DEV_EMMC_CMDTM_CMD_INDEX           0x3F000000
#define WD_DEV_EMMC_CMDTM_CMD_INDEX_S         24
#define WD_DEV_EMMC_CMDTM_CMD_TYPE            0x00C00000
#define WD_DEV_EMMC_CMDTM_CMD_TYPE_S          22
#define WD_DEV_EMMC_CMDTM_CMD_ISDATA          0x00200000
#define WD_DEV_EMMC_CMDTM_CMD_ISDATA_S        21
#define WD_DEV_EMMC_CMDTM_CMD_IXCHK_EN        0x00100000
#define WD_DEV_EMMC_CMDTM_CMD_IXCHK_EN_S      20
#define WD_DEV_EMMC_CMDTM_CMD_CRCCHK_EN       0x00080000
#define WD_DEV_EMMC_CMDTM_CMD_CRCCHK_EN_S     19
#define WD_DEV_EMMC_CMDTM_CMD_RSPNS_TYPE      0x00030000
#define WD_DEV_EMMC_CMDTM_CMD_RSPNS_TYPE_S    16
#define WD_DEV_EMMC_CMDTM_TM_MULTI_BLOCK      0x00000020
#define WD_DEV_EMMC_CMDTM_TM_MULTI_BLOCK_S    5
#define WD_DEV_EMMC_CMDTM_TM_DATA_DIR         0x00000010
#define WD_DEV_EMMC_CMDTM_TM_DATA_DIR_S       4
#define WD_DEV_EMMC_CMDTM_TM_AUTO_CMD_EN      0x0000000C
#define WD_DEV_EMMC_CMDTM_TM_AUTO_CMD_EN_S    2
#define WD_DEV_EMMC_CMDTM_TM_BLKCNT_EN        0x00000002
#define WD_DEV_EMMC_CMDTM_TM_BLKCNT_EN_S      1
#define WD_DEV_EMMC_CMDTM_MSK                 0x3FBF003E

#define WD_DEV_EMMC_RESP0                     (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0x10)))
#define WD_DEV_EMMC_RESP1                     (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0x14)))
#define WD_DEV_EMMC_RESP2                     (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0x18)))
#define WD_DEV_EMMC_RESP3                     (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0x1C)))

#define WD_DEV_EMMC_DATA                      (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0x20)))

#define WD_DEV_EMMC_STATUS                    (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0x24)))
#define WD_DEV_EMMC_STATUS_DAT_LEVEL1         0x1E000000
#define WD_DEV_EMMC_STATUS_DAT_LEVEL1_S       25
#define WD_DEV_EMMC_STATUS_CMD_LEVEL          0x01000000
#define WD_DEV_EMMC_STATUS_CMD_LEVEL_S        24
#define WD_DEV_EMMC_STATUS_DAT_LEVEL0         0x00F00000
#define WD_DEV_EMMC_STATUS_DAT_LEVEL0_S       20
#define WD_DEV_EMMC_STATUS_READ_TRANSFER      0x00000200
#define WD_DEV_EMMC_STATUS_READ_TRANSFER_S    9
#define WD_DEV_EMMC_STATUS_WRITE_TRANSFER     0x00000100
#define WD_DEV_EMMC_STATUS_WRITE_TRANSFER_S   8
#define WD_DEV_EMMC_STATUS_DAT_ACTIVE         0x00000004
#define WD_DEV_EMMC_STATUS_DAT_ACTIVE_S       2
#define WD_DEV_EMMC_STATUS_DAT_INHIBIT        0x00000002
#define WD_DEV_EMMC_STATUS_DAT_INHIBIT_S      1
#define WD_DEV_EMMC_STATUS_CMD_INHIBIT        0x00000001
#define WD_DEV_EMMC_STATUS_CMD_INHIBIT_S      0
#define WD_DEV_EMMC_STATUS_MSK                0x1FF00307

#define WD_DEV_EMMC_CONTROL0                  (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0x28)))
#define WD_DEV_EMMC_CONTROL0_ALT_BOOT_EN      0x00400000
#define WD_DEV_EMMC_CONTROL0_ALT_BOOT_EN_S    22
#define WD_DEV_EMMC_CONTROL0_BOOT_EN          0x00200000
#define WD_DEV_EMMC_CONTROL0_BOOT_EN_S        21
#define WD_DEV_EMMC_CONTROL0_SPI_MODE         0x00100000
#define WD_DEV_EMMC_CONTROL0_SPI_MODE_S       20
#define WD_DEV_EMMC_CONTROL0_GAP_IEN          0x00080000
#define WD_DEV_EMMC_CONTROL0_GAP_IEN_S        19
#define WD_DEV_EMMC_CONTROL0_READWAIT_EN      0x00040000
#define WD_DEV_EMMC_CONTROL0_READWAIT_EN_S    18
#define WD_DEV_EMMC_CONTROL0_GAP_RESTART      0x00020000
#define WD_DEV_EMMC_CONTROL0_GAP_RESTART_S    17
#define WD_DEV_EMMC_CONTROL0_GAP_STOP         0x00010000
#define WD_DEV_EMMC_CONTROL0_GAP_STOP_S       16
#define WD_DEV_EMMC_CONTROL0_HCTL_BIT         0x00000020
#define WD_DEV_EMMC_CONTROL0_HCTL_BIT_S       5
#define WD_DEV_EMMC_CONTROL0_HCTL_HS_EN       0x00000004
#define WD_DEV_EMMC_CONTROL0_HCTL_HS_EN_S     2
#define WD_DEV_EMMC_CONTROL0_HCTL_DWIDTH      0x00000002
#define WD_DEV_EMMC_CONTROL0_HCTL_DWIDTH_S    1
#define WD_DEV_EMMC_CONTROL0_MSK              0x007F0026

#define WD_DEV_EMMC_CONTROL1                  (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0x2C)))
#define WD_DEV_EMMC_CONTROL1_SRST_DATA        0x04000000
#define WD_DEV_EMMC_CONTROL1_SRST_DATA_S      26
#define WD_DEV_EMMC_CONTROL1_SRST_CMD         0x02000000
#define WD_DEV_EMMC_CONTROL1_SRST_CMD_S       25
#define WD_DEV_EMMC_CONTROL1_SRST_HC          0x01000000
#define WD_DEV_EMMC_CONTROL1_SRST_HC_S        24
#define WD_DEV_EMMC_CONTROL1_DATA_TOUINT      0x000F0000
#define WD_DEV_EMMC_CONTROL1_DATA_TOUINT_S    16
#define WD_DEV_EMMC_CONTROL1_CLK_FREQ8        0x0000FF00
#define WD_DEV_EMMC_CONTROL1_CLK_FREQ8_S      8
#define WD_DEV_EMMC_CONTROL1_CLK_FREQ_MS2     0x000000C0
#define WD_DEV_EMMC_CONTROL1_CLK_FREQ_MS2_S   6
#define WD_DEV_EMMC_CONTROL1_CLK_GENSEL       0x00000020
#define WD_DEV_EMMC_CONTROL1_CLK_GENSEL_S     5
#define WD_DEV_EMMC_CONTROL1_CLK_EN           0x00000004
#define WD_DEV_EMMC_CONTROL1_CLK_EN_S         2
#define WD_DEV_EMMC_CONTROL1_CLK_STABLE       0x00000002
#define WD_DEV_EMMC_CONTROL1_CLK_STABLE_S     1
#define WD_DEV_EMMC_CONTROL1_CLK_INTLEN       0x00000001
#define WD_DEV_EMMC_CONTROL1_CLK_INTLEN_S     0
#define WD_DEV_EMMC_CONTROL1_MSK              0x070FFFE7

#define WD_DEV_EMMC_INTERRUPT      (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0x30)))
#define WD_DEV_EMMC_INTERRUPT_ACMD_ERR        0x01000000
#define WD_DEV_EMMC_INTERRUPT_ACMD_ERR_S      24
#define WD_DEV_EMMC_INTERRUPT_DEND_ERR        0x00400000
#define WD_DEV_EMMC_INTERRUPT_DEND_ERR_S      22
#define WD_DEV_EMMC_INTERRUPT_DCRC_ERR        0x00200000
#define WD_DEV_EMMC_INTERRUPT_DCRC_ERR_S      21
#define WD_DEV_EMMC_INTERRUPT_DTO_ERR         0x00100000
#define WD_DEV_EMMC_INTERRUPT_DTO_ERR_S_S     20
#define WD_DEV_EMMC_INTERRUPT_CBAD_ERR        0x00080000
#define WD_DEV_EMMC_INTERRUPT_CBAD_ERR_S      19
#define WD_DEV_EMMC_INTERRUPT_CEND_ERR        0x00040000
#define WD_DEV_EMMC_INTERRUPT_CEND_ERR_S      18
#define WD_DEV_EMMC_INTERRUPT_CCRC_ERR        0x00020000
#define WD_DEV_EMMC_INTERRUPT_CCRC_ERR_S      17
#define WD_DEV_EMMC_INTERRUPT_CTO_ER          0x00010000
#define WD_DEV_EMMC_INTERRUPT_CTO_ER_S        16
#define WD_DEV_EMMC_INTERRUPT_ERR             0x00008000
#define WD_DEV_EMMC_INTERRUPT_ERR_S           15
#define WD_DEV_EMMC_INTERRUPT_ENDBOOT         0x00004000
#define WD_DEV_EMMC_INTERRUPT_ENDBOOT_S       14
#define WD_DEV_EMMC_INTERRUPT_BOOTACK         0x00002000
#define WD_DEV_EMMC_INTERRUPT_BOOTACK_S       13
#define WD_DEV_EMMC_INTERRUPT_RETUNE          0x00001000
#define WD_DEV_EMMC_INTERRUPT_RETUNE_S        12 
#define WD_DEV_EMMC_INTERRUPT_CARD            0x00000100
#define WD_DEV_EMMC_INTERRUPT_CARD_S          8
#define WD_DEV_EMMC_INTERRUPT_READ_RDY        0x00000020
#define WD_DEV_EMMC_INTERRUPT_READ_RDY_S      5
#define WD_DEV_EMMC_INTERRUPT_WRITE_RDY       0x00000010
#define WD_DEV_EMMC_INTERRUPT_WRITE_RDY_S     4
#define WD_DEV_EMMC_INTERRUPT_BLOCK_GAP       0x00000004
#define WD_DEV_EMMC_INTERRUPT_BLOCK_GAP_S     3
#define WD_DEV_EMMC_INTERRUPT_DATA_DONE       0x00000002
#define WD_DEV_EMMC_INTERRUPT_DATA_DONE_S     1
#define WD_DEV_EMMC_INTERRUPT_CMD_DONE        0x00000001
#define WD_DEV_EMMC_INTERRUPT_CMD_DONE_S      0
#define WD_DEV_EMMC_INTERRUPT_MSK             0x017FF137

#define WD_DEV_EMMC_IRPT_MASK                 (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0x34)))
// Copy from interrupt

#define WD_DEV_EMMC_IRPT_EN                   (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0x38)))
// Copy from interrupt

#define WD_DEV_EMMC_CONTROL2                  (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0x3C)))
#define WD_DEV_EMMC_CONTROL2_TUNED            0x00800000
#define WD_DEV_EMMC_CONTROL2_TUNED_S          23
#define WD_DEV_EMMC_CONTROL2_TUNEON           0x00400000
#define WD_DEV_EMMC_CONTROL2_TUNEON_S         22
#define WD_DEV_EMMC_CONTROL2_UHSMODE          0x00070000
#define WD_DEV_EMMC_CONTROL2_UHSMODE_S        16
#define WD_DEV_EMMC_CONTROL2_NOTC12_ERR       0x00000080
#define WD_DEV_EMMC_CONTROL2_NOTC12_ERR_S     7
#define WD_DEV_EMMC_CONTROL2_ACBAD_ERR        0x00000010
#define WD_DEV_EMMC_CONTROL2_ACBAD_ERR_S      4
#define WD_DEV_EMMC_CONTROL2_ACEND_ERR        0x00000008
#define WD_DEV_EMMC_CONTROL2_ACEND_ERR_S      3
#define WD_DEV_EMMC_CONTROL2_ACCRC_ERR        0x00000004
#define WD_DEV_EMMC_CONTROL2_ACCRC_ERR_S      2
#define WD_DEV_EMMC_CONTROL2_ACTO_ERR         0x00000002
#define WD_DEV_EMMC_CONTROL2_ACTO_ERR_S       1
#define WD_DEV_EMMC_CONTROL2_ACNOX_ERR        0x00000001
#define WD_DEV_EMMC_CONTROL2_ACNOX_ERR_S      0
#define WD_DEV_EMMC_CONTROL2_MSK              0x00C7009F

#define WD_DEV_EMMC_FORCE_IRPT                (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0x50)))
// Copy from interrupt

#define WD_DEV_EMMC_BOOT_TIMEOUT              (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0x70)))

#define WD_DEV_EMMC_DBG_SEL                   (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0x74)))
#define WD_DEV_EMMC_DBG_SEL_SELECT            0x00000001
#define WD_DEV_EMMC_DBG_SEL_SELECT_S          0
#define WD_DEV_EMMC_DBG_SEL_MSK               0x00000001

#define WD_DEV_EMMC_EXRDFIFO_CFG              (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0x80)))
#define WD_DEV_EMMC_EXRDFIFO_CFG_RD_THRESH    0x00000006
#define WD_DEV_EMMC_EXRDFIFO_CFG_RD_THRESH_S  0
#define WD_DEV_EMMC_EXRDFIFO_CFG_MSK          0x00000006

#define WD_DEV_EMMC_EXRDFIFO_EN               (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0x84)))
#define WD_DEV_EMMC_EXRDFIFO_EN_ENABLE        0x00000001
#define WD_DEV_EMMC_EXRDFIFO_EN_S             0
#define WD_DEV_EMMC_EXRDFIFO_EN_MSK           0x00000001

#define WD_DEV_EMMC_TUNE_STEP                 (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0x88)))
#define WD_DEV_EMMC_TUNE_STEP_DELAY           0x00000007
#define WD_DEV_EMMC_TUNE_STEP_DELAY_S         0
#define WD_DEV_EMMC_TUNE_STEP_MSK             0x00000007

#define WD_DEV_EMMC_TUNE_STEPS_STD            (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0x8C)))
#define WD_DEV_EMMC_TUNE_STEPS_STD_STEPS      0x0000001F
#define WD_DEV_EMMC_TUNE_STEPS_STD_STEPS_S    0
#define WD_DEV_EMMC_TUNE_STEPS_STD_MSK        0x0000001F

#define WD_DEV_EMMC_TUNE_STEPS_DDR            (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0x90)))
#define WD_DEV_EMMC_TUNE_STEPS_DDR_STEPS      0x0000001F
#define WD_DEV_EMMC_TUNE_STEPS_DDR_STEPS_S    0
#define WD_DEV_EMMC_TUNE_STEPS_DDR_MSK        0x0000001F


#define WD_DEV_EMMC_SPI_INT_SPT               (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0xF0)))
#define WD_DEV_EMMC_SPI_INT_SPT_SELECT        0x000000FF
#define WD_DEV_EMMC_SPI_INT_SPT_SELECT_S      0
#define WD_DEV_EMMC_SPI_INT_SPT_MSK           0x000000FF

#define WD_DEV_EMMC_SLOTISR_VER               (*((volatile uint32_t *) (WD_DEV_EMMC_BASE + 0xFC)))
#define WD_DEV_EMMC_SLOTISR_VER_VENDOR        0xFF000000
#define WD_DEV_EMMC_SLOTISR_VER_VENDOR_S      24
#define WD_DEV_EMMC_SLOTISR_VER_SDVERSION     0x00FF0000
#define WD_DEV_EMMC_SLOTISR_VER_SDVERSION_S   16
#define WD_DEV_EMMC_SLOTISR_VER_SLOT_STATUS   0x000000FF
#define WD_DEV_EMMC_SLOTISR_VER_SLOT_STATUS_S 0
#define WD_DEV_EMMC_SLOTISR_VER_MSK           0xFFFF00FF

#define WD_DEV_EMMC_ERRC_ISCRITICAL(errc) (errc & 1)

// LSB dictates criticality
enum wd_dev_emmc_errc {
    WD_DEV_EMMC_ERRC_FAIL_NO_CLOCK =   1 << 1 | 1,
    WD_DEV_EMMC_ERRC_FAIL_SET_CLOCK =  1 << 2 | 1,
    WD_DEV_EMMC_ERRC_FAIL_MBOX =       1 << 3 | 1,
    WD_DEV_EMMC_ERRC_FAIL_RESTART =    1 << 4 | 1,
    WD_DEV_EMMC_ERRC_TIMEOUT_INHIBIT = 1 << 5 | 0,
    WD_DEV_EMMC_ERRC_CLOCK_UNSTABLE =  1 << 6 | 0
};

enum wd_dev_emmc_errc wd_dev_emmc_setclock(unsigned freq);

/**
 * @brief      Gets next flag in errc
 *
 * Gets the next flag in the error code and modifies it to not have that flag. <br>
 * Returns NULL errc is 0 or 1 (just critical bit is left) <br>
 * Call this in a loop to get all errors <br>
 * An error code of 0 eans there are no errors <br>
 * 
 * @param[in]  errc  Error code returned from func
 *
 * @return     Pointer to error string (STATIC) NULL if errc is 0 or 1
 */
const char * wd_dev_emmc_geterrstr(enum wd_dev_emmc_errc * errc);

/**
 * @brief      Inits the EMMC
 *
 * @return     Error code
 */
enum wd_dev_emmc_errc wd_dev_emmc_init();