/*
 * Car_Move_cfg.h
 *
 * Created: 12/31/2023 11:05:33 PM
 *  Author: N A E E M
 */ 


#ifndef CAR_MOVE_CFG_H_
#define CAR_MOVE_CFG_H_

#define Car_cfg() DDRA |=0x0F; PORTA &=0xF0;

#define tire_one_is_front() READBIT(PORTA,PA0)
#define tire_one_is_back()  READBIT(PORTA,PA1)
#define tire_two_is_front() READBIT(PORTA,PA2)
#define tire_two_is_back()  READBIT(PORTA,PA3)

#define tire_one_front() SETBIT(PORTA,PA0); CLRBIT(PORTA,PA1);  
#define tire_one_back()  SETBIT(PORTA,PA1); CLRBIT(PORTA,PA0); 
#define tire_two_front() SETBIT(PORTA,PA2); CLRBIT(PORTA,PA3); 
#define tire_two_back()  SETBIT(PORTA,PA3); CLRBIT(PORTA,PA2); 
#define tire_stop() PORTA &=0xF0


#endif /* CAR_MOVE_CFG_H_ */