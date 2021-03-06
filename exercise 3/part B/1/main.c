#define F_CPU 16000000 // Needs to be before include Delay!

#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

void hzBlink();
void initUsart();

void writeString(char st[]);
void writeChar(char x);

// volatile is needed, otherwise the var gets snapped by Thanos and the main loop will never notice a change.
volatile int teller = 15;

// Serial received interrupt
ISR(USART_RX_vect) {
	while (!(UCSR0A & (1 << RXC0)))
		;

	char send = UDR0; // (You need to do something with the buffer in your interupt, otherwise it failed.

	int inputAsNum = 0;

	if (send >= '0' && send <= '9')
		inputAsNum = send - '0';

	if (send >= 'a' && send <= 'f')
		inputAsNum = send - 87;

	teller = inputAsNum;

	writeString("Changing...\n\r");
}

void initExtInt() {
	EIMSK = (1 << INT0);  // Setup interrupt
	EICRA = (1 << ISC01); // Setup falling edge
}

int main(void) {
	DDRB = 0xFF;

	initUsart();
	sei(); // Enable global interrupts

	while (1) {
		if (teller > 0) {
			hzBlink();
		} else {
			PORTB = 0x00;
		}
	}

}

void initUsart() {
	UCSR0A = 0;
	UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0); // Enable receiver, transmitter and receiver interrupt
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8 Bit (UCSZn) Enabled, No Parity (UPMn)

	UBRR0H = 00;
	UBRR0L = 103; //baudrade 9600 bij 16Mhz

	sei();
}

void hzBlink() {
	static int counter = 0;
	static int needChange = 0;

	_delay_ms(20);
	counter++;
	if (counter >= 20) {
		PORTB ^= (1 << PORTB4);
		counter = 0;

		// Only change after full cycle

		needChange = !needChange;

		if (needChange) {
			teller--;
			PORTB |= (teller & 0x0F); // Set first 4 bits of port to the 1s of teller int
			PORTB &= ~(~teller & 0x0F); // Reset first 4 bits of port to the 0s of teller int
		}
	}
}

void writeString(char st[]) {
	for (uint8_t i = 0; st[i] != 0; i++) {
		writeChar(st[i]);
	}
}

void writeChar(char x) {
	while (~UCSR0A & (1 << UDRE0))
		;
	UDR0 = x;
}
