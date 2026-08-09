#include <fb.h>

void _start(void) {
    framebuffer_init();

    framebuffer_clear(0xFFFF0000);

    while (1) {
        asm volatile ("hlt");
    }
}

