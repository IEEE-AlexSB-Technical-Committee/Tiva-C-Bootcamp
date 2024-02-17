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

int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
    SYSCTL_XTAL_16MHZ);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
    GPIOPinConfigure(GPIO_PF3_T1CCP1);
    GPIOPinTypeTimer(GPIO_PORTF_BASE, GPIO_PIN_3);
    TimerConfigure(TIMER1_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_B_PWM);
    TimerLoadSet(TIMER1_BASE, TIMER_B, 50000);
    TimerEnable(TIMER1_BASE, TIMER_B);

    while (1)
    {
        int i;
        for (i = 0; i < 50000; i++)
        {
            TimerMatchSet(TIMER1_BASE, TIMER_B, i);
            SysCtlDelay(100);
        }
        for (i = 50000; i > 0; i--)
        {
            TimerMatchSet(TIMER1_BASE, TIMER_B, i);
            SysCtlDelay(100);
        }
    }
}

