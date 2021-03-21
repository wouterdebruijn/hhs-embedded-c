#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define NOTE_D 293.66
#define NOTE_Ds 311.13
#define NOTE_F 349.23
#define NOTE_G 392
#define TIJDSDUUR1 180
#define TIJDSDUUR2 120

void playNoot(float freg, uint16_t tijd);
void initialisatie();
void rust(uint16_t v);
void itroBeethoven();

ISR(TIMER1_COMPA_vect) {
	PORTB ^= 0xFF;
}

int main(void) {

	initialisatie();

	while (1) {
		itroBeethoven();
		_delay_ms(2000);
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

void itroBeethoven() {
	playNoot(NOTE_G, TIJDSDUUR1);
	rust(TIJDSDUUR2);
	playNoot(NOTE_G, TIJDSDUUR1);
	rust(TIJDSDUUR2);
	playNoot(NOTE_G, TIJDSDUUR1);
	rust(TIJDSDUUR2);
	playNoot(NOTE_Ds, 4 * TIJDSDUUR1);
	rust(2 * TIJDSDUUR2);
	playNoot(NOTE_F, TIJDSDUUR1);
	rust(TIJDSDUUR2);
	playNoot(NOTE_F, TIJDSDUUR1);
	rust(TIJDSDUUR2);
	playNoot(NOTE_F, TIJDSDUUR1);
	rust(TIJDSDUUR2);
	playNoot(NOTE_D, 4 * TIJDSDUUR1);
}
