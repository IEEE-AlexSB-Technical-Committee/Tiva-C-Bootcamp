/*
 * GPIO.h
 *
 *  Created on: Feb 21, 2024
 *      Author: Ahmed Osama
 */

#ifndef GPIO_GPIO_H_
#define GPIO_GPIO_H_
//----------------------------------------------- Include Files ------------------------------------
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "std_return.h"

//---------------------------------------------- Macros --------------------------------------------
#define INTERRUPT_EXTERNAL_INTx_FEATURE_ENABLE      INTERRUPT_FEATURE_ENABLE                // Enable interrupt
#define PIN(...) ((pin_t) { .port_name = GPIO_PORTF_AHB_BASE, .pin_number = GPIO_PIN_2, .dir_mode = GPIO_DIR_MODE_OUT, \
    .strength = GPIO_STRENGTH_2MA, .pad_type = GPIO_PIN_TYPE_STD, .ISR_Handler = NULL, .INT_type = 0, .INT_priotity = 0, ##__VA_ARGS__ })       // PIN constructor

//----------------------------------------- User define datatypes ----------------------------------
typedef struct {
    uint32_t port_name;
    uint8_t pin_number;
    uint32_t dir_mode;
    uint32_t strength;
    uint32_t pad_type;
#if INTERRUPT_FEATURE_ENABLE == INTERRUPT_EXTERNAL_INTx_FEATURE_ENABLE
    void(*ISR_Handler)(void);
    uint32_t INT_type;
    uint8_t INT_priotity;
#endif
} pin_t;                    // GPIO pin type

typedef enum {
        LOW = 0,
        HIGH
} GPIO_Level;               // Logic levels

//-----------------------------------------Functions Declarations ---------------------------------
extern std_return GPIO_Init(pin_t *pin_config);                                     // Initialize GPIO
extern std_return GPIO_Pin_Write(pin_t *pin_config, GPIO_Level level);              // Write on pin
extern GPIO_Level GPIO_Pin_Read_Acc(pin_t *pin_config, std_return *success);        // Read from pin, with acknowledgment
extern GPIO_Level GPIO_Pin_Read(pin_t *pin_config);                                 // Read from pin
extern std_return GPIO_Pin_Toggle(pin_t *pin_config);                               // Toggle pin
extern std_return GPIO_INT_Config(pin_t *int_pin);                                  // GPIO interrupt congiguration

#endif /* GPIO_GPIO_H_ */
