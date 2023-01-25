/*
 * timming2.c
 *
 *  Created on: Jan 25, 2023
 *      Author: Joself
 */

#include <timming2.h>


void init_metimer (void)
{
    //Start timer in continuous mode sourced by SMCLK
    Timer_A_initContinuousModeParam initContParam = {0};
    initContParam.clockSource = TIMER_A_CLOCKSOURCE_ACLK;
    initContParam.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;
    initContParam.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_DISABLE;
    initContParam.timerClear = TIMER_A_DO_CLEAR;
    initContParam.startTimer = false;
    Timer_A_initContinuousMode(TIMER_A0_BASE, &initContParam);

    //Initiaze compare mode
    Timer_A_clearCaptureCompareInterrupt(TIMER_A0_BASE,
        TIMER_A_CAPTURECOMPARE_REGISTER_0
        );

    Timer_A_initCaptureModeParam initCompParam = {0};
    initCompParam.captureRegister = TIMER_A_CAPTURECOMPARE_REGISTER_0;
    initCompParam.captureMode = TIMER_A_CAPTUREMODE_RISING_EDGE;
    initCompParam.captureInputSelect = TIMER_A_CAPTURE_INPUTSELECT_CCIxA;
    initCompParam.synchronizeCaptureSource = TIMER_A_CAPTURE_SYNCHRONOUS;
    initCompParam.captureInterruptEnable = TIMER_A_CAPTURECOMPARE_INTERRUPT_ENABLE;
    initCompParam.captureOutputMode = TIMER_A_OUTPUTMODE_OUTBITVALUE;
    Timer_A_initCaptureMode(TIMER_A0_BASE, &initCompParam);

    Timer_A_startCounter( TIMER_A0_BASE,
            TIMER_A_CONTINUOUS_MODE
                );
    //For debugger
    __no_operation();
}

//******************************************************************************
//
//This is the TIMER0_A0 interrupt vector service routine.
//
//******************************************************************************
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER0_A0_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(TIMER0_A0_VECTOR)))
#endif
void TIMER0_A0_ISR (void)
{

    }


