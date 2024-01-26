/*
 * UART.c
 *
 * Created: 9/1/2023 12:33:18 PM
 *  Author: N A E E M
 */
#include "UART.h" 

// async, 8bits, 1 stop, no parity, 9600 Baude rate
void UART_init(void){
	UBRRL = 103;   //Buad_rate=Fosc/16(UBBR+1)
	UCSRB = 1<<RXEN | 1<<TXEN ;
}
void UART_write(uint8_t data){
	UDR = data;
	while(READBIT(UCSRA, TXC) == 0);
	
}
uint8_t UART_read(void){
	while(READBIT(UCSRA, RXC) == 0); // wait till new data
	return UDR;
}
