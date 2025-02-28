/*
 * Opd3.c
 *
 * Created: 21-2-2025 13:52:14
 * Author : Kersjan14
 */ 


#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile int number = 0;

// Increase interupt
ISR(INT1_vect) { 
	number++;
	display(number);
}

// Decrease interrupt
ISR(INT2_vect) {
	number--;
	display(number);
}

// Lookup Table
const unsigned char symbols[16] = {
	0x3F,
	0x30,
	0x5B,
	0x4F,
	0x66,
	0x6D,
	0x7D,
	0x07,
	0x7F,
	0x6F,
	0x77,
	0x7C,
	0x39,
	0x5E,
	0x79,
	0x71,
};

// Displays current hexnumber on 7seg display
void display(int number) {
	if (number <= 15) {
		PORTA = symbols[number];
	} else if (number < 0) {
		PORTA = 0x79;
	} else {
		PORTA = 0x79;
	}
}

int main( void ) {
	// Init I/O
	DDRA = 0xFF;
	EICRA |= 0x3C;
	EIMSK |= 0x06;
	
	sei();
	
	display(number);

	while (1) {
	}

	return 1;
}