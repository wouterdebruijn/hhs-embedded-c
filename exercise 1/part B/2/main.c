/*
 * Opdracht.c
 *
 * Created: 13/02/2021 13:30:59
 * Author : Wouter
 */ 

#include <avr/io.h>
#include <util/delay.h>

void setLed(uint8_t led, uint8_t state);

int main(void) {
	
	DDRD = 0xFF; // Set all pins to output;
	DDRB = 0xFF; // Set all pins to output;
	
    /* Replace with your application code */
    while (1) 
    {
		uint8_t i;
		for (i = 0; i < 10; i++) {
			setLed(i, 1);
			_delay_ms(5000);
			setLed(i, 0);
		}
    }
}

void setLed(uint8_t led, uint8_t state) {
	if (state) {
		if (led >= 8)
			PORTB |= (1 << (led - 8));
		else 
			PORTD |= (1 << led);
	} else {
		if (led >= 8)
			PORTB &= ~(1 << (led - 8));
		else
			PORTD &= ~(1 << led);
	}
}

