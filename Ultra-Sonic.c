/*
 * Ultra_Sonic.c
 *
 * Created: 12/29/2023 9:57:08 PM
 *  Author: N A E E M
 */ 

#include "Ultra-Sonic.h"
static uint16_t distance=0;
static uint32_t time = 0;
static volatile uint16_t OV=0;
static volatile uint16_t t1 = 0, t2 = 0, OVF = 0 ;
static volatile uint8_t flag = 0;

/*****************************************************************************
* Function Name: Ultra_Sonic_init
* Purpose      : initialize ultra sonic
* Parameters   : void
* Return value : void
*****************************************************************************/
void Ultra_Sonic_init(void){
	Ultra_Sonic_set_trigger;
	
/////////////////////////*****************Enabling input capture interrupt********//////////////////////////////

	CLRBIT(DDRD, PD6); // ICP1 input

	// Set the mode bits for Input Capture mode, trigger on rising edge
	TCCR1A = 0;
	TCCR1B=0;
	TCCR1B |= (1 << ICNC1) | (1 << ICES1);
	SETBIT(TIFR, ICF1); // Clear the Input Capture flag
	SETBIT(TIFR, TOV1); // Clear the Overflow flag
	SETBIT(TIMSK, TICIE1); // Enable Capture interrupt
	SETBIT(TIMSK, TOIE1); //  Enable Overflow interrupt
	sei();
	TCNT1 = 0;
	
	// You may want to set the prescaler here, e.g., for a prescaler of 8
	SETBIT(TCCR1B, CS11);


}

/*****************************************************************************
* Function Name: Ultra_Sonic_get_distance
* Purpose      : Measure the distance
* Parameters   : void
* Return value : uint16_t
*****************************************************************************/	
uint16_t Ultra_Sonic_get_distance(void){
	flag=0;
	TCNT1=0;
	Ultra_Sonic_trigger_on;
	_delay_us(10);
	Ultra_Sonic_trigger_off;
	
	Enable_Capture_interrupt;
	Enable_Overflow_interrupt;
	while(flag!=2);
	// Calculate the time difference in microseconds
	time = ((uint32_t)t2 - (uint32_t)t1) + (uint32_t)(OVF * 65536);

	// Adjusting for the prescaler of 8 and 16 MHz crystal
	time *= 8; // prescaler
	time /= 16; // clock frequency

	// Speed of sound assumed to be 343 m/s, and considering two-way travel
	distance = (double)(time/ 58 ); // (343 m/s) * (time in seconds) / 2
	return distance;
}

ISR(TIMER1_OVF_vect)
{
	OV++;
}
ISR(TIMER1_CAPT_vect)
{
	if (flag == 0)
	{
		t1 = ICR1;
		OV=0;
		next_falling_edge;
		flag = 1;
	}
	else if (flag == 1)
	{
		t2 = ICR1;
		OVF=OV;
		next_rising_edge;
		flag = 2;
		Disable_Capture_interrupt;
		Disable_Overflow_interrupt;
	}
}