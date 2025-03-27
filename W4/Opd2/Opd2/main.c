/*
 * Opd2.c
 *
 * Created: 14-3-2025 14:12:33
 * Author : Kersjan14
 */ 

#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>

void wait(int ms) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );
	}
}

void setupADC() {
	ADMUX = 0b11100000;
	ADCSRA = 0b11100110;
}

int main(void)
{
	DDRA = 0xFF;
	DDRB = 0xFF;
	
	setupADC();
	
    /* Replace with your application code */
    while (1) 
    {
	    PORTA = ADCL;
	    PORTB = ADCH;

		wait(100);

    }
}

