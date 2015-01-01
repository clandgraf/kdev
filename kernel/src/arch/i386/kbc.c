
#include <kernel/arch/i386/io.h>
#include <kernel/arch/i386/irq.h>
#include <kernel/klog.h>

#define KBC_STATUS        0x64
#define KBC_BUFFER        0x60

#define KBC_CMD_KBD_RESET 0xf4

void kbc_handler(uint8_t irq)
{
    uint8_t scancode = inb(KBC_BUFFER);

    klog_info("KBC: 0x%x\n", scancode);
}

void kbc_init(void)
{
    irq_register_handler(IRQ_KBC, &kbc_handler);

    /* Clear Keyboard Buffer */
    while (inb(KBC_STATUS) & 0x01)
     	inb(KBC_BUFFER);

    /* Wait til Keyboard is ready */
    while (inb(KBC_STATUS) & 0x02)
	;

    /* Reset Keyboard */
    outb(KBC_BUFFER, 0xf4);
}
