/*
 * gpio.c
 *
 *  Created on: Jul 22, 2022
 *      Author: CMsuchi
 */

#include "gpio.h"

void gpio(void)
{
    //gpio config for ADC input
     GPIO_setAsPeripheralModuleFunctionInputPin(
               GPIO_PORT_P1,
               GPIO_PIN1,
               GPIO_SECONDARY_MODULE_FUNCTION);

       GPIO_setAsPeripheralModuleFunctionInputPin(
               GPIO_PORT_P1,
               GPIO_PIN0,
               GPIO_SECONDARY_MODULE_FUNCTION);


       //Set LED2 as an output pin to debug the interrupt wake up
          GPIO_setAsOutputPin(
              GPIO_PORT_P4,
              GPIO_PIN0
              );
          GPIO_setAsOutputPin(
                        GPIO_PORT_P2,
                        GPIO_PIN7
                        );

       /*
            * Disable the GPIO power-on default high-impedance mode to activate
            * previously configured port settings
            */
       PMM_unlockLPM5();
}
