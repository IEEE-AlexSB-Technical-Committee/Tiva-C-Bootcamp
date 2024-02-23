/*
 * timer.h
 *
 *  Created on: Feb 21, 2024
 *      Author: Ahmed Osama
 */

#ifndef TIMER_TIMER_H_
#define TIMER_TIMER_H_

//----------------------------------------------- Include Files ------------------------------------
#include <stdint.h>
#include <stdbool.h>
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "std_return.h"

// Static variable to hold timer address
static uint32_t timer_addr;

//-----------------------------------------Functions Declarations ---------------------------------
extern void timerInt(void);                         // timer ISR
extern std_return timer_Init(uint32_t timer);       // Initialize timer
extern void delay_ms (uint32_t tempo);              // Delay


#endif /* TIMER_TIMER_H_ */
