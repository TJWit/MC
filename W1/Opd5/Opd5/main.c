/*
 * Opd5.c
 *
 * Created: 9-2-2024 12:35:11
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

const uint8_t lightPattern[] = {0x00, 0x01, 0x03, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xC0, 0x80};

int main(void)
{
	DDRD = 0xFF;
	
    while (1) 
    {
		for (int i = 0; i < sizeof(lightPattern); i++) {
			PORTD = lightPattern[i];
			wait(100);
		}
    }
}
