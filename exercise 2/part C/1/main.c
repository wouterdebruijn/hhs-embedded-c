/*
 * Opdracht 1.c
 *
 * Created: 17/02/2021 09:38:36
 * Author : Wouter
 *
 * Opdracht is goed verlopen. Het was even zoeken naar het juiste register, maar ik heb deze uiteindelijk kunnen vinden in het datasheet. 
 *
 * Verklaring monitor output. Wanneer de monitor op 7 bits, even pariteit is ingesteld wordt de data successful ontvangen, wanneer de monitor is ingesteld op 8 bit, geen pariteit wordt niet alle data altijd ontvangen. De data wordt corrupt omdat de lezer anders leest dan de schrijver geschreven heeft.
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>


int main(void) {
	UCSR0A = 0;
	UCSR0B = (1 << TXEN0); // Enable de USART Transmitter
	UCSR0C = (1 << UCSZ01) | (1<<UPM01); // 7 Bit (UCSZn) Enabled, Even Parity (UPMn)
	
	UBRR0H=00;
	UBRR0L=103; //baudrade 9600 bij
	
	while (1) {
		for(char c='0'; c<='9';c++) {
			while(~UCSR0A & (1 << UDRE0)); // Wait for empty transmit buffer
			UDR0 = c;
			for(uint8_t i=0;i<4;++i)
			_delay_ms(250);
		}
	}
	return (0);
}