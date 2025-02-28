/*
 * Opd5.c
 *
 * Created: 28-2-2025 10:40:20
 * Author : Kersjan14
 */ 

#define F_CPU 8e6

#include <avr/io.h>
#include <avr/delay.h>
#include "lcd.h"

void wait(int ms) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );
	}
}


int main(void)
{
	init();
	int i = 0;
	char buffer[10];
	
	display_text("Test");
	
	wait(10000);
	
    while (1) 
    {
		sprintf(buffer, "%d", i);
		display_text(i);
		wait(1000);
		i++;
    }
}

