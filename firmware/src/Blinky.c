#include <stdint.h>

#define GPIO_LEDs  0x80001404 // LED register address
#define GPIO_INOUT 0x80001408 // GPIO enable register
#define DELAY      0x500000   // Delay value

// Use volatile uint32_t for 32-bit register access
#define WRITE_ADDR(dir, value) { (*(volatile uint32_t *)(dir)) = (value); }
#define READ_ADDR(dir) (*(volatile uint32_t *)(dir))

void delay(uint32_t count) {
    volatile uint32_t i = 0;
    for (i = 0; i < count; i++) {
        // Empty loop to create a delay
    }
}

int main(void) {
    uint32_t led_state = 0;  // Initial LED state (32-bit)

    // Enable GPIO output (0xFFFF means enabling all pins, for example)
    WRITE_ADDR(GPIO_INOUT, 0xFFFF);

    while (1) {
        // Write the current LED state to the LED GPIO register
        WRITE_ADDR(GPIO_LEDs, led_state);

        // Toggle the LED state by inverting it
        led_state ^= 1;

        // Delay to control the blink speed
        delay(DELAY);
    }

    return 0;  // Never reached
}
