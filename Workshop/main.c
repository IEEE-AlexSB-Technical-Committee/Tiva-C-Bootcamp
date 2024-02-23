#include "stdint.h"
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include <GPIO/GPIO.h>
#include <UART/UART.h>
#include <timer/timer.h>
#include <LCD/LCD.h>

#define MAXLEN 100                  // Maximum possible length for password
#define PASSWORD "p@ssw0rd"         // The password
char pass[MAXLEN];                  // The array for incomming password
// Motor pins
pin_t m1 = PIN(.port_name = GPIO_PORTC_AHB_BASE, .pin_number = GPIO_PIN_2, .dir_mode = GPIO_DIR_MODE_OUT, .strength = GPIO_STRENGTH_8MA);
pin_t m2 = PIN(.port_name = GPIO_PORTC_AHB_BASE, .pin_number = GPIO_PIN_3, .dir_mode = GPIO_DIR_MODE_OUT, .strength = GPIO_STRENGTH_8MA);
// LED pins
pin_t red_led = PIN(.port_name = GPIO_PORTF_AHB_BASE, .pin_number = GPIO_PIN_1, .dir_mode = GPIO_DIR_MODE_OUT);
pin_t blue_led = PIN(.port_name = GPIO_PORTF_AHB_BASE, .pin_number = GPIO_PIN_2, .dir_mode = GPIO_DIR_MODE_OUT);
pin_t green_led = PIN(.port_name = GPIO_PORTF_AHB_BASE, .pin_number = GPIO_PIN_3, .dir_mode = GPIO_DIR_MODE_OUT);
// Terminal UART
uart_t terminal = UART(.uart_Select = UART0_BASE, .baud_rate = 115200,
                       .parity_type = UART_CONFIG_PAR_NONE, .data_length = UART_CONFIG_WLEN_8, .stopBit_length = UART_CONFIG_STOP_ONE);
// BlueTooth UART
uart_t bluetooth = UART(.uart_Select = UART1_BASE, .baud_rate = 9600,
                        .parity_type = UART_CONFIG_PAR_NONE, .data_length = UART_CONFIG_WLEN_8, .stopBit_length = UART_CONFIG_STOP_ONE);
// LCD
lcd_t lcd = LCD(.lcd_port = GPIO_PORTB_BASE, .lcd_port_enable = SYSCTL_PERIPH_GPIOB,
                .RS = GPIO_PIN_0, .E = GPIO_PIN_1, .D4 = GPIO_PIN_4, .D5 = GPIO_PIN_5, .D6 = GPIO_PIN_6, .D7 = GPIO_PIN_7);

/**
 * main.c
 */
int main(void)
{
    // Setup configuration
    SysCtlClockSet(SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ | SYSCTL_USE_PLL | SYSCTL_SYSDIV_2_5 );
    timer_Init(TIMER0_BASE);
    GPIO_Init(&red_led);
    GPIO_Init(&blue_led);
    GPIO_Init(&green_led);
    GPIO_Init(&m1);
    GPIO_Init(&m2);
    UART_Init(&terminal);
    UART_Init(&bluetooth);

    // Main loop
    while(1){
        UART_ReceiveString(&bluetooth, pass);                                   // Receiving from bluetooth
        if (strcmp(pass, PASSWORD) == 0) {                                      // Comparing incoming string with password
                    UART_SendString(&bluetooth, "correct password");
                    GPIO_Pin_Write(&green_led, HIGH);
                    GPIO_Pin_Write(&red_led, LOW);
                    GPIO_Pin_Write(&m1, HIGH);
                    GPIO_Pin_Write(&m2, LOW);
                    delay_ms(2000);
                    GPIO_Pin_Write(&m1, LOW);
                    GPIO_Pin_Write(&m2, LOW);
                    LCD_Print(&lcd, "Door open", "Welcome");
                    delay_ms(5000);
                    GPIO_Pin_Write(&green_led, LOW);
                    GPIO_Pin_Write(&red_led, HIGH);
                    GPIO_Pin_Write(&m1, LOW);
                    GPIO_Pin_Write(&m2, HIGH);
                    delay_ms(2000);
                    GPIO_Pin_Write(&m1, LOW);
                    GPIO_Pin_Write(&m2, LOW);
                    LCD_Clear(&lcd);
                    LCD_PrintLn(&lcd, 0, "Door closed");
                }
        else {
            GPIO_Pin_Write(&green_led, LOW);
            GPIO_Pin_Write(&red_led, HIGH);
            UART_SendString(&bluetooth, "wrong password");
            LCD_Clear(&lcd);
            LCD_PrintLn(&lcd, 0, "Door closed");
        }
    }
}
