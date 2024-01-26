/*
 * Timer.c
 *
 * Created: 9/5/2023 1:46:49 PM
 *  Author: N A E E M
 */ 

#include "Timer.h"

void Timer0_Normal_noPre_init(void){
		TCCR0 = 1;
		SETBIT(TIMSK,TOIE0);
		SETBIT(SREG,7);
		
}
void Timer0_Normal_Pre_init(void){
	TCCR0 = 0b101; // 1024 prescalar
	SETBIT(TIMSK,TOIE0);
	SETBIT(SREG,7);
}

void Timer0_Compare_noPre_init(uint32_t count){
	TCCR0 = 1;
	SETBIT(TCCR0,WGM01); //enable CTC
	SETBIT(TIMSK,OCIE0); //enable Compare Match
	SETBIT(SREG,7); 
	OCR0=count;
}
void Timer0_Compare_Pre_init(uint16_t count){
	TCCR0 = 0b101; // 1024 prescalar
	SETBIT(TCCR0,WGM01); //enable PWM
	SETBIT(TIMSK,OCIE0); //enable Compare Match
	SETBIT(SREG,7);
	OCR0=count;
}
void Timer1_PWM_OC1A_init(void){
	SETBIT(DDRD,PD5);
	SETBIT(TCCR1A,COM1A1);
	CLRBIT(TCCR1A,COM1A0);
	SETBIT(TCCR1A,WGM10);
	SETBIT(TCCR1A,WGM11);
	SETBIT(TCCR1B,WGM12);
	SETBIT(TCCR1B,CS10);
}
void Timer1_PWM_OC1A_DC(uint8_t dc){
	OCR1A = dc  * 10.23;
}

void Timer0_PWM_OC0_init(void){
	SETBIT(DDRB,PB3);
	TCCR0 = 1; // no prescalar
	SETBIT(TCCR0,WGM01);
	SETBIT(TCCR0,WGM00); //enable PWM
	CLRBIT(TCCR0,COM00);
	SETBIT(TCCR0,COM01);
	//SETBIT(TIMSK,OCIE0); //enable Compare Match
	//SETBIT(SREG,7);
}

void Timer0_PWM_OCR0_DC(uint16_t count){
	count*=2.55;
	OCR0=count;
}

/*
void Timer1_Capture_init(void){
	CLRBIT(DDRD,PD6); // ICP1 input
	TCCR1A=0;
	TCNT1=0;
	SETBIT(TIFR,ICF1); //clear flag
	SETBIT(TIMSK,TICIE1); //enable Capture interrupt
	SETBIT(SREG,7);
}
*/

void Timer1_Capture_init(void) {
    CLRBIT(DDRD, PD6); // ICP1 input

    // Set the mode bits for Input Capture mode, trigger on rising edge
    TCCR1A = 0;
    TCCR1B = (1 << ICNC1) | (1 << ICES1); 

    TCNT1 = 0;
    SETBIT(TIFR, ICF1); // Clear the Input Capture flag
    SETBIT(TIMSK, TICIE1); // Enable Capture interrupt

    // You may want to set the prescaler here, e.g., for a prescaler of 8
    SETBIT(TCCR1B, CS11);

    // If you don't set the prescaler here, you should set it later in your code.
}

void PWM_Timer2_init() {
	// Set OC2 (output compare) pin as output
	DDRD |= (1 << PD7);

	// Configure Timer 2 for fast PWM mode with non-inverting output on OC2
	TCCR2 |= (1 << WGM20) | (1 << WGM21) | (1 << COM21) | (1 << CS20);

	// Set the initial duty cycle (0%)
	OCR2 = 0;
}

// Function to set the PWM duty cycle (0 to 255)
void PWM_Timer2_set_duty_cycle(uint8_t duty_cycle) {
	duty_cycle*=2.55;
	// Ensure the duty cycle is within the valid range (0 to 255)
	if (duty_cycle > 255) {
		duty_cycle = 255;
	}

	// Set the duty cycle by updating the value in OCR2 register
	OCR2 = duty_cycle;
}

