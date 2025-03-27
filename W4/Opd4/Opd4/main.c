/*
 * Opd4.c
 *
 * Created: 14-3-2025 14:27:11
 * Author : Kersjan14
 */ 

#define F_CPU 8e6

#include <avr/io.h>
#include "lcd/lcd.h"
#include <stdbool.h>
#include <util/delay.h>
#include <stdio.h>

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
	lcd_init();
	lcd_display_text("Temperature: ", true);
	lcd_set_cursor(13);
	
	DDRA = 0xFF;
	
	setupADC();
	char buffer[3];
	
    while (1) {
		sprintf(buffer, "%03d", ADCH);
		lcd_display_text(buffer, false);
		PORTA = ADCH;
		wait(1000);
    }
}

