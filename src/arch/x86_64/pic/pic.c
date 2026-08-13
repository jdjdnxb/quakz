#include <arch/x86_64/pic.h>
#include <arch/x86_64/io.h>
#include <logger.h>

void pic_send_eoi(uint8_t irq) {
	if(irq >= 8)
		outb(PIC2_COMMAND,PIC_EOI);
	outb(PIC1_COMMAND,PIC_EOI);
}

void pic_remap(void) {
    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();

    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();

    outb(PIC1_DATA, 0x20);
    io_wait();

    outb(PIC2_DATA, 0x28);
    io_wait();

    outb(PIC1_DATA, ICW3_MASTER);
    io_wait();

    outb(PIC2_DATA, ICW3_SLAVE);
    io_wait();

    outb(PIC1_DATA, ICW4_8086);
    io_wait();

    outb(PIC2_DATA, ICW4_8086);
    io_wait();

    outb(PIC1_DATA, 0xFE);
    outb(PIC2_DATA, 0xFF);

    log(LOG_OK, "IRQ0 unmasked.\n");
    log(LOG_OK, "PIC remapped.\n");
}