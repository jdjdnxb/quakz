#include <font.h>
#include <fb.h>

void draw_char(char c, uint32_t x, uint32_t y, uint32_t fg, uint32_t bg) {
    const uint8_t *glyph = font8x16[(uint8_t)c];
    for (uint32_t row = 0; row < FONT_HEIGHT; row++) {
        uint8_t current_row = glyph[row];
        for (uint32_t col = 0; col < FONT_WIDTH; col++) {
            uint32_t pixel =
                (current_row & (1 << (7 - col)))
                    ? fg
                    : bg;

            put_pixel(x + col, y + row, pixel);
        }
    }
}

void draw_string(const char *s, uint32_t x, uint32_t y, uint32_t fg, uint32_t bg) {
    while (*s) {
        draw_char(*s, x, y, fg, bg);
        s++;
        x+=FONT_ADVANCE_X;
    }
}