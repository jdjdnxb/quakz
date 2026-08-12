#pragma once

#include <stdint.h>
#include <arch/x86_64/handlers.h>

typedef enum {
    PANIC_FATAL,
    PANIC_ASSERT,
    PANIC_EXCEPTION
} panic_type_t;

void panic_begin(panic_type_t type, const char *reason, struct interrupt_frame *frame, uint64_t error_code);

__attribute__((noreturn))
void panic_end(void);

void assert_failed(const char *expression, const char *file, uint32_t line);

#define ASSERT(x) do { if(!(x)) assert_failed(#x, __FILE__, __LINE__); } while (0);