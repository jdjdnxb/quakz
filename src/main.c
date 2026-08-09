#include <fb.h>

void _start(void) {
    framebuffer_init();

    while (1) {
        asm volatile ("hlt");
    }
}

