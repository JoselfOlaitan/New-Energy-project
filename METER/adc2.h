/*
 * adc2.h
 *
 *  Created on: Jan 25, 2023
 *      Author: Joself
 */

#ifndef ADC2_H_
#define ADC2_H_

#include "driverlib.h"
#include <msp430.h>
#include "math.h"

void Init_ADC(void);
void start_ADC(void);
void average_ADC_val(void);
void power_val(void);

typedef struct
{
    uint32_t adc_counter;
    uint32_t current_buffer,voltage_buffer;
    float  current,voltage;
    uint32_t  voltage_average;
    uint32_t power_cal;
    uint8_t adc_flag;
}
struct_adc;

struct_adc val;




#endif /* ADC2_H_ */
