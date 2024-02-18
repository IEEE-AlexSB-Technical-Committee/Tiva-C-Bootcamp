/*
 * myUART.h
 *
 *  Created on: Feb 9, 2024
 *      Author: yusuf
 */

#ifndef MYUART_H_
#define MYUART_H_

#include "stdbool.h"
#include <stdint.h>
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"

#define UART(...) ((UART_t) {.periph_index = SYSCTL_PERIPH_UART0, .gpio_index = SYSCTL_PERIPH_GPIOA, .baud_rate = 115200,\
    .TX = GPIO_PA1_U0TX, .RX = GPIO_PA0_U0RX, .word_len = UART_CONFIG_WLEN_8, .parity_bit = UART_CONFIG_PAR_NONE, .stop_bit = UART_CONFIG_STOP_ONE, ##__VA_ARGS__})

typedef struct u {
    uint32_t periph_index;
    uint32_t gpio_index;
    uint32_t baud_rate;
    uint32_t TX;
    uint32_t RX;
    uint32_t word_len;
    uint32_t parity_bit;
    uint32_t stop_bit;
} UART_t;

void initUART(UART_t *ut);
void sendChar(UART_t *ut, char c);
void sendString(UART_t *ut, char* str);
char receiveChar(UART_t *ut);

#endif /* MYUART_H_ */
