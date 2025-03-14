/*
 * Opd2.c
 *
 * Created: 28-2-2025 15:06:07
 * Author : Kersjan14
 */ 

#define F_CPU 8e6

#include <avr/io.h>
#include <avr/interrupt.h>

volatile static uint8_t state = 0;

// Timer2 interrupt handler
ISR(TIMER2_COMP_vect) {
	
	switch(state) {
		case 0: // Hoog voor 15ms
		PORTD |= (1 << 7);  // Zet PD7 hoog
		OCR2 = 117;           // Reset timer voor 15ms
		state = 1;
		break;
		
		case 1: // Laag voor 25ms
		PORTD &= ~(1 << 7); // Zet PD7 laag
		OCR2 = 195;           // Reset timer voor 25ms
		state = 0;
		break;
	}
}

int main(void) {
	// Configureer PORTD.7 als output
	DDRD |= (1 << 7);
	
	// Timer2 configuratie
	TCCR2 = 0b00001101;  // CTC mode, prescaler 1024
	TCNT2 = 0;
	OCR2 = 117;  // Begin met 15ms interval
	TIMSK |= (1<<7);  // Enable Timer2 compare interrupt
	sei();  // Enable global interrupts
	
	while(1) {
		// Programma blijft hier hangen
		// Timer2 interrupt handelt de pulsen
	}
	
	return 0;
}

