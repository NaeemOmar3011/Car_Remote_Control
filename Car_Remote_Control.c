/*
 * Car_Bluetooth_Control.c
 *
 * Created: 1/10/2024 1:46:51 PM
 * Author : N A E E M
 */ 

#include "LCD.h"
#include "UART.h"
#include "Car_Move.h"
#include "Ultra-Sonic.h"

/*******************Macros for data from bluetooth************************/
#define Front 'F'
#define Back 'B'
#define Right 'R'
#define Left 'L'
#define Left_Front 'G'
#define Right_Front 'I'
#define Left_Back 'H'
#define Right_Back 'J'
#define Stop 'S'

/*********************Macros for some peripherals*************************/
/////Light/////
#define Set_Light SETBIT(DDRD,PD3)	
#define Open_Light SETBIT(PORTD,PD3)
#define Close_Light CLRBIT(PORTD,PD3)
/////Buzzer/////
#define Set_Buzzer SETBIT(DDRC,PC0)	
#define Open_Buzzer SETBIT(PORTC,PC0)
#define Close_Buzzer CLRBIT(PORTC,PC0)


/****************************Global variables*****************************/
const uint8_t Min_Distance=20; 

/****************************Functions Prototype*****************************/
void Move_Direction(uint8_t data);


/****************************Main Function*****************************/
int main(void)
{
	//***Set_Peripherals***//
	Set_Light;
	Set_Buzzer;
	
	//***Functions_Initialization***//
	UART_init();
	Car_init();
	Ultra_Sonic_init();
	
	uint16_t dist=0,data=0;

    while (1) 
    {
		dist=Ultra_Sonic_get_distance(); //Measure the distance

		data=UART_read(); //Get data from bluetooth	
			
		Move_Direction(data); //Move the car
		
		
		//****Distance is too small to move****//
		while(dist < Min_Distance)
		{
			Move_Stop();
			
			Open_Buzzer;
			Open_Light;
			
			dist=Ultra_Sonic_get_distance(); //Measure the distance

			data=UART_read(); //Get data from bluetooth
				
			while((data != Front) && (data != Right_Front) && (data != Left_Front) && (data != Stop)) 
			{	
				data=UART_read(); //Get data from bluetooth
				
				Move_Direction(data);//Move the car	
			}
			
		}
		Close_Buzzer;
		Close_Light;
		_delay_ms(100);
		
		
    }
}


/*****************************************************************************
* Function Name: Move_Direction
* Purpose      : Moves the car in a certain direction
* Parameters   : uint8_t
* Return value : void
*****************************************************************************/
void Move_Direction(uint8_t data){
	switch(data) {
		case Front:
		Move_Forward();
		break;

		case Back:
		Move_Back();
		break;

		case Right:
		Move_Right();
		break;

		case Left:
		Move_Left();
		break;

		case Left_Front:
		Move_Left_Front();
		break;

		case Right_Front:
		Move_Right_Front();
		break;

		case Left_Back:
		Move_Left_Back();
		break;

		case Right_Back:
		Move_Right_Back();
		break;

		case Stop:
		Move_Stop();
		break;

	}

}

