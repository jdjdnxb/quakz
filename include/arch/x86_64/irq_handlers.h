#pragma once 

#include <arch/x86_64/handlers.h>

__attribute__((interrupt))
void irq_timer(struct interrupt_frame *frame);