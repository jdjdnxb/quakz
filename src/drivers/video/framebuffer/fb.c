#include <limine.h>
#include <fb.h>
#include <stdint.h>
#include <requests.h>

static struct limine_framebuffer *limine_fb;
framebuffer_t framebuffer;

void framebuffer_init(void) {
    if (framebuffer_request.response == NULL) {
        while (1) {
            asm volatile ("hlt");
        }
    }
    limine_fb = framebuffer_request.response->framebuffers[0];

    framebuffer.address = limine_fb->address;
    framebuffer.width = limine_fb->width;
    framebuffer.height = limine_fb->height;
    framebuffer.pitch = limine_fb->pitch;
    framebuffer.bpp = limine_fb->bpp;
    framebuffer.bytes_per_pixel = limine_fb->bpp / 8;
}

void put_pixel(uint32_t x, uint32_t y, uint32_t color) {
    if (x >= framebuffer.width || y >= framebuffer.height)
        return;

    uintptr_t addr = (uintptr_t)framebuffer.address + (uintptr_t)y * framebuffer.pitch + (uintptr_t)x * framebuffer.bytes_per_pixel;

    *(uint32_t*)addr = color;
}

void framebuffer_clear(uint32_t color) {
    for (uint32_t i = 0; i < framebuffer.height; i++) {
        for (uint32_t j = 0; j < framebuffer.width; j++) {
            put_pixel(j, i, color);
        }
    }
}