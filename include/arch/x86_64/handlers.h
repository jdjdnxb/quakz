#pragma once

#include <stdint.h>

struct interrupt_frame {
    uint64_t rip;
    uint64_t cs;
    uint64_t rflags;
    uint64_t rsp;
    uint64_t ss;
};

// #DE 0
__attribute__((interrupt))
void exception_divide_error(struct interrupt_frame *frame);

// #OF 4

__attribute__((interrupt))
void exception_overflow(struct interrupt_frame *frame);

// #UD 6
__attribute__((interrupt))
void exception_invalid_opcode(struct interrupt_frame *frame);

// #DF 8
__attribute__((interrupt))
void exception_double_fault(struct interrupt_frame *frame, uint64_t error_code);

// #NP 11
__attribute__((interrupt))
void exception_segment_not_present(struct interrupt_frame *frame, uint64_t error_code);

// #SS 12
__attribute__((interrupt))
void exception_stack_segment_fault(struct interrupt_frame *frame, uint64_t error_code);

// #GP 13
__attribute__((interrupt))
void exception_general_protection(struct interrupt_frame *frame, uint64_t error_code);

// #PF 14
__attribute__((interrupt))
void exception_page_fault(struct interrupt_frame *frame, uint64_t error_code);
