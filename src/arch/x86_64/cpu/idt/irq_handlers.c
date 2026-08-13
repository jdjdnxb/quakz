#include <arch/x86_64/irq_handlers.h>
#include <arch/x86_64/pic.h>
#include <arch/x86_64/handlers.h>
#include <kprintf.h>

extern volatile uint64_t ticks;

__attribute__((interrupt))
void irq_timer(struct interrupt_frame *frame) {
    (void)frame;
    ticks++;
    pic_send_eoi(0);
}