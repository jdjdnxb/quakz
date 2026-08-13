#pragma once

#include <stdint.h>

#define PIT_FREQUENCY 1193182
#define PIT_CHANNEL_0 0x40
#define PIT_COMMAND 0x43

void pit_init(uint32_t frequency);