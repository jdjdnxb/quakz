#include <fb.h>
#include <text.h>
#include <stdint.h>
#include <terminal.h>
#include <kprintf.h>
#include <panic.h>
#include <arch/x86_64/idt.h>
#include <logger.h>
#include <pmm.h>
#include <requests.h>
#include <arch/x86_64/cpu.h>

terminal_t kernel_terminal;

// linker symbols
extern char _kernel_start[];
extern char _kernel_end[];

uint64_t kernel_size;
uint64_t kernel_phys_start;
uint64_t kernel_phys_end;

void _start(void) {
    ASSERT(kernel_address_request.response != NULL);
    ASSERT(hhdm_request.response != NULL);
    ASSERT(memmap_request.response != NULL);

    kernel_size = (uint64_t)(_kernel_end - _kernel_start);
    kernel_phys_start = kernel_address_request.response->physical_base;
    kernel_phys_end = kernel_address_request.response->physical_base + kernel_size;

    framebuffer_init();
    terminal_init(&kernel_terminal);
    cpu_init();
    idt_init();
    log(LOG_INFO, "HHDM offset: %x\n", hhdm_request.response->offset);
    pmm_init();

    kprintf("Quakz v0.0.1\n");

    while (1) {
        __asm__ volatile ("hlt");
    }
}