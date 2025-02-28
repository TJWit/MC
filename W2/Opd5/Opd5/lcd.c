/*
 * lcd.c
 *
 * Created: 28-2-2025 10:44:44
 *  Author: Kersjan14
 */

#include <stddef.h>
#include <avr/io.h>
#define F_CPU 8e6
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>

typedef unsigned char byte;

static void lcd_strobe_lcd_e(void)
{
	PORTA |= (1<<6);
	_delay_ms(1);
	PORTA &= ~(1<<6);
	_delay_ms(1);
}

static void lcd_cmd_high_nibble(byte cmd)
{
	PORTC = (cmd & 0xF0); // High nibble to PC4-7
	PORTA &= ~(1<<4); // Force RS=PA4 low
}

static void lcd_cmd_low_nibble(byte cmd)
{
	PORTC = (cmd & 0x0F) << 4; // Low nibble to PC4-7
	PORTA &= ~(1<<4); // Force RS=PA4 low
}

static void lcd_data_high_nibble(byte data)
{
	PORTC = (data & 0xF0); // High nibble to PC4-7
	PORTA |= (1<<4); // Force RS=PA4 high
}

static void lcd_data_low_nibble(byte data)
{
	PORTC = (data & 0x0F) << 4; // Low nibble to PC4-7
	PORTA |= (1<<4); // Force RS=PA4 high
}
static void lcd_command(byte cmd)
{
	lcd_cmd_high_nibble(cmd);
	lcd_strobe_lcd_e();
	lcd_cmd_low_nibble(cmd);
	lcd_strobe_lcd_e();
}

static void lcd_data(byte data)
{
	lcd_data_high_nibble(data);
	lcd_strobe_lcd_e();
	lcd_data_low_nibble(data);
	lcd_strobe_lcd_e();
}

static void lcd_init_4bits_mode(void)
{
	// Note: this is for UNI-DS6 development board
	// Set appropriate pins to output
	PORTC &= 0x0F; // Set output pins low first
	PORTA &= 0x50;
	DDRC |= 0xF0; // Make PC4-7 output
	DDRA |= 0x50; // Make PA4 (RS) and PA6 (E) output
	
	// Switch from 8 bit to 4 bit mode
	// Note: first command is still in 8 bit mode
	PORTC = 0x20; // Function set: 0010 0000
	lcd_strobe_lcd_e();
	// Note: now in 4 bit mode, so send all data in nibbles
	
	// Set 2 lines, 5x8 dots characters
	lcd_command(0x28); // Function set: 0010 1000
	
	// Set display on, cursor off, blinking off
	lcd_command(0x0C); // Display on/off control: 0000 1100
	
	// Set cursor increment, no shift
	lcd_command(0x06); // Entry mode set: 0000 0110
	
	// Clear display, set data address 0 (top left)
	lcd_command(0x01); // Clear display
}

static void lcd_clear(void)
{
	lcd_command(0x01);
}

static void lcd_return_home(void)
{
	lcd_command(0x02);
}

static void lcd_data_address(byte address)
{
	lcd_command(address | 0x80);
}

static void lcd_write_string(char *str)
{
	for (int i = 0; i < strlen(str); i++)
	{
		lcd_data(str[i]);
	}
}

void init() {
	DDRG = 0xFF;
	PORTG = 0x01;
	lcd_init_4bits_mode();
	PORTG = 0x02;
	lcd_clear();
	PORTG = 0x03;
}
void display_text(char *str) {
	PORTG = 0x04;
	lcd_write_string(str);
	PORTG = 0x05;
}

void set_cursor(int position) {
	
}