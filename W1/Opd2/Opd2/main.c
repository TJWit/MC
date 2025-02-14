/*
 * Opd2.c
 *
 * Created: 9-2-2024 10:50:45
 * Author : Kersjan14
 */ 

#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>

void wait(int ms) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

int main(void)
{
	
	DDRD = 0xC0;
	
    while (1) 
    {
		PORTD = 0x80;
		wait(500);
		PORTD = 0x40;
		wait(500);
    }
	
	return 1;
}

