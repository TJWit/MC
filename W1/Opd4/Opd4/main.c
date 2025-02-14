/*
 * Opd3.c
 *
 * Created: 9-2-2024 12:25:34
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
	DDRD = 0xFF;
	
	while (1) 
	{
		for (int i = 0; i < 8; i++) {
			PORTD = (1 << i);
			wait(50);
		}
	}
}

