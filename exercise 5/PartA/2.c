#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void initBlink();


ISR(TIMER0_OVF_vect) {
	static int teller = 0;

	teller ++;
	if (teller >= 1000) {
		teller = 0;
		PORTB ^= 1 << PORTB1;
	}
}


int main(void) {
	initBlink();
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
