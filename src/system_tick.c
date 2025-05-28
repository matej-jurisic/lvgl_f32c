#include "system_tick.h"

#include <time.h> // For get_cpu_freq()

#include <sys/isr.h>
#include <mips/asm.h>
#include <dev/io.h>

static volatile uint32_t s_system_ms_tick = 0; // Incremented by ISR, holds milliseconds since boot
static uint32_t s_cp0_tick_increment = 0;      // CPU cycles per millisecond tick

// --- ISR setup ---
static int cp0_timer_isr(void); // Forward declaration for the ISR function

static struct isr_link s_cp0_timer_link = {
    .handler_fn = &cp0_timer_isr // Link ISR function
};

// --- Interrupt Service Routine (ISR) ---
static int
cp0_timer_isr(void)
{
    s_system_ms_tick++; // Increment the global millisecond counter

    uint32_t current_count;
    mfc0_macro(current_count, MIPS_COP_0_COUNT); // Read current CP0 counter value
    // Set next interrupt: current_count + desired_cycles_per_tick
    mtc0_macro(current_count + s_cp0_tick_increment, MIPS_COP_0_COMPARE);

    return (1); // Acknowledge interrupt
}

// --- Public functions ---

void init_system_tick(void)
{
    // Calculate required CPU cycles based on SYSTEM_TICK_FREQ_HZ
    s_cp0_tick_increment = get_cpu_freq() / SYSTEM_TICK_FREQ_HZ;

    // Register our ISR with interrupt line 7 (MIPS CP0 Timer interrupt)
    isr_register_handler(7, &s_cp0_timer_link);

    // Set initial CP0_COMPARE value to trigger the first interrupt
    uint32_t current_count;
    mfc0_macro(current_count, MIPS_COP_0_COUNT);
    mtc0_macro(current_count + s_cp0_tick_increment, MIPS_COP_0_COMPARE);

    asm("ei"); // Enable global interrupts
}

uint32_t get_elapsed_ms(void)
{
    return s_system_ms_tick; // Return the current millisecond count
}

void msleep(uint32_t ms)
{
    if (ms == 0)
        return; // No delay needed for 0ms

    uint32_t start_time = get_elapsed_ms(); // Record start time
    uint32_t end_time = start_time + ms;    // Calculate target end time

    while (get_elapsed_ms() < end_time)
    {
        asm("wait"); // Put CPU to sleep until next interrupt
    }
}