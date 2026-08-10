#include <arch/x86_64/idt.h>
#include <stdint.h>
#include <arch/x86_64/handlers.h>
#include <kprintf.h>

static idtr_t idtr;
static idt_entry_t idt[256];

static inline void lidt(idtr_t *idtr) {
    __asm__ volatile("lidt %0" :: "m"(*idtr) : "memory");
}

void idt_set_gate(uint8_t vector, void *handler) {
    uint64_t address = (uint64_t)handler;
    
    idt[vector].offset_low = (uint16_t)(address & 0xFFFF);
    idt[vector].offset_mid = (uint16_t)((address >> 16) & 0xFFFF);
    idt[vector].offset_high = (uint32_t)((address >> 32));

    idt[vector].selector = 0x28;    // kernel code segment selector

    // we dont need these yet
    idt[vector].ist = 0;
    idt[vector].type_attributes = 0x8E;
    
    idt[vector].zero = 0;
}

void idt_init(void) {
    idt_set_gate(0, &exception_divide_error);
    idt_set_gate(6, &exception_invalid_opcode);
    idt_set_gate(8, &exception_double_fault);
    idt_set_gate(14, &exception_page_fault);

    idtr.size = sizeof(idt) - 1;
    idtr.offset = (uint64_t)idt;    // address needs to be 64 bits wide

    lidt(&idtr);
    // __asm__ volatile("sti");

    kprintf("IDT initialized.\n");
}