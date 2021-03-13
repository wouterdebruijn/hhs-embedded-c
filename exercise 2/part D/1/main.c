/*
 * Opdracht 1.c
 *
 * Created: 17/02/2021 10:15:09
 * Author : Wouter
 */ 

#define F_CPU 16000000
#include <avr/io.h>

void initUsart();

void writeChar(char x);
void writeString(char st[]);
char readChar();
void setLedD0_D3(char c);

int main(void)
{
	DDRB = 0xFF; // Whole bus is output (My leds are on the B bus)
	
	char x;
	initUsart();
	
    while (1) 
    {
		writeString("Zet een HEX waarde op de pinnen B0...B3\n\r");
		x=readChar();
		setLedD0_D3(x);
    }
}

void initUsart(void) {
	UCSR0A = 0;
	UCSR0B = (1<<RXEN0)|(1<<TXEN0); // Enable receiver and transmitter
	UCSR0C = (1 << UCSZ01) | (1<<UCSZ00); // 8 Bit (UCSZn) Enabled, No Parity (UPMn)
	
	UBRR0H=00;
	UBRR0L=103; //baudrade 9600 bij
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

char readChar() {
	/* Wait for data to be received */
	 while ( !(UCSR0A & (1<<RXC0)) );
	 /* Get and return received data from buffer */
	 return UDR0;}void setLedD0_D3(char c) {	int v = 0;		// Convert ASCI to int	if (c >= 'a' && c <= 'f') {		v = c - 87;	}		if (c >= '0' && c <= '9') {		v = c - 48;	}		PORTB = v & 0b00001111;}