#include <avr/io.h>
#include "lcd.h"
#include "avr_compat.h"
#include "avr/cpufunc.h"
#define F_CPU 11059200UL
#include <util/delay.h>

void SetDir(void)
{
	sbi(RSDir , RSPin);
	sbi(RWDir , RWPin);
	sbi(ENDir , ENPin);
	if(LcdOrder)
	{
		LcdDir |= 0xF0;
	}
	else
	{
		LcdDir |=0x0F;
	}
}
void LcdInit()
{
	SetDir();
	_delay_ms((double)200);
	LcdCmd(0x02);
	_delay_ms((double)20);
	LcdCmd(0x28);
	_delay_ms((double)40);
	LcdCmd(0x0C);
	_delay_ms((double)20);
	LcdCmd(0x01);
	_delay_ms((double)20);
	LcdData('Y');
	_delay_ms((double)20);
}
void LcdCmd(unsigned char val)
{
	LcdReady();

	if(LcdOrder)
	{
		cbi(RSPort , RSPin);
		cbi(RWPort , RWPin);
		LcdPort &= ~(val & 0xF0);
		sbi(ENPort , ENPin);
		cbi(ENPort , ENPin);
		LcdPort &= ~((val & 0x0F) << 4);
		sbi(ENPort , ENPin);
		cbi(ENPort , ENPin);
	}
	else
	{
		cbi(RSPort , RSPin);
		cbi(RWPort , RWPin);
		LcdPort &= ~((val & 0xF0) >> 4);
		sbi(ENPort , ENPin);
		cbi(ENPort , ENPin);
		LcdPort &= ~(val & 0x0F);
		sbi(ENPort , ENPin);
		cbi(ENPort , ENPin);
	}
}
void LcdData(unsigned char val)
{
	LcdReady();
	if(LcdOrder)
	{
		sbi(RSPort , RSPin);
		cbi(RWPort , RWPin);
		LcdPort &= ~(val & 0xF0);
		sbi(ENPort , ENPin);
		cbi(ENPort , ENPin);
		LcdPort &= ~((val & 0x0F) << 4);
		sbi(ENPort , ENPin);
		cbi(ENPort , ENPin);
	}
	else
	{
		sbi(RSPort , RSPin);
		cbi(RWPort , RWPin);
		LcdPort &= ~((val & 0xF0) >>4);
		sbi(ENPort , ENPin);
		cbi(ENPort , ENPin);
		LcdPort &= ~(val & 0x0F);
		sbi(ENPort , ENPin);
		cbi(ENPort , ENPin);
	}
}
void LcdReady()
{
	//Pd1=1; pd2=2;pd3=3; pd0=0; pd4=4;.....
	int stat;
	cbi(LcdPort , LcdBusy);
	cbi(RSPort , RSPin);
	sbi(RWPort , RWPin);
		do
		{
			sbi(ENPort , ENPin);
			stat = LcdPort & (1 << LcdBusy );
			cbi(ENPort , ENPin);
			sbi(ENPort , ENPin);
			_NOP();
			cbi(ENPort , ENPin);
		}while(stat);
	sbi(LcdPort , LcdBusy);
	
}