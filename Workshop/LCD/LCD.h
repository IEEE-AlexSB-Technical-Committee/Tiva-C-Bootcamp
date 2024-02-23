/*
 * LCD.h
 *
 *  Created on: Feb 21, 2024
 *      Author: Ahmed Osama
 */

#ifndef LCD_LCD_H_
#define LCD_LCD_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "string.h"
#include "std_return.h"

//---------------------------------------------- Macros --------------------------------------------
#define LCD(...) ((lcd_t) { .lcd_port = GPIO_PORTB_BASE, .lcd_port_enable = SYSCTL_PERIPH_GPIOB, .RS = GPIO_PIN_0,\
    .E = GPIO_PIN_1, .D4 = GPIO_PIN_4, .D5 = GPIO_PIN_5, .D6 = GPIO_PIN_6, .D7 = GPIO_PIN_7, ##__VA_ARGS__ })                   // LCD constructor

//----------------------------------------- User define datatypes ----------------------------------
typedef struct{
    uint32_t lcd_port;
    uint32_t lcd_port_enable;
    uint32_t RS;
    uint32_t E;
    uint32_t D4;
    uint32_t D5;
    uint32_t D6;
    uint32_t D7;
}lcd_t;             // LCD type

std_return LCD_Init(lcd_t *_lcd);                                               //LCD initialization
std_return LCD_Command(lcd_t *_lcd, uint8_t c);                                 //Send command
std_return LCD_Show(lcd_t *_lcd, unsigned char d);                              //Show a char
std_return LCD_Clear(lcd_t *_lcd);                                              //Clear the screen
std_return LCD_Print(lcd_t *_lcd, char *s, char *d);                            //Print 2 lines
std_return LCD_PrintLn(lcd_t *_lcd, uint8_t i, char *s);                        //Print specific line
std_return LCD_PrintJustify(lcd_t *_lcd, uint8_t i, char *s, char *d);          //Print specific line floated left and floated right text
std_return LCD_Cursor(lcd_t *_lcd, uint8_t x, uint8_t y);                       //Set cursor


#endif /* LCD_LCD_H_ */
