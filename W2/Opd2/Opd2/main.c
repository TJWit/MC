/*
 * O2.c
 *
 * Created: 21-2-2025 12:25:19
 * Author : Kersjan14
 */ 

#define F_CPU 8e6

#include <avr/io.h>
#include <avr/interrupt.h>

volatile int light = -1;

ISR(INT1_vect) {
	light++;
	PORTA = (1 << light);
}

ISR(INT2_vect) {
	light--;
	PORTA = (1 << light);
}

int main(void)
{
	DDRA = 0xFF;
	
	EICRA |= 0x3C;
	EIMSK |= 0x06;
	
	sei();
	
    while (1) 
    {
    }
}

