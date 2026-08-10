#include <arch/x86_64/handlers.h>
#include <stdint.h>
#include <panic.h>
#include <kprintf.h>

__attribute__((interrupt))
void exception_divide_error(struct interrupt_frame *frame) {
    (void)frame;
    panic_begin(PANIC_EXCEPTION, "#DE Divide Error", NULL, 0);
    panic_end();
}

__attribute__((interrupt))
void exception_invalid_opcode(struct interrupt_frame *frame) {
    (void)frame;
    panic_begin(PANIC_EXCEPTION, "#UD Invalid Opcode", NULL, 0);
    panic_end();
}

__attribute__((interrupt))
void exception_double_fault(struct interrupt_frame *frame, uint64_t error_code) {
    panic_begin(PANIC_EXCEPTION, "#DF Double Fault", frame, error_code);
    panic_end();
}

__attribute__((interrupt))
void exception_page_fault(struct interrupt_frame *frame, uint64_t error_code) {
    panic_begin(PANIC_EXCEPTION, "#PF Page Fault", frame, error_code);
    panic_end();
}
