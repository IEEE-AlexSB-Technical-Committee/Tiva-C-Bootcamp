/*
 * myUART.c
 *
 *  Created on: Feb 9, 2024
 *      Author: yusuf
 */


#include "myUART.h"

#include "stdbool.h"
#include <stdint.h>

#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"

void initUART(UART_t *ut) {
    SysCtlPeripheralEnable(ut->periph_index);
    SysCtlPeripheralEnable(ut->gpio_index);

    GPIOPinConfigure(ut->RX);
    GPIOPinConfigure(ut->TX);

    switch (ut->periph_index) {
        case SYSCTL_PERIPH_UART0:
            GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
            UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), ut->baud_rate, (ut->word_len | ut->stop_bit | ut->parity_bit));
            break;
        case SYSCTL_PERIPH_UART1:
            GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);
            UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), ut->baud_rate, (ut->word_len | ut->stop_bit | ut->parity_bit));
            break;
        case SYSCTL_PERIPH_UART2:
            GPIOPinTypeUART(GPIO_PORTD_BASE, GPIO_PIN_6 | GPIO_PIN_7);
            UARTConfigSetExpClk(UART2_BASE, SysCtlClockGet(), ut->baud_rate, (ut->word_len | ut->stop_bit | ut->parity_bit));
            break;
        case SYSCTL_PERIPH_UART3:
            GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_6 | GPIO_PIN_7);
            UARTConfigSetExpClk(UART3_BASE, SysCtlClockGet(), ut->baud_rate, (ut->word_len | ut->stop_bit | ut->parity_bit));
            break;
        case SYSCTL_PERIPH_UART4:
            GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5);
            UARTConfigSetExpClk(UART4_BASE, SysCtlClockGet(), ut->baud_rate, (ut->word_len | ut->stop_bit | ut->parity_bit));
            break;
        case SYSCTL_PERIPH_UART5:
            GPIOPinTypeUART(GPIO_PORTE_BASE, GPIO_PIN_4 | GPIO_PIN_5);
            UARTConfigSetExpClk(UART5_BASE, SysCtlClockGet(), ut->baud_rate, (ut->word_len | ut->stop_bit | ut->parity_bit));
            break;
        case SYSCTL_PERIPH_UART7:
            GPIOPinTypeUART(GPIO_PORTE_BASE, GPIO_PIN_0 | GPIO_PIN_1);
            UARTConfigSetExpClk(UART7_BASE, SysCtlClockGet(), ut->baud_rate, (ut->word_len | ut->stop_bit | ut->parity_bit));
            break;
    }
}

void sendChar(UART_t* ut, char c) {
    switch (ut->periph_index) {
        case SYSCTL_PERIPH_UART0:
            UARTCharPut(UART0_BASE, c);
            break;
        case SYSCTL_PERIPH_UART1:
            UARTCharPut(UART1_BASE, c);
            break;
        case SYSCTL_PERIPH_UART2:
            UARTCharPut(UART2_BASE, c);
            break;
        case SYSCTL_PERIPH_UART3:
            UARTCharPut(UART3_BASE, c);
            break;
        case SYSCTL_PERIPH_UART4:
            UARTCharPut(UART4_BASE, c);
            break;
        case SYSCTL_PERIPH_UART5:
            UARTCharPut(UART5_BASE, c);
            break;
        case SYSCTL_PERIPH_UART7:
            UARTCharPut(UART7_BASE, c);
            break;
    }
}

void sendString(UART_t* ut, char* str) {
    while (*str != '\0')
        sendChar(ut, *str++);
}

char receiveChar(UART_t* ut) {
    switch (ut->periph_index) {
        case SYSCTL_PERIPH_UART0:
            return UARTCharGet(UART0_BASE);
        case SYSCTL_PERIPH_UART1:
            return UARTCharGet(UART1_BASE);
        case SYSCTL_PERIPH_UART2:
            return UARTCharGet(UART2_BASE);
        case SYSCTL_PERIPH_UART3:
            return UARTCharGet(UART3_BASE);
        case SYSCTL_PERIPH_UART4:
            return UARTCharGet(UART4_BASE);
        case SYSCTL_PERIPH_UART5:
            return UARTCharGet(UART5_BASE);
        case SYSCTL_PERIPH_UART7:
            return UARTCharGet(UART7_BASE);
    }
}
