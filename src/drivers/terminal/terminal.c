#include <terminal.h>
#include <text.h>
#include <fb.h>
#include <font.h>

extern framebuffer_t framebuffer;

void terminal_set_fg(terminal_t *terminal, uint32_t color) {
    terminal->fg = color;
}

void terminal_set_bg(terminal_t *terminal, uint32_t color) {
    terminal->bg = color;
}

void terminal_set_cursor(terminal_t *terminal, uint32_t x, uint32_t y) {
    terminal->cur_x = x;
    terminal->cur_y = y;
}

void terminal_resize(terminal_t *terminal, uint32_t width, uint32_t height) {
    terminal->width = width;
    terminal->height = height;
}

void terminal_clear(terminal_t *terminal) {
    framebuffer_clear(terminal->bg);
    terminal_set_cursor(terminal, TERMINAL_MARGIN, TERMINAL_MARGIN);
}

void terminal_init(terminal_t *terminal) {
    terminal_resize(terminal, framebuffer.width, framebuffer.height);

    terminal_set_fg(terminal, 0xFFEBE0BF);
    terminal_set_bg(terminal, 0xFF101010);

    terminal_clear(terminal);
}

void terminal_scroll(terminal_t *terminal) {
    (void)terminal;
}

void terminal_backspace(terminal_t *terminal) {
    if (terminal->cur_x == TERMINAL_MARGIN) 
        return;
    terminal->cur_x -= FONT_ADVANCE_X;

    draw_char(' ', terminal->cur_x, terminal->cur_y, terminal->fg, terminal->bg);
}

void terminal_newline(terminal_t *terminal) {
    terminal_set_cursor(terminal, TERMINAL_MARGIN, terminal->cur_y + FONT_ADVANCE_Y);

    /* if (terminal->cur_y + FONT_ADVANCE_Y >= terminal->height)
        terminal_scroll(); */
}

void terminal_tab(terminal_t *terminal) {
    terminal->cur_x += (FONT_ADVANCE_X) * TAB_SIZE;
    if (terminal->cur_x + (FONT_ADVANCE_X) > terminal->width) 
            terminal_newline(terminal);
}

void terminal_putchar(terminal_t *terminal, char c) {
    switch (c) {
        case '\n':
            terminal_newline(terminal);
            return;
        case '\t':
            terminal_tab(terminal);
            return;
        case '\b':
            terminal_backspace(terminal);
            return;
        default: 
            if ((terminal->cur_x + FONT_ADVANCE_X) > terminal->width)
                terminal_newline(terminal);

            draw_char(c, terminal->cur_x, terminal->cur_y, terminal->fg, terminal->bg);
            terminal->cur_x += FONT_ADVANCE_X;
    }
}

void terminal_write(terminal_t *terminal, const char *s) {
    while (*s) {
        terminal_putchar(terminal, *s);
        s++;
    }
}

void terminal_writeln(terminal_t *terminal, const char *s) {
    while (*s) {
        terminal_putchar(terminal, *s);
        s++;
    }
    terminal_putchar(terminal, '\n');
}

void terminal_write_colored(terminal_t *terminal, const char *s, uint32_t color) {
    uint32_t old_fg = terminal->fg;
    terminal->fg = color;
    terminal_write(terminal, s);
    terminal->fg = old_fg;
}

/*

TODO:

void terminal_write_uint(terminal_t *terminal, uint64_t value) {

}

void terminal_write_hex(terminal_t *terminal, uint64_t value) {

}
*/
