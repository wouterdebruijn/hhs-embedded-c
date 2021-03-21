#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

void initBlink();
void zetLedAan(uint8_t);
void zetLedUit(uint8_t);
int main(void) {
	initBlink();
	while (1) {
		zetLedAan(1);
		_delay_ms(500);
		zetLedUit(1);
		_delay_ms(500);
	}
	return 0;
}
void initBlink() {
	DDRB |= (1 << PORTB1);
}
void zetLedAan(uint8_t b) {
	PORTB |= (1 << PORTB1);
}
void zetLedUit(uint8_t b) {
	PORTB &= ~(1 << PORTB1);
}
