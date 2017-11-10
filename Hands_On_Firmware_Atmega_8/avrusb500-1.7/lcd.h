#ifndef LCD_H
#define LCD_H

/*Set Port, Direction and D7 Port for adc*/

#define LcdPort PORTD
#define LcdDir DDRD

#define LcdOrder 1			//Whether higher or lower order bits are used 1= high; 0= low

/*Set RS,RW Pin and Port numbers for adc*/
#define RSPin PB0
#define RWPin PD3
#define ENPin PD2

#define RSDir DDRB
#define RWDir DDRD
#define ENDir DDRD

#define RSPort PORTB
#define RWPort PORTD
#define ENPort PORTD

#define LcdBusy PD7

//Function Definition
void LcdInit(void);

//Lcd Communication functions:
void LcdCmd(unsigned char);
void LcdData(unsigned char);
void LcdReady(void);

#endif