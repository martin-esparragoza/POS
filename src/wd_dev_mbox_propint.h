/**
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
 * @{
 *
 * @brief      Property interface handler
 *
 */

#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

struct wd_dev_mbox_propint_tag {
    uint32_t identifier;
    uint32_t valuesize;
    uint32_t code;
    uint8_t value[];
} __attribute__((packed));

struct wd_dev_mbox_propint_buffer {
    uint32_t size;
    uint32_t code;
    struct wd_dev_mbox_propint_tag tags[];
} __attribute__((packed));

/**
 * @brief      Codes for buffer & tags
 */
enum wd_dev_mbox_propint_buffer_code {
    WD_DEV_MBOX_PROPINT_BUFFER_CODE_REQ =  0,          /**< Send a request */
    WD_DEV_MBOX_PROPINT_BUFFER_CODE_REQS = 0x80000000, /**< Successful request */
    WD_DEV_MBOX_PROPINT_BUFFER_CODE_REQF = 0x80000001  /**< Failed request */
};

/**
 * @brief      Constructor for buffer
 * 
 * Assumes that the code to add WILL be a request buffer
 * 
 * Sets default variables like size & code
 *
 * @param[in]  buffer  16 bit aligned buffer ptr
 * @param[in]  code    Code
 */
void wd_dev_mbox_propint_buffer_new(struct wd_dev_mbox_propint_buffer * buffer);

/**
 * @brief      Adds a REQUEST tag
 * 
 * Assumes that the type of the tag will be a request tag <br>
 * Remember to add space for response value
 *
 * @param[in]  buffer      Buffer
 * @param[in]  identifier  Identifier
 * @param[in]  value       Value
 * @param[in]  valuesize   Length of value in bytes
 * 
 * @return     Pointer to newly created tag
 * 
 * @see        <a href = "https://github.com/raspberrypi/firmware/wiki/Mailbox-property-interface">Identifiers</a>
 */
struct wd_dev_mbox_propint_tag * wd_dev_mbox_propint_buffer_addtag(struct wd_dev_mbox_propint_buffer * buffer, uint32_t identifier, void * value, uint32_t valuesize);

/**
 * @brief      Adds the final 0 to the buffer
 * 
 * You should not write to the buffer after this is done.
 * The only thing you can do is send.
 *
 * @param[in]  buffer  Buffer
 */
void wd_dev_mbox_propint_buffer_addendtag(struct wd_dev_mbox_propint_buffer * buffer);

/**
 * @brief      Get the size of buffer in bytes
 * 
 * @param[in]  buffer  Buffer
 *
 * @return     Size
 */
uint32_t wd_dev_mbox_propint_buffer_getsize(struct wd_dev_mbox_propint_buffer * buffer);

/**
 * @brief      Get request/response code of buffer
 * 
 * @param[in]  buffer  Buffer
 *
 * @return     Code
 */
enum wd_dev_mbox_propint_buffer_code wd_dev_mbox_propint_buffer_getcode(struct wd_dev_mbox_propint_buffer * buffer);

/**
 * @brief      Get tag from buffer (assuming properly made yk)
 * 
 * Remember to add your spaces for your buffers <br>
 * DOES NOT DO MAPPING! LAZY IMPLEMENTATION!
 *
 * @param[in]  buffer  Buffer
 * @param[in]  index   Index of tag
 *
 * @return     Pointer to tag NULL if reached end
 */
struct wd_dev_mbox_propint_tag * wd_dev_mbox_propint_buffer_gettag(struct wd_dev_mbox_propint_buffer * buffer, size_t index);

/**
 * @brief      Sends buffer to mailbox
 *
 * @param[in]  buffer  Buffer
 */
void wd_dev_mbox_propint_buffer_send(struct wd_dev_mbox_propint_buffer * buffer);

/**
 * @brief      Get identifier of tag
 * 
 * @param[in]  tag   Tag
 *
 * @return     Tag identifier
 */
uint32_t wd_dev_mbox_propint_tag_getidentifier(struct wd_dev_mbox_propint_tag * tag);

/**
 * @brief      Get size of value of tag
 *
 * @param[in]  tag   Tag
 *
 * @return     Tag value size in bytes
 */
uint32_t wd_dev_mbox_propint_tag_getvaluesize(struct wd_dev_mbox_propint_tag * tag);

/**
 * @brief      Get size returned
 * 
 * Gets bits 0-30 in response code <br>
 * Useful for ascii value return
 *
 * @param      tag   Tag
 *
 * @return     Tag value size in bytes
 */
uint32_t wd_dev_mbox_propint_buffer_getreturnvaluesize(struct wd_dev_mbox_propint_tag * tag);

/**
 * @brief      Tells you if tag was successfully processed
 *
 * @param[in]  tag   Tag
 *
 * @return     False if not true if so
 */
bool wd_dev_mbox_propint_tag_issuccessful(struct wd_dev_mbox_propint_tag * tag);

/**
 * @brief      Returns pointer to value
 *
 * @param[in]  tag   Tag
 *
 * @return     Value ptr
 */
void * wd_dev_mbox_propint_tag_getvalue(struct wd_dev_mbox_propint_tag * tag);

/**
 * @}
 * @}
 * @}
 */