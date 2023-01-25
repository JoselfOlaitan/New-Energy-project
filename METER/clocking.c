/*
 * clocking.c
 *
 *  Created on: Jan 25, 2023
 *      Author: Joself
 */

#include "clock2.h"

//Target frequency for MCLK in kHz
#define MCLK_DESIRED_FREQUENCY_IN_KHZ   8000


//MCLK/FLLRef Ratio

#define MCLK_FLLREF_RATIO   246

uint32_t myACLK = 0;
uint32_t myMCLK= 0;
uint32_t mySMCLK = 0;



void My_clock(void){

 //   PMM_setVcore(PMM_CORE_LEVEL_1);

    myACLK = CS_getACLK();
    mySMCLK = CS_getSMCLK();
    myMCLK = CS_getMCLK();



    // Set ACLK = REFO
    CS_initClockSignal(
    CS_ACLK,
    CS_REFOCLK_SELECT,
    CS_CLOCK_DIVIDER_1
    );


    CS_initClockSignal(
            CS_FLLREF,
            CS_REFOCLK_SELECT,
            CS_CLOCK_DIVIDER_1);

    // Set Ratio and Desired MCLK Frequency and initialize DCO
    CS_initFLLSettle(
    MCLK_DESIRED_FREQUENCY_IN_KHZ,
    MCLK_FLLREF_RATIO
    );

    myACLK = CS_getACLK();
      mySMCLK = CS_getSMCLK();
       myMCLK = CS_getMCLK();



}




