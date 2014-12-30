#ifndef __IRQ_H__
#define __IRQ_H__

#include <stdint.h>

typedef void (*irq_handler_t)(uint8_t irq);

void irq_register_handler(uint8_t irq, irq_handler_t handler);


#endif
