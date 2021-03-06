#define F_CPU 16000000

#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

void initExtInt();
void initPortD();

ISR(INT0_vect) {
	_delay_ms(20);
	if (~PIND & 1 << PORTD2) // Check that port is high, reduces bounce when combined with falling edge
		PORTB ^= 0xFF; // Toggle whole port B
}

int main(void) {
	DDRB = 0xFF;
	DDRD = 0x00;

	initPortD();
	initExtInt();

	while (1) {}

}
void initExtInt() {
	EIMSK = (1 << INT0);  // Setup interrupt
	EICRA = (1 << ISC01); // Setup falling edge
	sei(); // Enable global interrupts
}

void initPortD() {
	PORTD |= (1 << PORTD2);
}
