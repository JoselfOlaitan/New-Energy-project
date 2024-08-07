/*
 * timing.c
 *
 *  Created on: Sep 25, 2022
 *      Author: PREMAUDA
 */
#include "timing.h"
#include "gpio.h"
#include "adc2.h"

#define TIMER_PERIOD  33
#define DUTY_CYCLE    3
static uint32_t sub_counter = 0;
uint8_t k = 0;


void init_mtimer (void)
{


      //Start timer
    Timer_A_initUpModeParam param = {0};
    param.clockSource = TIMER_A_CLOCKSOURCE_ACLK;
    param.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;
    param.timerPeriod = TIMER_PERIOD;
    param.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_DISABLE;
    param.captureCompareInterruptEnable_CCR0_CCIE = TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE;
    param.timerClear = TIMER_A_DO_CLEAR;
    param.startTimer = false;
    Timer_A_initUpMode(TIMER_A1_BASE, &param);



    Timer_A_clearCaptureCompareInterrupt(TIMER_A1_BASE,
            TIMER_A_CAPTURECOMPARE_REGISTER_0 +
            TIMER_A_CAPTURECOMPARE_REGISTER_1
            );

    //Initialize compare mode to generate PWM1
    Timer_A_initCompareModeParam initComp1Param = {0};
    initComp1Param.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_1;
    initComp1Param.compareInterruptEnable = TIMER_A_CAPTURECOMPARE_INTERRUPT_ENABLE;
    initComp1Param.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;
    initComp1Param.compareValue = DUTY_CYCLE;
    Timer_A_initCompareMode(TIMER_A1_BASE, &initComp1Param);



//    TIMER_A_startCounter( TIMER_A1_BASE,TIMER_A_UP_MODE );


}

//******************************************************************************
//
//This is the TIMER1_A0 interrupt vector service routine.
//
//******************************************************************************
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER1_A0_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(TIMER1_A0_VECTOR)))
#endif
__interrupt void TIMER1_A0_ISR (void)
{

    sub_counter++;
       if (sub_counter == 100)
          {
              sub_counter = 0;
              //Toggle LED1
                    GPIO_toggleOutputOnPin(
                        GPIO_PORT_P4,
                        GPIO_PIN0);
//                    __bic_SR_register(LPM3_bits);  //exit LPM3

          }

//    ADC_startConversion(ADC_BASE, ADC_SEQOFCHANNELS);



}
#pragma vector=TIMER1_A1_VECTOR
//__interrupt
//#elif defined(__GNUC__)
//__attribute__((interrupt(TIMER1_A1_VECTOR)))
//#endif
__interrupt void TIMER1_A1_ISR (void)
{
    switch ( __even_in_range(TA1IV,14) )
    {
           case  0X00: break;                          //No interrupt
           case  0X02:
               //start_ADC(); // Start ADC conversion
                ADC_startConversion(ADC_BASE, ADC_SEQOFCHANNELS);
              //Toggle LED2
                k++;
                GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN7);
                break;
           case  0X04: break;                          //CCR2 not used
           case  0X06: break;                          //CCR3 not used
           case 0X08: break;                          //CCR4 not used
           case 0X0A: break;                          //CCR5 not used
           case 0X0C: break;                          //CCR6 not used
           case 0X0E: break;
           default:  _never_executed();
    }
}



