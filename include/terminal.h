#pragma once 

#include <stdint.h>

#define TERMINAL_MARGIN 2

typedef struct {
    uint32_t cur_x;
    uint32_t cur_y;

    uint32_t width;
    uint32_t height;

    uint32_t fg;
    uint32_t bg;
} terminal_t;

void terminal_set_fg(terminal_t *terminal, uint32_t color);
void terminal_set_bg(terminal_t *terminal, uint32_t color);
void terminal_set_cursor(terminal_t *terminal, uint32_t x, uint32_t y);
void terminal_resize(terminal_t *terminal, uint32_t width, uint32_t height);
void terminal_clear(terminal_t *terminal);

void terminal_initialize(terminal_t *terminal);

void terminal_scroll(terminal_t *terminal);
void terminal_backspace(terminal_t *terminal);
void terminal_newline(terminal_t *terminal);
void terminal_tab(terminal_t *terminal);

void terminal_putchar(terminal_t *terminal, char c);
void terminal_write(terminal_t *terminal, const char *s);
void terminal_writeln(terminal_t *terminal, const char *s);

void terminal_write_colored(terminal_t *terminal, const char *s, uint32_t color);

void terminal_write_uint(terminal_t *terminal, uint64_t value);
void terminal_write_hex(terminal_t *terminal, uint64_t value);