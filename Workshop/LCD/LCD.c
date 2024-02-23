/*
 * LCD.c
 *
 *  Created on: Feb 21, 2024
 *      Author: Ahmed Osama
 */

#include "LCD.h"



std_return LCD_Init(lcd_t *_lcd) {
    std_return ret_status = OK;
    if(NULL == _lcd) {
        ret_status = N_OK;
    }
    else {
        SysCtlPeripheralEnable(_lcd->lcd_port_enable);
        GPIOPinTypeGPIOOutput(_lcd->lcd_port, 0xFF);


        GPIOPinWrite(_lcd->lcd_port, _lcd->RS,  0x00 );
        GPIOPinWrite(_lcd->lcd_port, _lcd->D4 | _lcd->D5 | _lcd->D6 | _lcd->D7,  0x30 );
        GPIOPinWrite(_lcd->lcd_port, _lcd->E, 0x02);
        SysCtlDelay(10);
        GPIOPinWrite(_lcd->lcd_port, _lcd->E, 0x00);

        SysCtlDelay(50000);

        GPIOPinWrite(_lcd->lcd_port, _lcd->D4 | _lcd->D5 | _lcd->D6 | _lcd->D7,  0x30 );
        GPIOPinWrite(_lcd->lcd_port, _lcd->E, 0x02);

        SysCtlDelay(10);

        GPIOPinWrite(_lcd->lcd_port, _lcd->E, 0x00);

        SysCtlDelay(50000);

        GPIOPinWrite(_lcd->lcd_port, _lcd->D4 | _lcd->D5 | _lcd->D6 | _lcd->D7,  0x30 );
        GPIOPinWrite(_lcd->lcd_port, _lcd->E, 0x02);
        SysCtlDelay(10);
        GPIOPinWrite(_lcd->lcd_port, _lcd->E, 0x00);

        SysCtlDelay(50000);

        GPIOPinWrite(_lcd->lcd_port, _lcd->D4 | _lcd->D5 | _lcd->D6 | _lcd->D7,  0x20 );
        GPIOPinWrite(_lcd->lcd_port, _lcd->E, 0x02);

        SysCtlDelay(10);

        GPIOPinWrite(_lcd->lcd_port, _lcd->E, 0x00);

        SysCtlDelay(50000);

        LCD_Command(_lcd, 0x0F);
        LCD_Clear(_lcd);
    }
    return ret_status;
}

std_return LCD_Command(lcd_t *_lcd, uint8_t c) {
    std_return ret_status = OK;
    if(NULL == _lcd) {
        ret_status = N_OK;
    }
    else {
        GPIOPinWrite(_lcd->lcd_port, _lcd->D4 |_lcd->D5 | _lcd->D6 | _lcd->D7, (c & 0xf0) );
        GPIOPinWrite(_lcd->lcd_port, _lcd->RS, 0x00);
        GPIOPinWrite(_lcd->lcd_port, _lcd->E, 0x02);

        SysCtlDelay(50000);

        GPIOPinWrite(_lcd->lcd_port, _lcd->E, 0x00);

        SysCtlDelay(50000);

        GPIOPinWrite(_lcd->lcd_port, _lcd->D4 | _lcd->D5 |_lcd->D6 | _lcd->D7, (c & 0x0f) << 4 );
        GPIOPinWrite(_lcd->lcd_port, _lcd->RS, 0x00);
        GPIOPinWrite(_lcd->lcd_port, _lcd->E, 0x02);

        SysCtlDelay(10);

        GPIOPinWrite(_lcd->lcd_port, _lcd->E, 0x00);

        SysCtlDelay(50000);
    }
    return ret_status;
}

