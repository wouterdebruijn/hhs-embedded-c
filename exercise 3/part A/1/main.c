#define F_CPU 16000000

#include <avr/io.h>
#include <avr/delay.h>

void initPortD();
int knopDxIngedrukt(int port);

int main(void) {
	DDRB = 0xFF;
	initPortD();

	while (1) {
		if (knopDxIngedrukt(PIND3))
			PORTB = 1 << PORTB1 | 1 << PORTB3;
		else
			PORTB = 1 << PORTB0 | 1 << PORTB2;
	}
}

int knopDxIngedrukt(int port) {
	int static toggle = 0;

	if (PIND & (1 << port)) { // If pin is High
		_delay_ms(20); // Anti-dender

		if (!toggle) {
			return(1);
			toggle = 1;
		}

	} else {
		toggle = 0;
	}
	return(0);
}

void initPortD() {
	PORTD |= (1 << PORTD3);
}
