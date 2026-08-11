#pragma once

#include <stdint.h>

typedef struct {
    uint16_t size;           // sizeof(idt) - 1
    uint64_t offset;         // LINEAR address of the idt
} __attribute__((packed))idtr_t;

typedef struct {
   uint16_t offset_low;      // bits 0..15
   uint16_t selector;        // code segment selector in GDT or LDT
   uint8_t  ist;             // bits 0..2 hold the ist offset, rest of the bits are zero
   uint8_t  type_attributes; // gate type, dpl and p fields
   uint16_t offset_mid;      // bits 16..31
   uint32_t offset_high;     // bits 32..63
   uint32_t zero;            // reserved
} __attribute__((packed))idt_entry_t;

void idt_set_gate(uint8_t vector, void *handler);
void idt_init(void);