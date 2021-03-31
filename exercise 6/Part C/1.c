#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void initADC();
void initTimer2FastPWM();
void dimLed(uint8_t value);

void initUsart();
void writeString(char st[]);
void writeChar(char x);
void writeInt(int i);

void initTimer1Fast10PWM();
void pasPeriodeTijdTimer1Aan(uint8_t scaler);

uint16_t leesADwaarde(uint8_t analogInput);

volatile uint16_t adValues[8];

ISR(ADC_vect) {
	uint8_t index = ADMUX & 0x0F; // Strip first 4 bits;
	adValues[index] = ADC; // store value in array;
}

int main(void) {
	initADC();
	initTimer2FastPWM();
	initTimer1Fast10PWM();

	while(1) {
		uint16_t value = leesADwaarde(5);
		dimLed((double)value / 1023 * 255);

		int i;
		for (i=1; i < 6; i++) {
			pasPeriodeTijdTimer1Aan(i);
			_delay_ms(1000);
		}
	}
}

void dimLed(uint8_t value) {
	OCR2B = value;
}

void initADC() {
	ADMUX |= (1 << REFS0); /* reference voltage on AVCC */
	ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2); /* ADC clock prescaler /128 */
	ADCSRA |= (1 << ADIE); /* enable interrupt */
	ADCSRA |= (1 << ADEN); /* enable ADC */

	sei();
}

void initTimer2FastPWM() {
	DDRD |= (1 << PD3); // Set output register.
	TCCR2A = (1 << COM2B1) | (1 << WGM20) | (1 << WGM21); // Enable clear on Compare Fast PWM
	TCCR2B = (1 << CS22) | (1 << WGM22);
	OCR2A = 255;
}

void initTimer1Fast10PWM() {
	DDRB |= (1 << PB1);
	TCCR1A = (1 << COM1A1) | (1 << COM1A0) | (1 << WGM10) | (1 << WGM11); // Reversed Fast PWM, 10-bit
	TCCR1B = (1 << WGM12); // 10 Bit PWM

	TCCR1B |= (1 << CS10) | (1 << CS11); // Prescaler: 64
	OCR1A = 511;
}

void pasPeriodeTijdTimer1Aan(uint8_t scaler) {
	OCR1A = 1023 / scaler;
}

uint16_t leesADwaarde(uint8_t analogInput) {
	ADMUX &= ~(0x0F);
	ADMUX |= (analogInput & 0x0F); // Set first 4 bits of port to the 1s of teller int
	ADCSRA |= (1 << ADSC | 1 << ADIF); /* start ADC conversion */
	return(adValues[analogInput]);
}
