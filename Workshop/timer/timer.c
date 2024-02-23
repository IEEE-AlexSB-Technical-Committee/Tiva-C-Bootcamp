/*
 * timer.c
 *
 *  Created on: Feb 21, 2024
 *      Author: Ahmed Osama
 */
#include "timer.h"

volatile uint32_t millis = 0;

/*
 * Interrupt handler
 */
void timerInt(void){
    uint32_t status = 0;
    status = TimerIntStatus(timer_addr,true);
    TimerIntClear(timer_addr,status);
    millis++;
}

/**
 * Initialize timer in periodic mode
 */
std_return timer_Init(uint32_t timer){
    std_return ret = N_OK;
    uint32_t ui32Period = SysCtlClockGet() / 1000; //1ms
    timer_addr = timer;
    switch (timer) {
        case TIMER0_BASE:
            SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
            SysCtlDelay(3);
            TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
            TimerLoadSet(TIMER0_BASE, TIMER_A, ui32Period - 1);
            TimerIntRegister(TIMER0_BASE, TIMER_A, timerInt);
            TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
            TimerEnable(TIMER0_BASE, TIMER_A);
            break;
        case TIMER1_BASE:
            SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
            SysCtlDelay(3);
            TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);
            TimerLoadSet(TIMER1_BASE, TIMER_A, ui32Period - 1);
            TimerIntRegister(TIMER1_BASE, TIMER_A, timerInt);
            TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
            TimerEnable(TIMER1_BASE, TIMER_A);
            break;
        case TIMER2_BASE:
            SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);
            SysCtlDelay(3);
            TimerConfigure(TIMER2_BASE, TIMER_CFG_PERIODIC);
            TimerLoadSet(TIMER2_BASE, TIMER_A, ui32Period - 1);
            TimerIntRegister(TIMER2_BASE, TIMER_A, timerInt);
            TimerIntEnable(TIMER2_BASE, TIMER_TIMA_TIMEOUT);
            TimerEnable(TIMER2_BASE, TIMER_A);
            break;
        case TIMER3_BASE:
            SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER3);
            SysCtlDelay(3);
            TimerConfigure(TIMER3_BASE, TIMER_CFG_PERIODIC);
            TimerLoadSet(TIMER3_BASE, TIMER_A, ui32Period - 1);
            TimerIntRegister(TIMER3_BASE, TIMER_A, timerInt);
            TimerIntEnable(TIMER3_BASE, TIMER_TIMA_TIMEOUT);
            TimerEnable(TIMER3_BASE, TIMER_A);
            break;
        case TIMER4_BASE:
            SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER4);
            SysCtlDelay(3);
            TimerConfigure(TIMER4_BASE, TIMER_CFG_PERIODIC);
            TimerLoadSet(TIMER4_BASE, TIMER_A, ui32Period - 1);
            TimerIntRegister(TIMER4_BASE, TIMER_A, timerInt);
            TimerIntEnable(TIMER4_BASE, TIMER_TIMA_TIMEOUT);
            TimerEnable(TIMER4_BASE, TIMER_A);
            break;
        case TIMER5_BASE:
            SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER5);
            SysCtlDelay(3);
            TimerConfigure(TIMER5_BASE, TIMER_CFG_PERIODIC);
            TimerLoadSet(TIMER5_BASE, TIMER_A, ui32Period - 1);
            TimerIntRegister(TIMER5_BASE, TIMER_A, timerInt);
            TimerIntEnable(TIMER5_BASE, TIMER_TIMA_TIMEOUT);
            TimerEnable(TIMER5_BASE, TIMER_A);
            break;

        default:
            break;
    }
    ret = OK;
    return ret;
}

/**
 * Delay function
 */
void delay_ms (uint32_t tempo) {
    volatile uint32_t temp = millis;
    while ((millis - temp) < tempo);
}
