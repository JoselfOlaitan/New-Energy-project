/*
 * adc2.c
 *
 *  Created on: Jan 25, 2023
 *      Author: Joself
 */
#include "adc2.h"
#include "timming.h"
int i;
uint8_t t;
uint8_t m;
float dev,V_rms;
uint32_t squ;
uint32_t  RMS_value;
uint32_t voltage_array[20];
uint16_t ADC_Result[2];
int j = 0;



void Init_ADC(void)
{


    //Initialize the ADC Module
           /*
            * Base Address for the ADC Module
            * Use internal ADC bit as sample/hold signal to start conversion
            * USE MODOSC 5MHZ Digital Oscillator as clock source
            * Use default clock divider of 1
            */
           ADC_init(ADC_BASE,
               ADC_SAMPLEHOLDSOURCE_2,
               ADC_CLOCKSOURCE_ADCOSC,
               ADC_CLOCKDIVIDER_1);

           ADC_enable(ADC_BASE);

           /*
            * Base Address for the ADC Module
            * Sample/hold for 16 clock cycles
             * Do not enable Multiple Sampling
             */
           ADC_setupSamplingTimer(ADC_BASE,
                      ADC_CYCLEHOLD_16_CYCLES,
                      ADC_MULTIPLESAMPLESDISABLE);

            //Change the resolution to 10-bit
           ADC_setResolution(ADC_BASE,
                ADC_RESOLUTION_8BIT);

            //Configure Memory Buffer
            /*
             * Base Address for the ADC Module
             * Use input A0-A1
             * Use positive reference of AVcc
             * Use negative reference of AVss
             */
           ADC_configureMemory(ADC_BASE,
                    ADC_INPUT_A1,
                    ADC_VREFPOS_AVCC,
                    ADC_VREFNEG_AVSS);


           ADC_clearInterrupt(ADC_BASE,
                    ADC_COMPLETED_INTERRUPT);

            //Enable Memory Buffer interrupt
           ADC_enableInterrupt(ADC_BASE,
                    ADC_COMPLETED_INTERRUPT);

i =1;

}

void start_ADC(void)
{

     //Enable and Start the conversion
                           //in Sequence of Channels Conversion Mode
    ADC_startConversion(ADC_BASE, ADC_SEQOFCHANNELS);


}

#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void)
{
    switch(__even_in_range(ADCIV,ADCIV_ADCIFG))
    {
        case ADCIV_NONE:
            break;
        case ADCIV_ADCOVIFG:
            break;
        case ADCIV_ADCTOVIFG:
            break;
        case ADCIV_ADCHIIFG:
            break;
        case ADCIV_ADCLOIFG:
            break;
        case ADCIV_ADCINIFG:
            break;
        case ADCIV_ADCIFG:
//            i--;
            ADC_Result[i] = ADCMEM0;
            if(i == 0)
            {
               // __no_operation();                               // Only for debugger
                val.voltage_buffer +=ADC_Result[i];
                voltage_array[m]    =ADC_Result[i];
                m++;
                i = 1;
                //ADC_startConversion(ADC_BASE, ADC_SEQOFCHANNELS);
            }
            else
            {
               val.current_buffer += ADC_Result[i];
               val.adc_counter++;
               i--;
            }
            //average_ADC_val();
            break;
        default:
            break;
    }
}
void average_ADC_val(void)
{
if (val.adc_counter ==20)
    {
    val.voltage_average = (val.voltage_buffer/20);
    for (  t = 0; t < 20; t++ )
       {
           dev = abs( voltage_array[t]- val.voltage_average);

           squ += ((uint32_t) dev * dev);

       }
       squ = squ/20;
       V_rms = sqrt(squ);
       RMS_value = V_rms;

       val.voltage = (RMS_value * 0.0032* 200.07); // the
       val.current = (val.current_buffer/ 20) * (0.0032 * 10);
       val.current_buffer = 0;
       val.voltage_buffer = 0;
       val.adc_counter = 0;
       voltage_array[m] =0;
       m=0;
    }
}
void power_val (void)
{
    val.power_cal = val.current * val.voltage ;
}

