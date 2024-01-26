/*
 * Ultra_Sonic.h
 *
 * Created: 12/29/2023 9:57:24 PM
 *  Author: N A E E M
 */ 


#ifndef ULTRA_SONIC_H_
#define ULTRA_SONIC_H_
#include "generic_macros_header.h"


#define next_falling_edge TCCR1B &= ~(1 << ICES1)
#define next_rising_edge TCCR1B |= (1 << ICES1)
#define Disable_Capture_interrupt CLRBIT(TIMSK, TICIE1)
#define Disable_Overflow_interrupt CLRBIT(TIMSK, TOIE1)
#define Enable_Capture_interrupt SETBIT(TIMSK, TICIE1)
#define Enable_Overflow_interrupt SETBIT(TIMSK, TOIE1)

#define Ultra_Sonic_set_trigger SETBIT(DDRD,PD2)
#define Ultra_Sonic_trigger_on SETBIT(PORTD,PD2)
#define Ultra_Sonic_trigger_off CLRBIT(PORTD,PD2)

void Ultra_Sonic_init(void);
uint16_t Ultra_Sonic_get_distance(void);


#endif /* ULTRA-SONIC_H_ */