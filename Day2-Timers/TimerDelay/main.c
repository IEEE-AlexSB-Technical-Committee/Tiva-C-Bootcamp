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
//#include "MCAL/Timers/timers.h"

static volatile bool delay_flag = false;

void interrupt_handler(void)
{
    TimerIntClear(WTIMER0_BASE, TIMER_TIMB_TIMEOUT);
    delay_flag = true;
}

void delay(uint32_t millis)
{
    TimerPrescaleSet(WTIMER0_BASE, TIMER_B, 100);
    TimerLoadSet(WTIMER0_BASE, TIMER_B,
                 (SysCtlClockGet() / 100000) * millis);
    TimerEnable(WTIMER0_BASE, TIMER_B);
    while (!delay_flag)
        ;
    delay_flag = false;
}

int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
    SYSCTL_XTAL_16MHZ);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER0);
    IntMasterEnable();
    TimerConfigure(WTIMER0_BASE,
    TIMER_CFG_SPLIT_PAIR | TIMER_CFG_B_ONE_SHOT);
    TimerIntRegister(WTIMER0_BASE, TIMER_B, interrupt_handler);
    TimerIntEnable(WTIMER0_BASE, TIMER_TIMB_TIMEOUT);
    IntEnable(INT_WTIMER0B);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);

    while (1)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
        delay(1000);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0);
        delay(1000);
    }
}

