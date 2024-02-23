/*
 * GPIO.c
 *
 *  Created on: Feb 21, 2024
 *      Author: Ahmed Osama
 */
#include "GPIO.h"


std_return GPIO_Init(pin_t *pin_config) {
    switch (pin_config->port_name) {
        case GPIO_PORTA_AHB_BASE:
            SysCtlGPIOAHBEnable(SYSCTL_PERIPH_GPIOA);
        case GPIO_PORTA_BASE:
            SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
            while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA));
            break;
        case GPIO_PORTB_AHB_BASE:
            SysCtlGPIOAHBEnable(SYSCTL_PERIPH_GPIOB);
        case GPIO_PORTB_BASE:
            SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
            while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB));
            break;
        case GPIO_PORTC_AHB_BASE:
            SysCtlGPIOAHBEnable(SYSCTL_PERIPH_GPIOC);
        case GPIO_PORTC_BASE:
            SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
            while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC));
            break;
        case GPIO_PORTD_AHB_BASE:
            SysCtlGPIOAHBEnable(SYSCTL_PERIPH_GPIOD);
        case GPIO_PORTD_BASE:
            SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
            while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD));
            break;
        case GPIO_PORTE_AHB_BASE:
            SysCtlGPIOAHBEnable(SYSCTL_PERIPH_GPIOE);
        case GPIO_PORTE_BASE:
            SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
            while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE));
            break;
        case GPIO_PORTF_AHB_BASE:
            SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
        case GPIO_PORTF_BASE:
            while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));
            SysCtlGPIOAHBEnable(SYSCTL_PERIPH_GPIOF);
            break;
        default:
            return N_OK;
    }

    GPIOPadConfigSet(pin_config->port_name, pin_config->pin_number, pin_config->strength, pin_config->pad_type);
    GPIODirModeSet(pin_config->port_name, pin_config->pin_number, pin_config->dir_mode);
    GPIOPinWrite(pin_config->port_name, pin_config->pin_number, LOW);

    return OK;
}

std_return GPIO_Pin_Write(pin_t *pin_config, GPIO_Level level) {
    switch (level) {
        case HIGH:
            GPIOPinWrite(pin_config->port_name, pin_config->pin_number, pin_config->pin_number);
            break;
        case LOW:
            GPIOPinWrite(pin_config->port_name, pin_config->pin_number, LOW);
            break;
        default:
            return N_OK;
    }
    return OK;
}

GPIO_Level GPIO_Pin_Read_Ack(pin_t *pin_config, std_return *success) {
    int32_t value = GPIOPinRead(pin_config->port_name, pin_config->pin_number);
    *success = OK;
    return (GPIO_Level)value;
}

GPIO_Level GPIO_Pin_Read(pin_t *pin_config) {
    return (GPIO_Level)GPIOPinRead(pin_config->port_name, pin_config->pin_number);
}

std_return GPIO_Pin_Toggle(pin_t *pin_config) {
    std_return ret = N_OK;
    if(GPIO_Pin_Read(pin_config) == LOW)
        ret = GPIO_Pin_Write(pin_config, HIGH);
    else
        ret = GPIO_Pin_Write(pin_config, LOW);
    return ret;
}

std_return GPIO_INT_Config(pin_t *int_pin) {
    std_return ret = N_OK;
    uint8_t port = 0;
    if (int_pin != NULL) {
        switch (int_pin->port_name) {
            case GPIO_PORTA_AHB_BASE:
            case GPIO_PORTA_BASE:
                port = INT_GPIOA;
                break;
            case GPIO_PORTB_AHB_BASE:
            case GPIO_PORTB_BASE:
                port = INT_GPIOB;
                break;
            case GPIO_PORTC_AHB_BASE:
            case GPIO_PORTC_BASE:
                port = INT_GPIOC;
                break;
            case GPIO_PORTD_AHB_BASE:
            case GPIO_PORTD_BASE:
                port = INT_GPIOD;
                break;
            case GPIO_PORTE_AHB_BASE:
            case GPIO_PORTE_BASE:
                port = INT_GPIOE;
                break;
            case GPIO_PORTF_AHB_BASE:
            case GPIO_PORTF_BASE:
                port = INT_GPIOF;
                break;
            default:
                return ret;
        }
        IntMasterDisable();
        GPIOIntClear(int_pin->port_name, int_pin->pin_number);
        IntRegister(port, int_pin->ISR_Handler);
        GPIOIntTypeSet(int_pin->port_name, int_pin->pin_number, int_pin->INT_type);
        IntPrioritySet(port, int_pin->INT_priotity);
        GPIOIntEnable(int_pin->port_name, int_pin->pin_number);
        IntEnable(port);
        IntMasterEnable();
        ret = OK;
    }
    return ret;
}
