#include <fb.h>
#include <text.h>
#include <stdint.h>
#include <terminal.h>
#include <kprintf.h>

terminal_t kernel_terminal;

void _start(void) {
    framebuffer_init();
    terminal_initialize(&kernel_terminal);
    terminal_write(&kernel_terminal, "ABCDEFGHIJKLMNOPQRSTUVWXYZ\nabcdefghijklmnopqrstuvwxyz\n1234567890\n");
    terminal_write_colored(&kernel_terminal, "This text is colored.\n", 0xFFFF0000);

    int x = 42;
    uint64_t y = 4717230;

    kprintf("kprintf test:\nx: %d\ny: %x\n", x, y);
    
    while (1) {
        asm volatile ("hlt");
    }
}