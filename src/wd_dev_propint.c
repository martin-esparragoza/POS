#include "wd_dev_mbox_propint.h"
#include "wd_dev_mbox.h"
#include "wd_mem.h"
#include <stdint.h>

void pos_wd_dev_mbox_propint_buf_new(struct pos_wd_dev_mbox_propint_buf * buffer, enum pos_wd_dev_mbox_propint_code code) {
    buffer->size = sizeof(struct pos_wd_dev_mbox_propint_buf);
    buffer->code = code;
}

void pos_wd_dev_mbox_propint_buf_addtag(struct pos_wd_dev_mbox_propint_buf * buffer, uint32_t identifier, uint32_t code, void* value, uint32_t valuesize) {
    struct pos_wd_dev_mbox_propint_tag * tag = ((void *) buffer) + buffer->size;
    tag->identifier = identifier;
    tag->code = code;
    tag->size = valuesize;
    pos_wd_memcpy(value, tag->value, valuesize);
    // Align stolen
    buffer->size += sizeof(struct pos_wd_dev_mbox_propint_tag) + ((valuesize + 3) / 4) * 4 + 4;
}

void pos_wd_dev_mbox_propint_buf_reset(struct pos_wd_dev_mbox_propint_buf * buffer) {
    buffer->size = 0;
}

void pos_wd_dev_mbox_propint_sendbuf(struct pos_wd_dev_mbox_propint_buf * buffer) {
    *((uint32_t *) (buffer + buffer->size)) = 0; // Add 0 to mark end
    pos_wd_dev_mbox_write(POS_WD_DEV_MBOX_CHANNEL_PROPERTY_ARMTOVC, (uint32_t) (uintptr_t) (&buffer->size));
}

struct pos_wd_dev_mbox_propint_tag * pos_wd_dev_mbox_propint_gettag(struct pos_wd_dev_mbox_propint_buf * buffer, unsigned index) {
    struct pos_wd_dev_mbox_propint_tag * ptr = buffer->tags;

    for (unsigned i = 0; i < index; i++) {
        if (ptr->identifier == 0) {
            return NULL;
        }

        ptr += ptr->size;
    }

    return ptr;
}
