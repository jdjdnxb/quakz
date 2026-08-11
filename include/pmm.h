#pragma once

#include <stdint.h>

#define PAGE_SIZE 4096
#define PAGE_ALIGN_UP(x)   (((x) + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1))
#define PAGE_ALIGN_DOWN(x) ((x) & ~(PAGE_SIZE - 1))

void pmm_init(void);
uint64_t pmm_alloc_page();
void pmm_free_page(uint64_t address);
