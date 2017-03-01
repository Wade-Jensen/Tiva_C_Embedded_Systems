//*****************************************************************************
//
// blinky.c - Simple example to blink the on-board LED.
//
// Copyright (c) 2013-2016 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 2.1.3.156 of the DK-TM4C129X Firmware Package.
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/gpio.c"
#include "driverlib/sysctl.h"

//Timer stuff
#include "driverlib/timer.h"


void
Timer0IntHandler(void)
{
    //
    // Clear the timer interrupt.
    //
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    //
    // Toggle the flag for the first timer.
    //
    //HWREGBITW(&g_ui32Flags, 0) ^= 1;

    if( !GPIOPinRead(GPIO_PORTN_BASE,GPIO_PIN_5) ) {
        // LED is off, turn it on
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_5, GPIO_PIN_5);
    }
    else {
        // Turn off the LED.
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_5, 0x0);
    }
}
#define BASE_CLK 120000000  // 120MHz
void runTimer0AsPeriodic(uint32_t secs) {
    // Enable TIMER0 peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    // Setup TIMER0 to periodic behaviour
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    // Register the interrupt
    TimerIntRegister(TIMER0_BASE, TIMER_A, Timer0IntHandler);
    TimerLoadSet(TIMER0_BASE, TIMER_A, secs*BASE_CLK);
    TimerIntEnable(TIMER0_BASE, TIMER_A);
    TimerEnable(TIMER0_BASE, TIMER_A);
}


int
main(void)
{

    // Enable the GPIO port that is used for the on-board LED.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);

    // Check if the peripheral access is enabled.
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION))
    {
    }

    // Enable the GPIO pin for the LED (PQ7).  Set the direction as output, and
    // enable the GPIO pin for digital function.
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_5);

    runTimer0AsPeriodic(1);

    // Loop forever while the timers run.

    while(1)
    {
    }
}
