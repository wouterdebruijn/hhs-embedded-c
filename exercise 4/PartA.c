#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

#define WAARDE1 200

void initUsart();
void writeString(char st[]);
void writeChar(char x);
void writeInt(int i);

int main(void) {

	uint16_t adcValue;
	DDRB = 0x10;
	ADMUX |= (1 << REFS0) | (1 << MUX2); /* reference voltage on AVCC */
	ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2); /* ADC clock prescaler /128 */
	ADCSRA |= (1 << ADEN); /* enable ADC */

	initUsart();

	// ------ Event loop ------ //
	while (1) {

		ADCSRA |= (1 << ADSC | 1 << ADIF); /* start ADC conversion */
		while (~ADCSRA & (1 << ADIF))
			;
		adcValue = ADC; /* read ADC in */

		writeString("Value: ");
		writeInt(adcValue);
		writeString("\n\r");

		if (adcValue > WAARDE1)
			PORTB |= (1 << PORTB4);

		else
			PORTB &= ~(1 << PORTB4);

		_delay_ms(250);
	} /* End event loop */
	return (0); /* This line is never reached */
}

void initUsart() {
	UCSR0A = 0;
	UCSR0B = (1 << RXEN0) | (1 << TXEN0); // Enable receiver and transmitter
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8 Bit (UCSZn) Enabled, No Parity (UPMn)

	UBRR0H = 00;
	UBRR0L = 103; //baudrade 9600 bij
}

void writeString(char st[]) {
	for (uint8_t i = 0; st[i] != 0; i++) {
		writeChar(st[i]);
	}
}

void writeChar(char x) {
	while (~UCSR0A & (1 << UDRE0))
		;
	UDR0 = x;
}

void writeInt(int i) {
	char buffer[8];
	itoa(i, buffer, 10);
	writeString(buffer);
}
