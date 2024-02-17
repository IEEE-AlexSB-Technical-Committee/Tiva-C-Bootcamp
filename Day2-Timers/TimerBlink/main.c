#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_timer.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "MCAL/GPIO/GPIO.h"
#include "MCAL/Timers/timers.h"

int state = 0;

void interrupt_handler(void)
{
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, state);
    state ^= GPIO_PIN_3;
    TimerIntClear(WTIMER0_BASE, TIMER_A);
}

int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
    SYSCTL_XTAL_16MHZ);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER0);
    TimerConfigure(WTIMER0_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_PERIODIC);
    TimerLoadSet(WTIMER0_BASE, TIMER_A, SysCtlClockGet());
    TimerPrescaleSet(WTIMER0_BASE, TIMER_A, 2);
    TimerIntRegister(WTIMER0_BASE, TIMER_A, interrupt_handler);
    TimerIntEnable(WTIMER0_BASE, TIMER_A);
    TimerEnable(WTIMER0_BASE, TIMER_A);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);

    while (1)
    {
    }
}

