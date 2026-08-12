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
void exception_overflow(struct interrupt_frame *frame) {
    (void)frame;
    panic_begin(PANIC_EXCEPTION, "#OF Overflow", NULL, 0);
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
void exception_segment_not_present(struct interrupt_frame *frame, uint64_t error_code) {
    panic_begin(PANIC_EXCEPTION, "#NP Segment Not Present", frame, error_code);
    panic_end();
}

__attribute__((interrupt))
void exception_stack_segment_fault(struct interrupt_frame *frame, uint64_t error_code) {
    panic_begin(PANIC_EXCEPTION, "#SS Stack-Segment Fault", frame, error_code);
    panic_end();
}

__attribute__((interrupt))
void exception_general_protection(struct interrupt_frame *frame, uint64_t error_code) {
    panic_begin(PANIC_EXCEPTION, "#GP General Protection Fault", frame, error_code);
    panic_end();
}

__attribute__((interrupt))
void exception_page_fault(struct interrupt_frame *frame, uint64_t error_code) { 
    uint64_t cr2;
    __asm__ volatile("mov %%cr2, %0" : "=r"(cr2));

    panic_begin(PANIC_EXCEPTION, "#PF Page Fault", frame, error_code);
    kprintf("CR2: %x", cr2);
    panic_end();
}
