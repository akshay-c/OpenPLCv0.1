/****************************************************************************
* Title   :   Custom port operations and adc read via specific commands
* Authors:    Akshay Chipkar
* Copyright: GPL
*
*        
*****************************************************************************/
#include <avr/io.h>
#include "avr_compat.h"
#include "custom.h"
#include "uart.h"

void initButtons()
{
    //Adc pins are input pins
    cbi(DDRC,ADC0);
    cbi(DDRC,ADC1);
    cbi(DDRC,ADC2);
    cbi(DDRC,ADC3);
    cbi(DDRC,ADC4);
    cbi(DDRC,ADC5);

    //Adc are low(tristate) by default on reset
    cbi(PORTC,ADC0);
    cbi(PORTC,ADC1);
    cbi(PORTC,ADC2);
    cbi(PORTC,ADC3);
    cbi(PORTC,ADC4);
    cbi(PORTB,ADC5);

    //Adc Configuration
    ADCSRA = ADCSRA | 1<<ADEN;
}
char readCommand(unsigned char Command)
{
    unsigned int OpCode;
    unsigned int AdcNum;
    char Value;
    unsigned char temp;
    temp=Command;
    OpCode=temp>>5;
    temp=Command;
    if(OpCode==1)
    {
        AdcNum = (temp & 0x1C)>>2;
        temp = Command;
        Value = temp & 0x01;
        temp = Command & 0xFE;
        if (AdcNum <= 5 || AdcNum >=0)
        {
            ADMUX = ADMUX & 0xF0;
            ADMUX = ADMUX | AdcNum;
            sbi(ADCSRA,ADSC);
            while(!(ADCSRA & (1<<ADIF)));
            sbi(ADCSRA,ADIF);
            uart_sendchar(ADCL);
            uart_sendchar(ADCH);
            return Command;
        }
        else
        {
                return 88;
        }
    }
    else{   return 88; }
}
