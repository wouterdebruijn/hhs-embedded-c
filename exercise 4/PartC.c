#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void initUsart();
void writeString(char st[]);
void writeChar(char x);
void writeInt(int i);

void initAD();
void leesADwaarde(uint8_t analogInput);

volatile uint16_t adValues[8];

ISR(ADC_vect) {
	uint8_t index = ADMUX & 0x0F; // Strip first 4 bits;
	adValues[index] = ADC; // store value in array;
}

int main(void) {

	initUsart(); // Enable Usart
	initAD();

	// ------ Event loop ------ //
	while (1) {
		leesADwaarde(5);
		_delay_ms(20); // Without this, leesADwaarde(4) doesn't run.
		leesADwaarde(4);

		/*Send to Usart*/
		writeString("New Value: ");
		writeInt(adValues[4]);
		writeString("\tEdge: ");
		writeInt(adValues[5]);
		writeString("\n\r");

		if (adValues[5] > adValues[4])
			PORTB |= (1 << PORTB4);
		else
			PORTB &= ~(1 << PORTB4);

		_delay_ms(250);
	} /* End event loop */
	return (0); /* This line is never reached */
}

void initAD() {
	DDRB = 0x10;
	ADMUX |= (1 << REFS0); /* reference voltage on AVCC */
	ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2); /* ADC clock prescaler /128 */
	ADCSRA |= (1 << ADIE); /* enable interrupt */
	ADCSRA |= (1 << ADEN); /* enable ADC */

	sei(); // Enable global Interrupt
}

void leesADwaarde(uint8_t analogInput) {
	ADMUX |= (analogInput & 0x0F); // Set first 4 bits of port to the 1s of teller int
	ADMUX &= ~(~analogInput & 0x0F); // Reset first 4 bits of port to the 0s of teller int

	ADCSRA |= (1 << ADSC | 1 << ADIF); /* start ADC conversion */
}

void initUsart(void) {
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
