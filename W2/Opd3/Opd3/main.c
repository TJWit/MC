/*
 * Opd3.c
 *
 * Created: 21-2-2025 13:52:14
 * Author : Kersjan14
 */ 


#define F_CPU 8e6
#include <avr/io.h>
#include <string.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define LCD_E 	3
#define LCD_RS	2

void lcd_strobe_lcd_e(void);
void init_4bits_mode(void);
void lcd_write_string(char *str);
void lcd_write_data(unsigned char byte);
void lcd_write_cmd(unsigned char byte);

void lcd_strobe_lcd_e(void) {
	PORTC |= (1<<LCD_E);	// E high
	_delay_ms(1);			// nodig
	PORTC &= ~(1<<LCD_E);  	// E low
	_delay_ms(1);			// nodig?
}

void init_4bits_mode(void) {
	// PORTC output mode and all low (also E and RS pin)
	DDRC = 0xFF;
	PORTC = 0x00;

	// Step 2 (table 12)
	PORTC = 0x20;	// function set
	lcd_strobe_lcd_e();

	// Step 3 (table 12)
	PORTC = 0x20;   // function set
	lcd_strobe_lcd_e();
	PORTC = 0x80;
	lcd_strobe_lcd_e();

	// Step 4 (table 12)
	PORTC = 0x00;   // Display on/off control
	lcd_strobe_lcd_e();
	PORTC = 0xF0;
	lcd_strobe_lcd_e();

	// Step 4 (table 12)
	PORTC = 0x00;   // Entry mode set
	lcd_strobe_lcd_e();
	PORTC = 0x60;
	lcd_strobe_lcd_e();

}

void lcd_write_string(char *str) {
	// Het kan met een while:

	// while(*str) {
	// 	lcd_write_data(*str++);
	// }

	// of met een for:
	for(;*str; str++){
		lcd_write_data(*str);
	}
}

void lcd_write_data(unsigned char byte) {
	// First nibble.
	PORTC = byte;
	PORTC |= (1<<LCD_RS);
	lcd_strobe_lcd_e();

	// Second nibble
	PORTC = (byte<<4);
	PORTC |= (1<<LCD_RS);
	lcd_strobe_lcd_e();
}

void lcd_write_command(unsigned char byte)

{
	// First nibble.
	PORTC = byte;
	PORTC &= ~(1<<LCD_RS);
	lcd_strobe_lcd_e();

	// Second nibble
	PORTC = (byte<<4);
	PORTC &= ~(1<<LCD_RS);
	lcd_strobe_lcd_e();
}

void lcd_clear(void) {
	lcd_write_command(0x00);
	lcd_write_command(0x01);  // Clear display command
	_delay_ms(2);            // Wait for clear operation to complete
	lcd_write_command(0x80);  // Move cursor to home position
}

const char* table[16] = {"0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F"};

void display(int digit) {
    lcd_clear();
	
	if (digit <= 15) {
		char* string = table[digit];  // Safe assignment of const char*
		lcd_write_string(string);
		} else if (digit < 0) {
		lcd_write_string("E");
		} else {
		lcd_write_string("E");
	}
}

volatile int number = 0;

ISR(INT1_vect) {
	number++;
	display(number);
}

ISR(INT2_vect) {
	number--;
	display(number);
}


int main( void ) {
	// Init I/O
	DDRD = 0xFF;
	EICRA |= 0x3C;
	EIMSK |= 0x06;
	
	sei();
	
	init_4bits_mode();
	lcd_clear();
	
	display(number);

	// Loop forever
	while (1) {
		PORTD ^= (1<<7);	// Toggle PORTD.7
		_delay_ms( 250 );
	}

	return 1;
}