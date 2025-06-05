// Standard library headers
#include <time.h> // For get_cpu_freq()

// Device and hardware-specific headers
#include <sys/isr.h>
#include <mips/asm.h>
#include <dev/io.h>

// LVGL F32C framework headers
#include "system_tick.h"

static volatile uint32_t s_system_ms_tick = 0; // Incremented by ISR, holds milliseconds since boot
static uint32_t s_cp0_tick_increment = 0;      // CPU cycles per millisecond tick

static int cp0_timer_isr(void);

static struct isr_link s_cp0_timer_link = {
    .handler_fn = &cp0_timer_isr // Link ISR function
};

static int
cp0_timer_isr(void)
{
    uint32_t current_count;

    s_system_ms_tick++; // Increment the global millisecond counter

    mfc0_macro(current_count, MIPS_COP_0_COUNT); // Read current CP0 counter value
    // Set next interrupt: current_count + desired_cycles_per_tick
    mtc0_macro(current_count + s_cp0_tick_increment, MIPS_COP_0_COMPARE);

    return (1);
}

void lv_f32c_init_system_tick(void)
{
    uint32_t current_count;

    // Calculate required CPU cycles based on SYSTEM_TICK_FREQ_HZ
    s_cp0_tick_increment = get_cpu_freq() / SYSTEM_TICK_FREQ_HZ;

    // Register ISR
    isr_register_handler(7, &s_cp0_timer_link);

    // Set initial CP0_COMPARE value to trigger the first interrupt
    mfc0_macro(current_count, MIPS_COP_0_COUNT);
    mtc0_macro(current_count + s_cp0_tick_increment, MIPS_COP_0_COMPARE);

    asm("ei"); // Enable global interrupts
}

uint32_t lv_f32c_get_elapsed_ms(void)
{
    return s_system_ms_tick;
}

void lv_f32c_msleep(uint32_t ms)
{
    uint32_t start_time, end_time;

    if (ms == 0)
        return; // No delay needed for 0ms

    start_time = lv_f32c_get_elapsed_ms(); // Record start time
    end_time = start_time + ms;            // Calculate target end time

    while (lv_f32c_get_elapsed_ms() < end_time)
    {
        asm("wait"); // Put CPU to sleep until next interrupt
    }
}