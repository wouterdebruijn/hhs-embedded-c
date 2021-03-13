/*
 * Opdracht.c
 *
 * Created: 13/02/2021 13:30:59
 * Author : Wouter
 *
 * Kleine bug, wanneer de richting veranderd wordt duurt het één cycle tot dit wordt toegepast.
 *
 */ 

#include <avr/io.h>
#include <util/delay.h>

void setLed(uint8_t led, uint8_t state);
int buttonPressed();

uint8_t pressed = 0;

int main(void) {
	
	DDRD = 0xFF; // Set all pins to output;
	DDRB = 0x03; // Set first 2 pins to output;
	
	uint8_t i = 0;
	
    /* Replace with your application code */
    while (1) 
    {
		if (buttonPressed()) {
			// Disable all LEDs
			PORTD = 0x00;
			PORTB &= ~0x03;
			
			// Set the LED
			setLed(i, 1);
				
			// Ready loop for next cycle
			if (i >= 9) i = 0;
			else i++;
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

int buttonPressed() {
	if (PINB & (1 << PINB7)) {
		if (!pressed) {
			pressed = 1;
			return(1);
		}
	} else {
		pressed = 0;
	}
	return(0);
}