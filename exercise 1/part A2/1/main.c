/*
 * Het aan en uit zetten van een LED - 1
 *
 * Created: 13/02/2021 12:50:48
 * Author : Wouter
 */ 

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB |= (1 << PORTB5); // Set LED pin to output
	
	uint8_t toggle = 0;
	
    while (1) 
    {
		if (PINB & (1 << PINB7)) { // If pin 7 (Button) HIGH
			_delay_ms(20); // Anti-dender
					
			if (!toggle) {
				PORTB ^= (1 << PORTB5); // Toggle LED
				toggle = 1;
			}
			
		} else {
			toggle = 0;
		}
    }	
}