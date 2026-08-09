#include <fb.h>
#include <text.h>
#include <stdint.h>

void _start(void) {
    framebuffer_init();

    framebuffer_clear(0x00000000);
    draw_string("Hello world, test 1234567890!", 100, 100, 0xFFFFFFFF);
    
    while (1) {
        asm volatile ("hlt");
    }
}

