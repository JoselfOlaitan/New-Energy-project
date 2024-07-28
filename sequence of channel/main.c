
/*
 * main.c
 *
 *  Created on: Jul 22, 2022
 *      Author: CMsuchi
 */




#include "main.h"




void main(void)
{
    WDT_A_hold(WDT_A_BASE);
   My_clock();
    //Stop Watchdog Timer

    gpio();  // configure Gpio pins

    Init_ADC(); // configure the ADC

    init_mtimer(); //configure timer


    Timer_A_startCounter(TIMER_A1_BASE, TIMER_A_UP_MODE);

    __bis_SR_register(GIE);
    while (1)
    {
//        start_ADC(); // Start ADC conversion
        average_ADC_val();
        __no_operation();
//     __bis_SR_register(LPM3_bits);                     // Enter LPM3 w/ interrupts
                                               // Only for debugger
    }


}


