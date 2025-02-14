/*
 * Opd3.c
 *
 * Created: 9-2-2024 11:50:59
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


int main(void)
{
	DDRD = 0x80;
	
	while (1) 
	{
		if (PINC & 0x01){
			PORTD = 0x80;
			wait(500);
			PORTD = 0x00;
			wait(500);
		} else {
			PORTD = 0x00;
		}
	}
}

