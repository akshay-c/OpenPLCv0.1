/* vim: set sw=8 ts=8 si et: */
#ifndef LED_H
#define LED_H
#include <avr/io.h>

/* enable PC0 as output */
#define LED_INIT DDRB|=_BV(PB1)
/* led on, pin=0 */
#define LED_ON PORTB|=_BV(PB1)
/* led off, pin=1 */
#define LED_OFF PORTB&=~_BV(PB1)

#endif //LED_H
