/**
 * @file
 * 
 * @addtogroup WD
 * @{
 * 
 * @addtogroup DEV
 * @{
 * 
 * @addtogroup MBOX
 * @{
 * 
 * @defgroup   PROPINT
 * Property interface
 * @{
 *
 * @brief      Propint interface drivers
 */

#pragma once
#include <stdint.h>
#include <stddef.h>

struct pos_wd_dev_mbox_propint_tag {
    uint32_t identifier;
    uint32_t size;       /**< Private. Size of value buffer in bytes */
    uint32_t code;       /**< Request code that can be set */
    uint32_t value[];    /**< Cheat to align to 32 bit */
};

/**
 * @breif      Property interface util buffer
 * 
 * If you want to send/rcv this
 * you need to align it to a 32
 * bit boudary <br>
 */
struct pos_wd_dev_mbox_propint_buf {
    uint32_t size;                             /**< Size in bytes that is set by writer */
    uint32_t code;                             /**< Request/response code */
    struct pos_wd_dev_mbox_propint_tag tags[];
};

enum pos_wd_dev_mbox_propint_code {
    POS_WD_DEV_MBOX_PROPINT_CODE_REQ =     0,
    POS_WD_DEV_MBOX_PROPINT_CODE_REQSUC =  0x80000000, /**< Request successful. Used in responses. */
    POS_WD_DEV_MBOX_PROPINT_CODE_REQFAIL = 0x80000001  /**< Used in responses */
};

/**
 * @brief      Inits values for propint buffer writer
 *
 * @param      buffer  Pointer to buffer allocated some way or another
 */
void pos_wd_dev_mbox_propint_buf_new(struct pos_wd_dev_mbox_propint_buf * buffer, enum pos_wd_dev_mbox_propint_code code);

/**
 * @brief      Adds a tag to a propint buffer
 *
 * @param[in]  identifier  Identifier
 * @param[in]  code        Code
 * @param[in]  value       Value
 * @param[in]  valuesize   Size of value in bytes
 * 
 * @see        <a href = "https://github.com/raspberrypi/firmware/wiki/Mailbox-property-interface">Docs</a>
 */
void pos_wd_dev_mbox_propint_buf_addtag(struct pos_wd_dev_mbox_propint_buf * buffer, uint32_t identifier, uint32_t code, void* value, uint32_t valuesize);

/**
 * @brief      Resets position in buffer
 * 
 * Does not clear.
 *
 * @param      buffer  Buffer
 */
void pos_wd_dev_mbox_propint_buf_reset(struct pos_wd_dev_mbox_propint_buf * buffer);

/**
 * @brief      Send buffer to MBOX
 *
 * @param      buffer  Buffer
 */
void pos_wd_dev_mbox_propint_sendbuf(struct pos_wd_dev_mbox_propint_buf * buffer);

/**
 * @brief      Get tag from propint buffer
 *
 * @param      buffer  Buffer
 * @param[in]  index   Index of tag
 *
 * @return     NULL if cannot find
 */
struct pos_wd_dev_mbox_propint_tag * pos_wd_dev_mbox_propint_gettag(struct pos_wd_dev_mbox_propint_buf * buffer, unsigned index);