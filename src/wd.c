/**
 * @defgroup   WD
 * Warpdrive
 * @{
 * @}
 */

#include <stdint.h>
#include "wd_dev_uart1.h"
#include "wd_dev_mbox.h"
#include "wd_dev_gpio.h"
#include "wd_stdio.h"
#include "wd_dev_sdhost.h"
#include "wd_dev_mbox_propint.h"
#include <stdint.h>

static uintmax_t wd_machine_id;
static uintptr_t wd_atags;

static volatile uint32_t __attribute__((aligned(16))) buffer1[] = {
    32, 0, 0x00010005, 8, 0, 0, 0, 0
};

static volatile uint32_t __attribute__((aligned(16))) buffer2[] = {
    32, 0, 0x00010003, 6, 0, 0, 0, 0
};

static volatile uint32_t __attribute__((aligned(16))) buffer3[] = {
    52, 0, 0x00010005, 8, 0, 0, 0, 0x00010003, 6, 0, 0, 0, 0
};

/**
 * Return if something bad happened otherwise chug on
 */
intmax_t 
#if BIT == 32
__attribute__((target("arm")))
#endif
    wd_main(uintmax_t r0 __attribute__((unused)), uintmax_t r1, uintmax_t r2) {
    // Disable IRQ and FIQ interrupts
#if BIT == 32
    __asm__ volatile("cpsid if");
#elif BITS == 64
    __asm__ volatile("msr daifset, #0xF");
#endif
    wd_machine_id = r1;
    wd_atags = (uintptr_t) r2;

    wd_dev_uart1_init();

    volatile uint32_t __attribute__((aligned(16))) testbuffer[256];
    struct wd_dev_mbox_propint_buffer * buffer = (void *) testbuffer;
    wd_dev_mbox_propint_buffer_new(buffer);
    uint32_t value[] = {0, 0};
    wd_dev_mbox_propint_buffer_addtag(buffer, 0x00010005, value, sizeof(value));
    wd_dev_mbox_propint_buffer_addendtag(buffer);

    wd_dev_uart1_printf("address: 0x%x\n", &buffer1);
    wd_dev_uart1_printf("address: 0x%x\n", &buffer2);
    wd_dev_mbox_write(WD_DEV_MBOX_CHANNEL_PROPERTY_ARMTOVC, (((long) buffer1) & ~0x0F) >> 4);
    wd_dev_mbox_write(WD_DEV_MBOX_CHANNEL_PROPERTY_ARMTOVC, (((long) buffer2) & ~0x0F) >> 4);
    wd_dev_mbox_write(WD_DEV_MBOX_CHANNEL_PROPERTY_ARMTOVC, (((long) buffer3) & ~0x0F) >> 4);
    //wd_dev_mbox_write(WD_DEV_MBOX_CHANNEL_PROPERTY_ARMTOVC, (((long) &testbuffer) & ~0x0F) >> 4);
    wd_dev_mbox_propint_buffer_send(buffer);

    for (unsigned i = 0; i < 8; i++) {
        wd_dev_uart1_printf("0x%x ", buffer1[i]);
    }
    wd_dev_uart1_printf("\n");

    for (unsigned i = 0; i < 8; i++) {
        wd_dev_uart1_printf("0x%x ", buffer2[i]);
    }
    wd_dev_uart1_printf("\n");

    for (unsigned i = 0; i < 13; i++) {
        wd_dev_uart1_printf("0x%x ", buffer3[i]);
    }
    wd_dev_uart1_printf("\n");

    for (unsigned i = 0; i < 13; i++) {
        wd_dev_uart1_printf("0x%x ", testbuffer[i]);
    }
    wd_dev_uart1_printf("\n");

    return 0xDEADBEEF;
}