/*
 * Opd5.c
 *
 * Created: 28-2-2025 10:40:20
 * Author : Kersjan14
 */ 

#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

void wait(int ms) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );
	}
}


int main(void)
{
	init();
	
	display_text("Test");
	wait(1000);
	set_cursor(5);
	display_text("Hello World");
    while (1) 
    {
    }
}

