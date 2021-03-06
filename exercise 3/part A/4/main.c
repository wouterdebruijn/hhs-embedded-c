#define F_CPU 16000000

#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

void initPortD();
void hzBlink();

int teller = 15;

int main(void) {
	DDRB = 0xFF;

	initPortD();

	while (1) {
		if (teller > 0) {
			hzBlink();
		} else {
			PORTB = 0x00;
		}
	}

}

void hzBlink() {
	static int counter = 0;
	static int needChange = 0;

	_delay_ms(20);
	counter ++;
	if (counter >= 20) {
		PORTB ^= (1 << PORTB4);
		counter = 0;

		// Only change after full cycle

		needChange = !needChange;

		if (needChange) {
			teller --;
			PORTB |= (teller & 0x0F); // Set first 4 bits of port to the 1s of teller int
			PORTB &= ~(~teller & 0x0F); // Reset first 4 bits of port to the 0s of teller int
		}
	}
}

void initPortD() {
	DDRD = 0x00; // Not really needed, but doing it anyway
	PORTD |= (1 << PORTD2);
}
