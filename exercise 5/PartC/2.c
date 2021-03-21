#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define NOTE_D 293.66
#define NOTE_Ds 311.13
#define NOTE_F 349.23
#define NOTE_G 392
#define TestTIJDSDUUR1 1800
#define TestTIJDSDUUR2 1200

void playNoot(float freg, uint16_t tijd);
void initialisatie();
void rust(uint16_t v);

ISR(TIMER1_COMPA_vect) {
	PORTB ^= 0xFF;
}

int main(void) {

	initialisatie();
	playNoot(NOTE_D,TestTIJDSDUUR1);
	rust(TestTIJDSDUUR2);
	playNoot(NOTE_Ds,TestTIJDSDUUR1);
	rust(TestTIJDSDUUR2);
	playNoot(NOTE_F,TestTIJDSDUUR1);
	rust(TestTIJDSDUUR2);
	playNoot(NOTE_G,TestTIJDSDUUR1);

	while (1) {
	}

}

void initialisatie() {
	DDRB = 0xFF; // het genereren van een toon gebeurd op een output
	TCCR1B = (1 << CS10) | (1 << WGM12); // No prescale
	TIMSK1 = (1 << OCIE1A); // Enable interrupt for ACR1A
}

void rust(uint16_t v) {
	for (uint16_t i = 0; i < v; ++i) {
		_delay_ms(1);
	}
}

void playNoot(float freg, uint16_t tijd) {
	uint16_t fOCnA = (F_CPU / (2 * 1 * freg)) - 1;
	OCR1A = fOCnA;
	sei();
	rust(tijd);
	cli();
}
