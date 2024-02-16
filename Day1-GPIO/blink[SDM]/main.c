#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"
/**
 * main.c
 */

void delay_ms(uint32_t ui32ms);
int main(void)
{
	// Set system clock
	/**
	* SYSCTL_OSC_MAIN : Main oscillator
	* SYSCTL_XTAL_16MHZ: 16 MHz external crystal
	* SYSCTL_USE_PLL: Using PLL
	* SYSCTL_SYSDIV_2_5 : SYSDIV 2.5
	*
	* System clock is 80 MHz
	*/
    SysCtlClockSet(SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ | SYSCTL_USE_PLL | SYSCTL_SYSDIV_2_5);
	// Enable GPIO port
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));
	// Enable AHB bus
    SysCtlGPIOAHBEnable(SYSCTL_PERIPH_GPIOF);
	// Pin mode
    GPIOPinTypeGPIOOutput(GPIO_PORTF_AHB_BASE, GPIO_PIN_2);
    GPIOPinWrite(GPIO_PORTF_AHB_BASE, GPIO_PIN_2, 0);

    while(1) {
        GPIOPinWrite(GPIO_PORTF_AHB_BASE, GPIO_PIN_2, GPIO_PIN_2);
        delay_ms(1000);
        GPIOPinWrite(GPIO_PORTF_AHB_BASE, GPIO_PIN_2, 0);
        delay_ms(500);
    }
	return 0;
}

void delay_ms(uint32_t ui32ms) {
    SysCtlDelay(((float) SysCtlClockGet() * (float)ui32ms / 3000.0));
}
