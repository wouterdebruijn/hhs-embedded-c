/*
 * Opdracht 3.c
 *
 * Created: 17/02/2021 09:20:14
 * Author : Wouter
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

void writeChar(char x);
void writeString(char st[]);

int main(void) {

	UCSR0A = 0;
	UCSR0B = (1 << TXEN0); // Enable de USART Transmitter
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); /* 8 data bits, 1 stop bit */
	UBRR0H=00;
	UBRR0L=103; //baudrade 9600 bij

	while(1) {
		writeString("1234");
		for(uint8_t i=0;i<4;++i)
		_delay_ms(250);
	}
	return 0;
}


void writeString(char st[]) {
	for(uint8_t i = 0 ; st[i] != 0 ; i++) {
		writeChar( st[i] );
	}
}

void writeChar(char x) {
	while(~UCSR0A & (1 << UDRE0));
	UDR0 = x;
}