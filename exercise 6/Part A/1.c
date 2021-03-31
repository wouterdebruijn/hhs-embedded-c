#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

void initTimer2FastPWM();
void dimLed(uint8_t value);

int main(void) {

	initTimer2FastPWM();
	_delay_ms(1000);
	dimLed(255);
	_delay_ms(1000);

	while(1) {
		dimLed(50);
		_delay_ms(500);
		dimLed(220);
		_delay_ms(500);
	}
}

void initTimer2FastPWM() {
	DDRD |= (1 << PD3); // Set output register.
	TCCR2A = (1 << COM2B1) | (1 << WGM20) | (1 << WGM21); // Enable clear on Compare Fast PWM
	TCCR2B = (1 << CS22) | (1 << WGM22);
	OCR2A = 255;
}

void dimLed(uint8_t value) {
	OCR2B = value;
}
