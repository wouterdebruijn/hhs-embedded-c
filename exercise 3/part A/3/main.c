#define F_CPU 16000000

#include <avr/io.h>
#include <avr/delay.h>

void hzBlink();

int main(void) {
	DDRB = 0xFF;

	while (1) {
		hzBlink();
		_delay_ms(1000);
	}

}

void hzBlink() {
	PORTB ^= (1 << PORTB4);
}
