#include "wd_dev_sdhost.h"
#include "wd_dev_mbox_propint.h"
#include "wd_dev_mbox.h"
#include "wd_dev_uart1.h"
#include <stdbool.h>
#include <stdint.h>

bool pos_wd_dev_sdhost_init() {
    struct pos_wd_dev_mbox_propint_buf * buffer = __builtin_alloca_with_align(256, 128);
    pos_wd_dev_mbox_propint_buf_new(buffer, POS_WD_DEV_MBOX_PROPINT_CODE_REQ);
    uint32_t device_id = 0; // SD 
    pos_wd_dev_mbox_propint_buf_addtag(buffer, 0x00020001, 0, &device_id, sizeof(device_id));
    pos_wd_dev_mbox_propint_buf_addendtag(buffer);

    pos_wd_dev_mbox_propint_sendbuf(buffer);

    if (buffer->code != POS_WD_DEV_MBOX_PROPINT_CODE_REQSUC) {
        // PANIC!
        return false;
    }

    struct pos_wd_dev_mbox_propint_tag * tag = pos_wd_dev_mbox_propint_buf_gettag(buffer, 0);

    pos_wd_dev_uart1_printf("device id: %d\n", tag->value[0]);
    pos_wd_dev_uart1_printf("status: %d\n", tag->value[1]);

    return true;
}