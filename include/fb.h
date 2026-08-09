#pragma once

#include <stdint.h>

typedef struct {
    uint8_t *address;
    uint64_t height;
    uint64_t width;
    uint64_t pitch;
    uint16_t bpp;
    uint16_t bytes_per_pixel;
} framebuffer_t;

void framebuffer_init(void);
void put_pixel(uint32_t x, uint32_t y, uint32_t color);
void framebuffer_clear(uint32_t color);

extern framebuffer_t framebuffer;