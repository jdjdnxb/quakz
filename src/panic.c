#include <panic.h>
#include <stdint.h>
#include <kprintf.h>
#include <terminal.h>
#include <arch/x86_64/handlers.h>

extern terminal_t kernel_terminal;

void panic_begin(panic_type_t type, const char *reason, struct interrupt_frame *frame, uint64_t error_code) {
    terminal_set_bg(&kernel_terminal, 0xFF101010);
    terminal_set_fg(&kernel_terminal, 0xFFFF5555);
    terminal_clear(&kernel_terminal);

    kprintf("==============================================\n");
    kprintf("               Kernel Panic!\n");
    kprintf("==============================================\n");

    kprintf("Whoops! Quakz has crashed. Good luck!\n");

    switch (type) {
        case PANIC_FATAL:
            kprintf("Reason: FATAL: %s\n", reason);
            break;
        case PANIC_EXCEPTION:
            kprintf("Reason: EXCEPTION: %s\n", reason);
            break;
        case PANIC_ASSERT:
            kprintf("Reason: ASSERTION FAILURE\n");
            break;
    }

    if (frame) {
        kprintf("Error Code: %x\n\n", error_code);

        kprintf("RIP:    %x\n", frame->rip);
        kprintf("CS:     %x\n", frame->cs);
        kprintf("RFLAGS: %x\n", frame->rflags);
        kprintf("RSP:    %x\n", frame->rsp);
        kprintf("SS:     %x\n\n", frame->ss);
    }
}

__attribute__((noreturn))
void panic_end(void) {
    __asm__ volatile("cli");
    while (1) {
        __asm__ volatile("hlt");
    }
}

void assert_failed(const char *expression, const char *file, uint32_t line) {
    panic_begin(PANIC_ASSERT, expression, NULL, 0);
    
    kprintf("Assertion failed!\n");
    kprintf("Expression: %s\n", expression);
    kprintf("File:       %s\n", file);
    kprintf("Line:       %u\n", line);

    panic_end();
}