
/*
 * common.c
 *
 *  Created on: 24Apr.,2017
 *      Author: WadeJensen
 */

#include <stdint.h>
#include <stdbool.h>

#include "drivers/pinout.h"
#include "driverlib/gpio.h"
#include "inc/tm4c1297nczad.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"

void setupLedOuputs() {
    // Red LED output
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_5);
    // Green LED output
    GPIOPinTypeGPIOOutput(GPIO_PORTQ_BASE, GPIO_PIN_7);
    // Blue LED output
    GPIOPinTypeGPIOOutput(GPIO_PORTQ_BASE, GPIO_PIN_4);
    // Speed LED Output
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);
    // Link LED Outputm
    GPIOPinTypeGPIOOutput(GPIO_PORTK_BASE, GPIO_PIN_4);
    // Active LED Output
    GPIOPinTypeGPIOOutput(GPIO_PORTK_BASE, GPIO_PIN_6);
}

void setupPushButtonInputs() {
    // PE5/PN3/PP1 are used for the push buttons.
    GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_5);
    GPIOPinTypeGPIOInput(GPIO_PORTN_BASE, GPIO_PIN_3);
    GPIOPinTypeGPIOInput(GPIO_PORTP_BASE, GPIO_PIN_1);
}

void busyWaitRed() {
    // flash red light for 10 secs
    int j;
    for (j = 0; j<2; j++) {
        int k = 0;
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_5, GPIO_PIN_5);
        int i;
        for (i=0; i<2400000; i++) {
            k++;
        }
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_5, 0x0);
    }
}

void busyWaitGreen() {
    // flash green light for 10 secs
    int j;
    for (j = 0; j<2; j++) {
        int k = 0;
        GPIOPinWrite(GPIO_PORTQ_BASE, GPIO_PIN_7, GPIO_PIN_7);
        int i;
        for (i=0; i<2400000; i++) {
            k++;
        }
        GPIOPinWrite(GPIO_PORTQ_BASE, GPIO_PIN_7, 0x0);
    }
}

void busyWaitBlue() {
    // flash green light for 10 secs
    int j;
    for (j =0; j<2; j++) {
        int k = 0;
        GPIOPinWrite(GPIO_PORTQ_BASE, GPIO_PIN_4, GPIO_PIN_4);
        int i;
        for (i=0; i<2400000; i++) {
            k++;
        }
        GPIOPinWrite(GPIO_PORTQ_BASE, GPIO_PIN_4, 0x0);
    }
}
