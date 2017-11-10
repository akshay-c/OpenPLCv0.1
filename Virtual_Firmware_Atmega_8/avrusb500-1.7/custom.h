/*************************************************************************
 Title:   C include file for "custom"
 Target:    atmega8
 Copyright: GPL
***************************************************************************/
#ifndef CUSTOM_H
#define CUSTOM_H

#define MID 1

//Function Definitions
void initButtons(void);
char readCommand(unsigned char);

//BIT Definitions
#define Btn1 PC5
#define Btn2 PC4
#define Btn3 PC3
#define Btn4 PC2
#define Btn5 PC1
#define Btn6 PB1
#define Btn7 PB0
#define AdcPin PC0

#endif
