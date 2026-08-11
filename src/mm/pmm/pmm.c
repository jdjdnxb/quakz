#include <pmm.h>
#include <stdint.h>
#include <logger.h>
#include <limine.h>
#include <requests.h>
#include <kprintf.h>
#include <utils.h>
#include <panic.h>

static uint64_t bitmap_pages;   // how many pages the bitmap needs
static uint64_t bitmap_phys;    // where bitmap storage starts

// physical address of the bitmaps
static uint64_t allocation_bitmap_phys;     
static uint64_t protection_bitmap_phys;

static uint64_t bitmap_size;

// HHDM addresses of the bitmaps (these are the ones we use to do allocating/protecting)
static uint8_t *allocation_bitmap;
static uint8_t *protection_bitmap;

static struct limine_memmap_response *memmap;
static uint64_t memmap_entry_count;

static uint64_t total_page_count;

// defined in main.c
extern uint64_t kernel_phys_start;
extern uint64_t kernel_phys_end;

static void pmm_mark_free(uint64_t address) {
    uint64_t page_number = address / PAGE_SIZE;
    uint64_t byte = page_number / 8;
    uint8_t bit = page_number % 8;

    if (protection_bitmap[byte] & (1 << bit)) {
        log(LOG_ERROR, "PMM: Refusing to mark protected page as free.\n");
        return;
    }

    allocation_bitmap[byte] &= ~(1 << bit);
}

static void pmm_mark_used(uint64_t address) {
    uint64_t page_number = address / PAGE_SIZE;
    uint64_t byte = page_number / 8;
    uint8_t bit = page_number % 8;
    allocation_bitmap[byte] |= (1 << bit);
}

static void pmm_mark_protected(uint64_t address) {
    uint64_t page_number = address / PAGE_SIZE;
    uint64_t byte = page_number / 8;
    uint8_t bit = page_number % 8;
    protection_bitmap[byte] |= (1 << bit);
}

static void pmm_mark_range_free(uint64_t start, uint64_t end) {
    for (uint64_t i = start; i < end; i += PAGE_SIZE) {
        pmm_mark_free(i);
    }
}

static void pmm_mark_range_used(uint64_t start, uint64_t end) {
    for (uint64_t i = start; i < end; i += PAGE_SIZE) {
        pmm_mark_used(i);
    }
}

static void pmm_mark_range_protected(uint64_t start, uint64_t end) {
    for (uint64_t i = start; i < end; i += PAGE_SIZE) {
        pmm_mark_protected(i);
    }
}

void pmm_init(void) {
    memmap = memmap_request.response;
    memmap_entry_count = memmap->entry_count;

    bitmap_phys = 0;
    // we need to find the highest address so we can get the total page count
    uint64_t highest_address = 0;
    for (uint64_t i = 0; i < memmap_entry_count; i++) {
        if (memmap->entries[i]->type != LIMINE_MEMMAP_USABLE)
            continue;

        uint64_t aligned_start = PAGE_ALIGN_UP(memmap->entries[i]->base);
        uint64_t aligned_end = PAGE_ALIGN_DOWN(memmap->entries[i]->base + memmap->entries[i]->length);
        kprintf("[PMM ] Found usable region: %x - %x\n", aligned_start, aligned_end);

        if (aligned_end > highest_address)
            highest_address = aligned_end;
    }

    total_page_count = CEIL_DIV(highest_address, PAGE_SIZE);
    bitmap_size = CEIL_DIV(total_page_count, 8);

    // calculate the size needed for both bitmaps directly
    bitmap_pages = CEIL_DIV(bitmap_size * 2, PAGE_SIZE);

    for (uint64_t i = 0; i < memmap_entry_count; i++) {
        if (memmap->entries[i]->type != LIMINE_MEMMAP_USABLE) 
            continue;
        
        uint64_t aligned_start = PAGE_ALIGN_UP(memmap->entries[i]->base);
        uint64_t aligned_end = PAGE_ALIGN_DOWN(memmap->entries[i]->base + memmap->entries[i]->length);

        if (aligned_end - aligned_start >= bitmap_pages * PAGE_SIZE) {
            bitmap_phys = aligned_start;
            kprintf("[PMM ] Bitmap needs %lu pages\n[PMM ] Bitmap storage starts at: %x\n", bitmap_pages, bitmap_phys);
            break;
        }
    }

    allocation_bitmap_phys = bitmap_phys;
    // bitmap_size is the size of a single bitmap
    protection_bitmap_phys = allocation_bitmap_phys + bitmap_size;

    ASSERT(hhdm_request.response != NULL);

    allocation_bitmap = (uint8_t *)(allocation_bitmap_phys + hhdm_request.response->offset);
    protection_bitmap = (uint8_t *)(protection_bitmap_phys + hhdm_request.response->offset);

    for (uint64_t i = 0; i < bitmap_size; i++) {
        // assume everything is unavailable
        allocation_bitmap[i] = 0xFF;    // 0xFF = 1111 1111
        protection_bitmap[i] = 0x00;
    }

    for (uint64_t i = 0; i < memmap_entry_count; i++) {
        if (memmap->entries[i]->type != LIMINE_MEMMAP_USABLE) 
            continue;
        
        uint64_t aligned_start = PAGE_ALIGN_UP(memmap->entries[i]->base);
        uint64_t aligned_end = PAGE_ALIGN_DOWN(memmap->entries[i]->base + memmap->entries[i]->length);
        
        pmm_mark_range_free(aligned_start, aligned_end);
    }

    uint64_t kernel_start = PAGE_ALIGN_DOWN(kernel_phys_start);
    uint64_t kernel_end = PAGE_ALIGN_UP(kernel_phys_end);

    // dont allow the PMM to hand out/free kernel/bitmap pages
    pmm_mark_range_used(kernel_start, kernel_end);
    pmm_mark_range_protected(kernel_start, kernel_end);
    
    uint64_t bitmap_start = PAGE_ALIGN_DOWN(bitmap_phys);
    uint64_t bitmap_end = PAGE_ALIGN_UP(bitmap_phys + bitmap_pages * PAGE_SIZE);

    pmm_mark_range_used(bitmap_start, bitmap_end);
    pmm_mark_range_protected(bitmap_start, bitmap_end);

    log(LOG_OK, "PMM enabled.\n");
}

uint64_t pmm_alloc_page() {
    uint64_t phys = 0;
    return phys;
}

void pmm_free_page(uint64_t address) {
    (void)address;
}

