#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void initBlink();
void initUsart();

int timerInterval = 1000;

ISR(TIMER0_OVF_vect) {
	static int teller = 0;

	teller ++;
	if (teller >= timerInterval) {
		teller = 0;
		PORTB ^= 1 << PORTB1;
	}
}

ISR(USART_RX_vect) {
	char send = UDR0;
	int toInt = send - 48;

	timerInterval = toInt * 250; // Every step adds .25 Hz. So 1 is 0.25Hz, 2 0.5Hz etc.
}


int main(void) {
	initBlink();
	initUsart();

	while (1) {	}
	return 0;
}

void initBlink() {
	DDRB |= (1 << PORTB1);

	TCCR0A = 0;
	TCCR0B = 1 << CS00 | 1 << CS01;
	TIMSK0 = 1 << TOIE0;
	TCNT0 = 256-250;
	sei();
}

void initUsart() {
	UCSR0A = 0;
	UCSR0B = (1 << RXEN0) | (1 << RXCIE0);
	UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);

	UBRR0H = 00;
	UBRR0L = 103;
}
