#ifndef SYSTEM_TICK_H
#define SYSTEM_TICK_H

#include <stdint.h>
#include <stdbool.h>

#define SYSTEM_TICK_FREQ_HZ 1000

void init_system_tick(void);
void msleep(uint32_t ms);
uint32_t get_elapsed_ms(void);

#endif // SYSTEM_TICK_H