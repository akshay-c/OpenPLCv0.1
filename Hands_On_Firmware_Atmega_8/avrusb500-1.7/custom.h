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
#define ADC0 PC0
#define ADC1 PC1
#define ADC2 PC2
#define ADC3 PC3
#define ADC4 PC4
#define ADC5 PC5

#endif
