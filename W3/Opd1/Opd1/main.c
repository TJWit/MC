/*
 * Opd1.c
 *
 * Created: 28-2-2025 13:45:49
 * Author : Kersjan14
 */ 

#define F_CPU 8e6

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "lcd/lcd.h"
#include <avr/interrupt.h>

#define BIT(x)			(1 << (x))

void wait(int ms) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );
	}
}

int main(void)
{
	init();
	
	DDRD &= ~BIT(7);
	TCCR2 = 0b00000111;
	
	display_text("Teller: ");
	
    while (1) 
    {
	    char buffer[10];
	    sprintf(buffer, "Teller: %03d", TCNT2);
	    display_text(buffer);
		wait(100);
    }
}

