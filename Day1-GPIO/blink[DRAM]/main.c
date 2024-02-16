#include <stdint.h>

#include "inc/tm4c123gh6pm.h"
/**
 * main.c
 */
int main(void)
{
    uint32_t ui32Delay = 0;

    // 1. Enable GPIO port
    SYSCTL_RCGCGPIO_R |= 0x20;
    ui32Delay = SYSCTL_RCGCGPIO_R;

    // 2. Set direction as output
    GPIO_PORTF_DIR_R |= (1 << 1);


    // 3. Configure GPIOAFSEL to program PortF as GPIO
    GPIO_PORTF_AFSEL_R &= ~(1 << 1);

    // 4. Enable PF1 digital function
    GPIO_PORTF_DEN_R |= (1 << 1);
    GPIO_PORTF_DATA_R &= ~(1 << 1);

    while(1) {
        GPIO_PORTF_DATA_R ^= (1 << 1);

        for(ui32Delay = 0; ui32Delay < 400000; ui32Delay++);
    }

	return 0;
}
