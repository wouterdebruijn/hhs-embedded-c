/*
 * De eerste kennismaking met het eXplain boardje - 7
 *
 * Created: 13/02/2021 12:50:48
 * Author : Wouter
 */ 

#include <avr/io.h>


int main(void)
{
	DDRB = (1 << PORTB5); // Set LED pin to output
	
    while (1) 
    {
		PORTB |= (PINB & (1 << PINB7) << PORTB5); // Set LED to the button value 
    }
	
}

