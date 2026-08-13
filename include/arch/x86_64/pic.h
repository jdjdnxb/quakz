#pragma once

#include <stdint.h>

#define PIC1		0x20		/* IO base address for master PIC */
#define PIC2		0xA0		/* IO base address for slave PIC */
#define PIC1_COMMAND	PIC1
#define PIC1_DATA	(PIC1+1)
#define PIC2_COMMAND	PIC2
#define PIC2_DATA	(PIC2+1)
#define PIC_EOI 0x20

#define ICW1_ICW4	0x01		/* Indicates that ICW4 will be present */
#define ICW1_INIT	0x10		/* Initialization - required! */

#define ICW3_MASTER 0x04
#define ICW3_SLAVE  0x02

#define ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */

void pic_send_eoi(uint8_t irq);
void pic_remap(void);