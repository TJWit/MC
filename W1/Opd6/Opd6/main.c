/*
 * Opd6.c
 *
 * Created: 9-2-2024 12:55:23
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
	int state = 0;
	
    while (1) 
    {
		if (PINC & 1 << 0){
			state = (state + 1) % 2;
			}
		
		switch (state)
		{
		case 0:
			PORTD = 0x80;
			wait(1000);
			PORTD = 0x00;
			wait(1000);
			break;
		case 1:
			PORTD = 0x80;
			wait(250);
			PORTD = 0x00;
			wait(250);
			break;
		}
    }
}

