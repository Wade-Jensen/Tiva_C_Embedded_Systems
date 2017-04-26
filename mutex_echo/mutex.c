/*
 * Copyright (c) 2015-2016, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


/* XDC module Headers */
#include <xdc/std.h>
#include <xdc/runtime/System.h>

/* BIOS module Headers */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>

/* Example/Board Header files */
#include "Board.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "grlib/grlib.h"
#include "drivers/kentec320x240x16_ssd2119.h"
#include "drivers/frame.h"
#include "drivers/pinout.h"

tContext sContext;
uint32_t digits = 0;

/*
 *  ======== mutex.c ========
 */

#define TASKSTACKSIZE   1024

Void task1Fxn(UArg arg0, UArg arg1);
Void task2Fxn(UArg arg0, UArg arg1);

Int resource = 0;
Int finishCount = 0;
UInt32 sleepTickCount;

Task_Struct task1Struct, task2Struct;
Char task1Stack[TASKSTACKSIZE], task2Stack[TASKSTACKSIZE];
Semaphore_Struct semStruct;
Semaphore_Handle semHandle;

char buff[25];
uint32_t i = 0;
uint32_t shouldPrint = 0;


//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif

//*****************************************************************************
//
// Send a string to the UART.
//
//*****************************************************************************
void
UARTSend(const uint8_t *pui8Buffer, uint32_t ui32Count)
{
    //
    // Loop while there are more characters to send.
    //
    while(ui32Count--)
    {
        //
        // Write the next character to the UART.
        //
        //UARTCharPutNonBlocking(UART0_BASE, *pui8Buffer++);
        UARTCharPut(UART0_BASE, *pui8Buffer++);
    }
}

/*
 *  ======== main ========
 */
Int main()
{
    uint32_t ui32SysClock;

    // Run from the PLL at 120 MHz.
    ui32SysClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                           SYSCTL_OSC_MAIN | SYSCTL_USE_PLL |
                                           SYSCTL_CFG_VCO_480), 120000000);


    // Configure the device pins.
    PinoutSet();

    // Initialize the display driver.
    Kentec320x240x16_SSD2119Init(ui32SysClock);

    // Initialize the graphics context.
    GrContextInit(&sContext, &g_sKentec320x240x16_SSD2119);

    // Draw the application frame.
    FrameDraw(&sContext, "uart-echo");

    // Display UART configuration on the display.
    GrStringDraw(&sContext, "Port:",       -1,  70, 70, 0);
    GrStringDraw(&sContext, "Baud:",       -1,  70, 95, 0);
    GrStringDraw(&sContext, "Data:",       -1,  70, 120, 0);
    GrStringDraw(&sContext, "Parity:",     -1,  70, 145, 0);
    GrStringDraw(&sContext, "Stop:",       -1,  70, 170, 0);
    GrStringDraw(&sContext, "Uart 0",      -1, 150, 70, 0);
    GrStringDraw(&sContext, "115,200 bps", -1, 150, 95, 0);
    GrStringDraw(&sContext, "8 Bit",       -1, 150, 120, 0);
    GrStringDraw(&sContext, "None",        -1, 150, 145, 0);
    GrStringDraw(&sContext, "1 Bit",       -1, 150, 170, 0);

    //
    // Enable the (non-GPIO) peripherals used by this example.  PinoutSet()
    // already enabled GPIO Port A.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    // Enable processor interrupts.
    IntMasterEnable();

    // Configure the UART for 115,200, 8-N-1 operation.

    UARTConfigSetExpClk(UART0_BASE, ui32SysClock, 115200,
                            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                             UART_CONFIG_PAR_NONE));

    //
    // Enable the UART interrupt.
    //
    //IntEnable(INT_UART0);
    //UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);

    // Prompt for text to be entered.
    UARTSend((uint8_t *)"Enter text: ", 12);


    /* Construct BIOS objects */
    Task_Params taskParams;
    Semaphore_Params semParams;

    /* Call board init functions */
    Board_initGeneral();

    /* Construct writer/reader Task threads */
    Task_Params_init(&taskParams);
    taskParams.stackSize = TASKSTACKSIZE;
    taskParams.stack = &task1Stack;
    taskParams.priority = 2;
    Task_construct(&task1Struct, (Task_FuncPtr)task1Fxn, &taskParams, NULL);

    taskParams.stack = &task2Stack;
    taskParams.priority = 1;
    Task_construct(&task2Struct, (Task_FuncPtr)task2Fxn, &taskParams, NULL);

    /* Construct a Semaphore object to be use as a resource lock, inital count 1 */
    Semaphore_Params_init(&semParams);
    Semaphore_construct(&semStruct, 1, &semParams);

    /* Obtain instance handle */
    semHandle = Semaphore_handle(&semStruct);

    /* We want to sleep for 10000 microseconds */
    sleepTickCount = 10000 / Clock_tickPeriod;

    BIOS_start();    /* Does not return */
    return(0);
}

/*
 *  ======== task1Fxn ========
 */
Void task1Fxn(UArg arg0, UArg arg1)
{
    UInt32 time;

    for (;;) {
        System_printf("Running task1 function\n");

        if (Semaphore_getCount(semHandle) == 0) {
            System_printf("Sem blocked in task1\n");
        }

        /* Get access to resource */
        Semaphore_pend(semHandle, BIOS_WAIT_FOREVER);

        /* Do work by waiting for 2 system ticks to pass */
        time = Clock_getTicks();
        while (Clock_getTicks() <= (time + 1)) {
            ;
        }

        /* Do work on locked resource */
        resource += 1;
        /* Unlock resource */


        while(UARTCharsAvail(UART0_BASE))
        {
            //
            // Read the next character from the UART and write it back to the UART.
            //
            buff[i] = UARTCharGet(UART0_BASE);
            UARTCharPut(UART0_BASE, buff[i]);
            i++;

            if (buff[i-1]=='\r') {
                digits = 0;
                if (i<9) {
                    digits = 1;
                }
                else if (i < 99) {
                    digits = 2;
                }
                else if (i<999) {
                    digits = 3;
                }

                shouldPrint = 1;

                //int j;
                //for (j=0; j<i; j++) {
                //    UARTCharPutNonBlocking(UART0_BASE, buff[j]);
                //}
            }

            //
        }
        Semaphore_post(semHandle);
        Task_sleep(sleepTickCount);
    }
}

/*
 *  ======== task2Fxn ========
 */
Void task2Fxn(UArg arg0, UArg arg1)
{
    for (;;) {
        System_printf("Running task2 function\n");

        if (Semaphore_getCount(semHandle) == 0) {
            System_printf("Sem blocked in task2\n");
        }

        /* Get access to resource */
        Semaphore_pend(semHandle, BIOS_WAIT_FOREVER);

        /* Do work on locked resource */
        resource += 1;
        /* Unlock resource */

        Semaphore_post(semHandle);

        //finishCount++;
        //if (finishCount == 5) {
        //    System_printf("Calling BIOS_exit from task2\n");
        //    BIOS_exit(0);
        //}



        if (shouldPrint) {

            char str[25];
            sprintf ( str, "\n%d characters received and displayed\n\r", i-1);
            UARTSend( (uint8_t *) str, 37+digits );
            UARTSend((uint8_t *)"\nEnter text: ", 12);

            GrStringDraw(&sContext, (const char*) buff, i-1, 10, 195, 1);
            i = 0;
            shouldPrint = 0;
        }


        Semaphore_post(semHandle);

        Task_sleep(sleepTickCount);
    }
}
