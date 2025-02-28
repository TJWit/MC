/*
 * Opd4.c
 *
 * Created: 28-2-2025 09:47:14
 * Author : Kersjan14
 */ 

#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

typedef struct {
	unsigned char data;
	unsigned int delay ;
} PATTERN_STRUCT;

PATTERN_STRUCT pattern[] = {
	{0x01, 50},
	{0x02, 50},
	{0x04, 50},
	{0x08, 50},
	{0x10, 50},
	{0x20, 50},
	{0x00, 0}
};


int main( void )
{
	DDRA = 0xFF;					// PORTA all output
		
	while (1) {
		// Set index to begin of pattern array
		int index = 0;
		// as long as delay has meaningful content
		while( pattern[index].delay != 0 ) {
			// Write data to PORTA
			PORTA = pattern[index].data;
			// wait
			wait(pattern[index].delay);
			// increment for next round
			index++;
		}
	}
	return 1;
}

