#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

ISR(TIMER1_COMPA_vect) {
	PORTB ^= 0xFF;
}

 int main(void)
{
	DDRB = 0xFF; // het genereren van een toon gebeurd op een output
	TCCR1B = (1 << CS10) | (1 << WGM12); // No prescale
	OCR1A = 27241; // 293.66 Hz ish

	TIMSK1 = (1 << OCIE1A); // Enable interrupt for ACR1A

	sei();
	_delay_ms(2000);
	cli();
	_delay_ms(2000);
	sei();
	_delay_ms(2000);
	cli();

	while (1) {}

}

