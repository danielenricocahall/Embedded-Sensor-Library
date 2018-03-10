#include <msp430.h>

#include "tempSensor.h"
/*
 * tempSensor.c
 *
 *  Created on: Dec 21, 2015
 *      Author: Danny
 */

//function to initialize ADC
void tempInit()
{
    ADC10CTL0=SREF_1 + REFON + ADC10ON + ADC10SHT_3 ; //1.5V ref,Ref on,64 clocks for sample
    ADC10CTL1=INCH_10+ ADC10DIV_3; //temp sensor is at 10 and clock/4
}
//*********************************************************************************************
//compute and output approximate temperature
//Note: Account for 15-20% error due to noise and internal temperature fluctuations
//within the chip
int tempOut()
{
    int t=0;
    __delay_cycles(1000);              //wait for reference to settle
    ADC10CTL0 |= ENC + ADC10SC;      //enable conversion and start conversion
    while(ADC10CTL1 & BUSY);         //convert
    t=ADC10MEM;                       //store val in t
    ADC10CTL0&=~ENC;                     //disable adc conv
    return (int)((t * 27069L - 18169625L) >> 16); //convert and return temperature
}




