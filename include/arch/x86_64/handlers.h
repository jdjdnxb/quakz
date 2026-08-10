#pragma once

#include <stdint.h>

struct interrupt_frame {
    uint64_t rip;
    uint64_t cs;
    uint64_t rflags;
    uint64_t rsp;
    uint64_t ss;
};

__attribute__((interrupt))
void exception_divide_error(struct interrupt_frame *frame);

__attribute__((interrupt))
void exception_invalid_opcode(struct interrupt_frame *frame);

__attribute__((interrupt))
void exception_double_fault(struct interrupt_frame *frame, uint64_t error_code);

__attribute__((interrupt))
void exception_page_fault(struct interrupt_frame *frame, uint64_t error_code);
