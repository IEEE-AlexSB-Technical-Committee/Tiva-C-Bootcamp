/*
 * UART.c
 *
 *  Created on: Feb 21, 2024
 *      Author: Ahmed Osama
 */
#include "UART.h"


std_return UART_Init(uart_t *_uart) {

    std_return ret_status = N_OK;
        uint32_t port_Select = 0;
        uint32_t port_base = 0;
        uint32_t uart_Select = 0;
        uint32_t p_rx = 0;
        uint32_t p_tx = 0;
        uint32_t basePin_rx = 0;
        uint32_t basePin_tx = 0;
        if(NULL == _uart){
            ret_status = N_OK;
        }
        else
        {
            switch(_uart->uart_Select){
                case UART0_BASE:
                    port_Select = SYSCTL_PERIPH_GPIOA;
                    port_base = GPIO_PORTA_BASE;
                    uart_Select = SYSCTL_PERIPH_UART0;
                    p_rx = GPIO_PA0_U0RX ;
                    p_tx = GPIO_PA1_U0TX ;
                    basePin_rx = GPIO_PIN_0;
                    basePin_tx = GPIO_PIN_1;
                    break;
                case UART1_BASE:
                    port_Select = SYSCTL_PERIPH_GPIOB;
                    port_base = GPIO_PORTB_BASE;
                    uart_Select = SYSCTL_PERIPH_UART1;
                    p_rx = GPIO_PB0_U1RX ;
                    p_tx = GPIO_PB1_U1TX ;
                    basePin_rx = GPIO_PIN_0;
                    basePin_tx = GPIO_PIN_1;
                    break;
                case UART2_BASE:
                    port_Select = SYSCTL_PERIPH_GPIOD;
                    port_base = GPIO_PORTD_BASE;
                    uart_Select = SYSCTL_PERIPH_UART2;
                    p_rx = GPIO_PD6_U2RX ;
                    p_tx = GPIO_PD7_U2TX ;
                    basePin_rx = GPIO_PIN_6;
                    basePin_tx = GPIO_PIN_7;
                    break;
                case UART3_BASE:
                    port_Select = SYSCTL_PERIPH_GPIOC;
                    port_base = GPIO_PORTC_BASE;
                    uart_Select = SYSCTL_PERIPH_UART3;
                    p_rx = GPIO_PC6_U3RX ;
                    p_tx = GPIO_PC7_U3TX ;
                    basePin_rx = GPIO_PIN_6;
                    basePin_tx = GPIO_PIN_7;
                    break;
                case UART4_BASE:
                    port_Select = SYSCTL_PERIPH_GPIOC;
                    port_base = GPIO_PORTC_BASE;
                    uart_Select = SYSCTL_PERIPH_UART4;
                    p_rx = GPIO_PC4_U4RX ;
                    p_tx = GPIO_PC5_U4TX ;
                    basePin_rx = GPIO_PIN_4;
                    basePin_tx = GPIO_PIN_5;
                    break;
                case UART5_BASE:
                    port_Select = SYSCTL_PERIPH_GPIOE;
                    port_base = GPIO_PORTE_BASE;
                    uart_Select = SYSCTL_PERIPH_UART5;
                    p_rx = GPIO_PE4_U5RX ;
                    p_tx = GPIO_PE5_U5TX ;
                    basePin_rx = GPIO_PIN_4;
                    basePin_tx = GPIO_PIN_5;
                    break;
                case UART6_BASE:
                    port_Select = SYSCTL_PERIPH_GPIOD;
                    port_base = GPIO_PORTD_BASE;
                    uart_Select = SYSCTL_PERIPH_UART6;
                    p_rx = GPIO_PD4_U6RX ;
                    p_tx = GPIO_PD5_U6TX ;
                    basePin_rx = GPIO_PIN_4;
                    basePin_tx = GPIO_PIN_5;
                    break;
                case UART7_BASE:
                    port_Select = SYSCTL_PERIPH_GPIOE;
                    port_base = GPIO_PORTE_BASE;
                    uart_Select = SYSCTL_PERIPH_UART7;
                    p_rx = GPIO_PE0_U7RX ;
                    p_tx = GPIO_PE1_U7TX ;
                    basePin_rx = GPIO_PIN_0;
                    basePin_tx = GPIO_PIN_1;
                    break;
                default :
                    port_Select = SYSCTL_PERIPH_GPIOA;
                    port_base = GPIO_PORTA_BASE;
                    uart_Select = SYSCTL_PERIPH_UART0;
                    p_rx = GPIO_PA0_U0RX ;
                    p_tx = GPIO_PA1_U0TX ;
                    basePin_rx = GPIO_PIN_0;
                    basePin_tx = GPIO_PIN_1;
                    break;
            }

            // Enable UARTx and GPIO Port x clock
            SysCtlPeripheralEnable(uart_Select);
            SysCtlPeripheralEnable(port_Select);

            // Set Pxx and Pxx as UART pins

            GPIOPinConfigure(p_rx);
            GPIOPinConfigure(p_tx);
            /* The function sets the pin type of Pxx and Pxx to UART*/
            GPIOPinTypeUART(port_base, basePin_rx | basePin_tx);

            // Configure UARTx
            UARTConfigSetExpClk(_uart->uart_Select, SysCtlClockGet(), _uart->baud_rate,
                        (_uart->data_length | _uart->stopBit_length |
                                _uart->parity_type));

            ret_status = OK;

        }
        return ret_status;
}


std_return UART_SendChar(uart_t *_uart,uint8_t data){
    std_return ret_status = N_OK;
    if(NULL == _uart){
        ret_status = N_OK;
    }
    else
    {
        UARTCharPut(_uart->uart_Select, data);
        ret_status = OK;
    }
    return ret_status;
}



std_return UART_SendString(uart_t *_uart,const char *str){
    std_return ret_status = N_OK;
    if(NULL == _uart){
        ret_status = N_OK;
    }
    else
    {
        while (*str) {
            UART_SendChar(_uart,*str++);
        }
        ret_status = OK;
    }
    return ret_status;
}


uint8_t UART_ReceiveChar(uart_t *_uart,std_return *retVal){
    std_return ret_status = N_OK;
    uint8_t receiveData = 0;
    if(NULL == _uart || retVal == NULL){
        ret_status = N_OK;
    }
    else
    {

        receiveData = UARTCharGet(_uart->uart_Select);
        ret_status = OK;
        *retVal = ret_status;
    }
    return receiveData;
}

std_return UART_ReceiveString(uart_t *_uart, char *str) {
    std_return t;
    *str = 0;

    while (*(str-1) != '\n' && *(str-1) != '\r') {
        *str++ = UART_ReceiveChar(_uart, &t);
    }
    *(str-1) = 0;
    return t;
}
