/*
 * UART.h
 *
 *  Created on: Feb 21, 2024
 *      Author: Ahmed Osama
 */
#ifndef UART_UART_H_
#define UART_UART_H_

//----------------------------------------------- Include Files ------------------------------------
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/uart.h"
#include "std_return.h"

//---------------------------------------------- Macros --------------------------------------------
#define UART(...) ((uart_t) { .uart_Select = UART0_BASE, .baud_rate = 9600, .parity_type = UART_CONFIG_PAR_NONE, \
    .data_length = UART_CONFIG_WLEN_8, .stopBit_length = UART_CONFIG_STOP_ONE, ##__VA_ARGS__ })                     // UART constructor

//----------------------------------------- User define datatypes ----------------------------------
typedef struct{
    uint32_t uart_Select;
    uint32_t baud_rate;
    uint32_t parity_type;
    uint32_t data_length;
    uint32_t stopBit_length;
}uart_t;                        // UART type


//-----------------------------------------Functions Declarations ---------------------------------
std_return UART_Init(uart_t *_uart);                                // Initialize UART
std_return UART_SendChar(uart_t *_uart,uint8_t data);               // Send character
std_return UART_SendString(uart_t *_uart,const char *str);          // Send string
uint8_t UART_ReceiveChar(uart_t *_uart,std_return *retVal);         // Receive character
std_return UART_ReceiveString(uart_t *_uart, char *str);            //  Receive string


#endif /* UART_UART_H_ */
