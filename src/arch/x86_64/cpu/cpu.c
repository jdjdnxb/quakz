#include <arch/x86_64/cpu.h>
#include <cpuid.h>
#include <logger.h>
#include <stdbool.h>

bool cpu_has_sse(void) {
    unsigned int eax, ebx, ecx, edx;

    __cpuid(1, eax, ebx, ecx, edx);

    return (edx & (1 << 25)) != 0;
}

bool cpu_has_sse2(void) {
    unsigned int eax, ebx, ecx, edx;

    __cpuid(1, eax, ebx, ecx, edx);

    return (edx & (1 << 26)) != 0;
}

void cpu_init(void) {
    bool sse = cpu_has_sse();
    bool sse2 = cpu_has_sse2();
    log(LOG_INFO, "SSE:  %s\n", sse ? "Yes" : "No");
    if (sse) {
        // enable sse in the future
    }
    log(LOG_INFO, "SSE2: %s\n", sse2 ? "Yes" : "No");
    if (sse2) {
        // enable sse2 in the future
    }
}