std_return LCD_Show(lcd_t *_lcd, unsigned char d) {
    std_return ret_status = OK;
    if(NULL == _lcd) {
        ret_status = N_OK;
    }
    else {
        GPIOPinWrite(_lcd->lcd_port, _lcd->D4 | _lcd->D5 | _lcd->D6 | _lcd->D7, (d & 0xf0) );
        GPIOPinWrite(_lcd->lcd_port, _lcd->RS, 0x01);
        GPIOPinWrite(_lcd->lcd_port, _lcd->E, 0x02);

        SysCtlDelay(10);
        GPIOPinWrite(_lcd->lcd_port, _lcd->E, 0x00);
        SysCtlDelay(50000);

        GPIOPinWrite(_lcd->lcd_port, _lcd->D4 | _lcd->D5 | _lcd->D6 | _lcd->D7, (d & 0x0f) << 4 );
        GPIOPinWrite(_lcd->lcd_port, _lcd->RS, 0x01);
        GPIOPinWrite(_lcd->lcd_port, _lcd->E, 0x02);

        SysCtlDelay(10);
        GPIOPinWrite(_lcd->lcd_port, _lcd->E, 0x00);
        SysCtlDelay(50000);
    }
    return ret_status;
}

std_return LCD_Cursor(lcd_t *_lcd, uint8_t x, uint8_t y){
    std_return ret_status = OK;
    if(NULL == _lcd) {
        ret_status = N_OK;
    }
    else {
        if (x==0) {
            LCD_Command(_lcd, 0x80 + (y % 16));
            return ret_status;
        }
        LCD_Command(_lcd, 0xC0 + (y % 16));
    }
    return ret_status;
}

std_return LCD_Clear(lcd_t *_lcd){
    std_return ret_status = OK;
    if(NULL == _lcd) {
        ret_status = N_OK;
    }
    else {
        LCD_Command(_lcd, 0x01);
        SysCtlDelay(10);
    }
    return ret_status;
}

std_return LCD_PrintJustify(lcd_t *_lcd, uint8_t i, char *s, char *d) {
    std_return ret_status = OK;
    if(NULL == _lcd) {
        ret_status = N_OK;
    }
    else {
        if (i==0) {
            for (i=0; i<strlen(s); i++) {
                LCD_Cursor(_lcd, 0, i);
                LCD_Show(_lcd, s[i]);
            }
            for (i=0; i<strlen(d); i++) {
                LCD_Cursor(_lcd, 0, 15-i);
                LCD_Show(_lcd, d[strlen(d)-i-1]);
            }
            LCD_Command(_lcd, 0xC0 + 16);
            return ret_status;
        }
        for (i=0; i<strlen(s); i++) {
            LCD_Cursor(_lcd, 1, i);
            LCD_Show(_lcd, s[i]);
        }
        for (i=0; i<strlen(d); i++) {
            LCD_Cursor(_lcd, 1, 15-i);
            LCD_Show(_lcd, d[strlen(d)-i-1]);
        }
        LCD_Command(_lcd, 0xC0 + 16);
    }
    return ret_status;
}

std_return LCD_Print(lcd_t *_lcd, char *s, char *d) {
    std_return ret_status = OK;
    if(NULL == _lcd) {
        ret_status = N_OK;
    }
    else {
        int j;
        for (j=0; j<16; j++) {
            if (j<strlen(s)) {
                LCD_Cursor(_lcd, 0,j);
                LCD_Show(_lcd, s[j]);
            }
            if (j<strlen(d)) {
                LCD_Cursor(_lcd, 1,j);
                LCD_Show(_lcd, d[j]);
            }
        }
        LCD_Command(_lcd, 0xC0 + 16);
    }
    return ret_status;
}

std_return LCD_PrintLn(lcd_t *_lcd, uint8_t i, char *s) {
    std_return ret_status = OK;
    if(NULL == _lcd) {
        ret_status = N_OK;
    }
    else {
        LCD_Cursor(_lcd, i, 0);
        for (i=0; i<strlen(s); i++) {
            LCD_Show(_lcd, s[i]);
        }
        LCD_Command(_lcd, 0xC0 + 16);
    }
    return ret_status;
}

