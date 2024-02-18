//#include "myUART.h"
#include "myUART.h"

#include "stdbool.h"
#include <stdint.h>

#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"

int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    bool state_r = false, state_g = false, state_b = false;

    UART_t u0 = UART(.baud_rate = 9600);
    UART_t u1 = UART(.periph_index = SYSCTL_PERIPH_UART1, .gpio_index = SYSCTL_PERIPH_GPIOB, .baud_rate = 9600,\
        .TX = GPIO_PB1_U1TX, .RX = GPIO_PB0_U1RX, .word_len = UART_CONFIG_WLEN_8, .parity_bit = UART_CONFIG_PAR_NONE, .stop_bit = UART_CONFIG_STOP_ONE);

    initUART(&u0);
    initUART(&u1);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0);

    while (1) {
        char c = receiveChar(&u1);

        sendString(&u0, "you entered:");
        sendChar(&u0, c);
        sendChar(&u0, '\n');

        switch (c) {
            case 'r':
                state_r = !state_r;
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, (state_r) ? GPIO_PIN_1 : 0);
                break;
            case 'g':
                state_g = !state_g;
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, (state_g) ? GPIO_PIN_3 : 0);
                break;
            case 'b':
                state_b = !state_b;
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, (state_b) ? GPIO_PIN_2 : 0);
                break;
        }
    }

}
