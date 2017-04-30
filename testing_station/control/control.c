/*
 * control.c
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

void setupControlOutputs() {
    // Raise cylinder output
    GPIOPinTypeGPIOOutput(GPIO_PORTL_BASE, GPIO_PIN_0);
    // Lower cylinder output
    GPIOPinTypeGPIOOutput(GPIO_PORTL_BASE, GPIO_PIN_1);
    // Eject cylinder extend output
    GPIOPinTypeGPIOOutput(GPIO_PORTL_BASE, GPIO_PIN_2);
    // Air slider on output
    GPIOPinTypeGPIOOutput(GPIO_PORTL_BASE, GPIO_PIN_3);
    // Lifting cylinder raised sensor input
    GPIOPinTypeGPIOInput(GPIO_PORTN_BASE, GPIO_PIN_4);
}

void extendEjector() {
    GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_2, GPIO_PIN_2);
}

void retractEjector() {
    GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_2, 0x0);
}

void raisePlatform() {
    GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_0, GPIO_PIN_0);
}

void stopRaisePlatform() {
    GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_0, 0x0);
}

void lowerPlatform() {
    GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_1, GPIO_PIN_1);
}

void stopLowerPlatform() {
    GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_1, 0x0);
}

void airBedOn() {
    GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_3, GPIO_PIN_3);
}

void airBedOff() {
    GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_3, 0x0);
}


