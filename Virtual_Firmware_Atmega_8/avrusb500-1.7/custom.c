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
    //Button pins are output pins
    sbi(DDRC,Btn1);
    sbi(DDRC,Btn2);
    sbi(DDRC,Btn3);
    sbi(DDRC,Btn4);
    sbi(DDRC,Btn5);
    sbi(DDRB,Btn6);
    sbi(DDRB,Btn7);

    //Buttons are high by default on reset
    sbi(PORTC,Btn1);
    sbi(PORTC,Btn2);
    sbi(PORTC,Btn3);
    sbi(PORTC,Btn4);
    sbi(PORTC,Btn5);
    sbi(PORTB,Btn6);
    sbi(PORTB,Btn7);

    //Adc Configuration
    ADMUX = AdcPin;
    ADCSRA = ADCSRA | 1<<ADEN;
}
char readCommand(unsigned char Command)
{
    unsigned int OpCode;
    unsigned int BtnNum;
    char Value;
    unsigned char temp;
    temp=Command;
    OpCode=temp>>5;
    temp=Command;
    if(OpCode==1)
    {
        BtnNum = (temp & 0x1C)>>2;
        temp = Command;
        Value = temp & 0x01;
        temp = Command & 0xFE;
        switch(BtnNum)
        {
            case 1:
                if(Value==0x01)
                    sbi(PORTC,Btn1);
                else
                    cbi(PORTC,Btn1);
                return (temp | ((PORTC & (1<<Btn1))>>Btn1));
                break;
            case 2:
                if(Value==0x01)
                    sbi(PORTC,Btn2);
                else
                    cbi(PORTC,Btn2);
                return (temp | ((PORTC & (1<<Btn2))>>Btn2));
                break;
            case 3:
                if(Value==0x01)
                    sbi(PORTC,Btn3);
                else
                    cbi(PORTC,Btn3);
                return (temp | ((PORTC & (1<<Btn3))>>Btn3));
                break;
            case 4:
                if(Value==0x01)
                    sbi(PORTC,Btn4);
                else
                    cbi(PORTC,Btn4);
                return (temp | ((PORTC & (1<<Btn4))>>Btn4));
                break;
            case 5:
                if(Value==0x01)
                    sbi(PORTC,Btn5);
                else
                    cbi(PORTC,Btn5);
                return (temp | ((PORTC & (1<<Btn5))>>Btn5));
                break;
            case 6:
                if(Value==0x01)
                    sbi(PORTB,Btn6);
                else
                    cbi(PORTB,Btn6);
                return (temp | ((PORTB & (1<<Btn6))>>Btn6));
                break;
            case 7:
                if(Value==0x01)
                    sbi(PORTB,Btn7);
                else
                    cbi(PORTB,Btn7);
                return (temp | ((PORTB & (1<<Btn7))>>Btn7));
                break;
            default:
                return 88;
                break;
        }
    }
    else if(OpCode==2)
    {
        BtnNum = (temp & 0x1C)>>2;
        temp = Command & 0xFE;
        switch(BtnNum)
        {
            case 1:
                return (temp | ((PORTC & (1<<Btn1))>>Btn1));
                break;
            case 2:
                return (temp | ((PORTC & (1<<Btn2))>>Btn2));
                break;
            case 3:
                return (temp | ((PORTC & (1<<Btn3))>>Btn3));
                break;
            case 4:
                return (temp | ((PORTC & (1<<Btn4))>>Btn4));
                break;
            case 5:
                return (temp | ((PORTC & (1<<Btn5))>>Btn5));
                break;
            case 6:
                return (temp | ((PORTB & (1<<Btn6))>>Btn6));
                break;
            case 7:
                return (temp | ((PORTB & (1<<Btn7))>>Btn7));
                break;
            default:
                return 88;
                break;
        }
    }
    else if (OpCode == 3)
    {
        sbi(ADCSRA,ADSC);
        while(!(ADCSRA & (1<<ADIF)));
        sbi(ADCSRA,ADIF);
        uart_sendchar(ADCL);
        uart_sendchar(ADCH);
        return Command;
    }
    else if (OpCode == 4)
    {
        uart_sendchar(MID);
        return Command;
    }
    else{   return 88; }
}
