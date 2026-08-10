#include <fb.h>
#include <text.h>
#include <stdint.h>
#include <terminal.h>
#include <kprintf.h>
#include <panic.h>
#include <arch/x86_64/idt.h>

terminal_t kernel_terminal;

void _start(void) {
    framebuffer_init();
    terminal_init(&kernel_terminal);
    idt_init();

    // ASSERT(0);
    
    /* volatile int x = 1;
    volatile int y = 0;

    x = x / y; */

    // asm volatile ("ud2");

    volatile uint64_t *ptr = (uint64_t *)0x123456789ABC;
    *ptr = 0xDEADBEEF;

    while (1) {
        __asm__ volatile ("hlt");
    }
}