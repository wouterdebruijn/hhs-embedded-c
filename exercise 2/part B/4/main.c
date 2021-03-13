/*
 * Opdracht 4.c
 *
 * Created: 17/02/2021 09:22:52
 * Author : Wouter
 *
 * Opdracht uitgevoerd zonder problemen, ben er niet zeker over of de output die ik via serial binnen heb gekregen correct is. Leesbaar was het namelijk niet. 
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

void writeChar(char x);
void writeString(char st[]);
void writeInt(int i);

int main(void) {

	UCSR0A = 0;
	UCSR0B = (1 << TXEN0); // Enable de USART Transmitter
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); /* 8 data bits, 1 stop bit */
	UBRR0H=00;
	UBRR0L=103; //baudrade 9600 bij

	while(1) {
		for (int i=0; i <= 101; i++) {
			writeInt(i);
		}
	}
	return 0;
}

void writeInt(int i) {
	char buffer[8];
	itoa(i,buffer,10);
	writeString(buffer);
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