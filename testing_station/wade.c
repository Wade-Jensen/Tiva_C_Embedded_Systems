/*
 * wade.c
 *
 *  Created on: 24Apr.,2017
 *      Author: WadeJensen
 */

/*
 *  ======== main.c ========
 */

//#include <xdc/std.h>

#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>

#include <stdint.h>
#include <stdbool.h>

#include <ti/sysbios/knl/Task.h>

#include "drivers/pinout.h"
#include "driverlib/gpio.h"
#include "inc/tm4c1297nczad.h"
#include "inc/hw_memmap.h"

#include "driverlib/sysctl.h"

#include "common/common.h"
#include "control/control.h"

/*
 *  ======== taskFxn ========
 */
Void taskFxn(UArg a0, UArg a1)
{
    System_printf("enter taskFxn()\n");

    Task_sleep(10);

    System_printf("exit taskFxn()\n");
}

/*
 *  ======== main ========
 */
Int main()
{
    /*
     * use ROV->SysMin to view the characters in the circular buffer
     */
    System_printf("enter main()\n");

    PinoutSet();

    //SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION); // Redundant due to PinoutSet()
    setupControlOutputs();
    busyWaitRed();

    // raise cylinder
    raisePlatform();
    // Green light
    busyWaitGreen();
    // stop raising
    stopRaisePlatform();

    // Blue light
    busyWaitBlue();

    // air slider on
    airBedOn();
    // eject
    extendEjector();
    busyWaitRed();
    // stop ejecting
    retractEjector();
    // air slider off
    airBedOff();
    busyWaitGreen();

    // lower cylinder
    lowerPlatform();
    busyWaitBlue();
    // stop lowering
    stopLowerPlatform();

    //BIOS_start();    /* does not return */
    return(0);
}



