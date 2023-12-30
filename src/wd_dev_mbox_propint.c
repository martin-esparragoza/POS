#include "wd_dev_mbox_propint.h"
#include "../include/memory.h"
#include "wd_dev_mbox.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

void wd_dev_mbox_propint_buffer_new(volatile struct wd_dev_mbox_propint_buffer * buffer) {
    buffer->size = sizeof(struct wd_dev_mbox_propint_buffer);
    buffer->code = WD_DEV_MBOX_PROPINT_BUFFER_CODE_REQ;
}

volatile struct wd_dev_mbox_propint_tag * wd_dev_mbox_propint_buffer_addtag(volatile struct wd_dev_mbox_propint_buffer * buffer, uint32_t identifier, void * value, uint32_t valuesize) {
    volatile struct wd_dev_mbox_propint_tag * tag = ((void *) buffer) + buffer->size;
    // Adjust size to new tag creation
    buffer->size += sizeof(struct wd_dev_mbox_propint_tag) + valuesize;

    tag->identifier = identifier;
    tag->valuesize = valuesize;
    tag->code = 0; // Request
    memcpy_vd(tag->value, value, valuesize);

    // Align to 32 bits
    unsigned aligned = (buffer->size + 3) & ~3;
    memset(((void *) buffer) + buffer->size, 0, aligned);

    buffer->size = aligned;

    return tag;
}

void wd_dev_mbox_propint_buffer_addendtag(volatile struct wd_dev_mbox_propint_buffer * buffer) {
    ((uint32_t *) buffer)[buffer->size / 4] = 0;
    buffer->size += 4;
}

inline uint32_t wd_dev_mbox_propint_buffer_getsize(volatile struct wd_dev_mbox_propint_buffer * buffer) {
    return buffer->size;
}

inline enum wd_dev_mbox_propint_buffer_code wd_dev_mbox_propint_buffer_getcode(volatile struct wd_dev_mbox_propint_buffer * buffer) {
    return buffer->code;
}

volatile struct wd_dev_mbox_propint_tag * wd_dev_mbox_propint_buffer_gettag(volatile struct wd_dev_mbox_propint_buffer * buffer, size_t index) {
    volatile struct wd_dev_mbox_propint_tag * ret = buffer->tags;
    for (unsigned i = 0; i < index; i++) {
        if (ret->identifier == 0)
            return NULL;

        ret += ret->valuesize + sizeof(struct wd_dev_mbox_propint_tag *);
    }

    return ret;
}

void wd_dev_mbox_propint_buffer_send(volatile struct wd_dev_mbox_propint_buffer * buffer) {
    wd_dev_mbox_write(WD_DEV_MBOX_CHANNEL_PROPERTY_ARMTOVC, (((long) buffer) & ~0x0F) >> 4);
    while ((WD_DEV_MBOX_STATUS & 0x40000000) != 0) {;}
}

inline uint32_t wd_dev_mbox_propint_tag_getidentifier(volatile struct wd_dev_mbox_propint_tag * tag) {
    return tag->identifier;
}

inline uint32_t wd_dev_mbox_propint_tag_getvaluesize(volatile struct wd_dev_mbox_propint_tag * tag) {
    return tag->valuesize;
}

inline uint32_t wd_dev_mbox_propint_buffer_getreturnvaluesize(volatile struct wd_dev_mbox_propint_tag * tag) {
    return tag->code & 0x7FFFFFFF;
}

bool wd_dev_mbox_propint_tag_issuccessful(volatile struct wd_dev_mbox_propint_tag * tag) {
    return (tag->code & (1 << 31)) > 0;
}

inline volatile void * wd_dev_mbox_propint_tag_getvalue(volatile struct wd_dev_mbox_propint_tag * tag) {
    return tag->value;
}