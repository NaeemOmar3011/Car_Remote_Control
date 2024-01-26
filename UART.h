/*
 * UART.h
 *
 * Created: 9/1/2023 12:33:29 PM
 *  Author: N A E E M
 */ 


#ifndef UART_H_
#define UART_H_
#include "generic_macros_header.h"

void UART_init(void);
void UART_write(uint8_t data);
uint8_t UART_read(void);




#endif /* UART_H_ */