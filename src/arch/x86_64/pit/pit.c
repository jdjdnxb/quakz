#include <arch/x86_64/pit.h>
#include <stdint.h>
#include <arch/x86_64/io.h>

void pit_init(uint32_t frequency) {
    uint16_t divisor = PIT_FREQUENCY / frequency;
    outb(PIT_COMMAND, 0x36);

    outb(PIT_CHANNEL_0, divisor & 0xFF);
    outb(PIT_CHANNEL_0, divisor >> 8);
}