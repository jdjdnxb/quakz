#include <terminal.h>
#include <logger.h>
#include <config.h>
#include <stdarg.h>
#include <kprintf.h>

extern terminal_t kernel_terminal;

#ifdef LOGGER_ENABLED

void log(log_type_t type, const char *fmt, ...) {
    uint32_t log_color;
    const char *status;

    switch(type) {
        case LOG_INFO:
            log_color = 0xFF8FA8B8;
            status = "INFO";
            break;
        case LOG_OK:
            log_color = 0xFF70D070;
            status = " OK ";
            break;
        case LOG_WARN:
            log_color = 0xFFFFB347;
            status = "WARN";
            break;
        case LOG_ERROR:
            log_color = 0xFFFF5555;
            status = "ERR ";
            break;
    }

    terminal_write_colored(&kernel_terminal, "[", log_color);
    terminal_write_colored(&kernel_terminal, status, log_color);
    terminal_write_colored(&kernel_terminal, "] ", log_color);

    va_list args;
    va_start(args, fmt);

    kvprintf(fmt, args);

    va_end(args);
}

#else

void log(log_type_t type, const char *message) {
    (void)type;
    (void)message;
}

#endif