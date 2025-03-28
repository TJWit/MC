/*
 * Opd2.c
 *
 * Created: 28-3-2025 12:07:57
 * Author : Kersjan14
 */ 

#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdbool.h>

#define DDR_SPI DDRB
#define PORT_SPI PORTB

void wait(int ms) {
	for (int i=0; i<ms; i++) {
		_delay_ms(1);
	}
}

void spi_init() {
	DDR_SPI = 0xF7;
	PORT_SPI |= (1 << 0);
	SPCR = 0b11010010;
}

void spi_write(unsigned char data) {
	SPDR = data;
	while(!(SPSR & 1 << SPIF));
}

void spi_slaveSelect(unsigned char chipNumber) {
	PORT_SPI &= ~(1<<chipNumber);
}

void spi_slaveDeselect(unsigned char ChipNumber) {
	PORT_SPI |= (1<<ChipNumber);
}

void spi_writeWord(unsigned char adress, unsigned char data) {
	spi_slaveSelect(0);
	spi_write(adress);
	spi_write(data);
	spi_slaveDeselect(0);
}

// Initialize the driver chip (type MAX 7219)
void displayDriverInit()
{
	spi_writeWord(0x09, 0xFF); // 09:decode, FF:all digits
	spi_writeWord(0x0A, 0x0F); // 0A:intensity, 0F:max (01-0F)
	spi_writeWord(0x0B, 0x03); // 0B:scan-limit, 03:0-3
	spi_writeWord(0x0C, 0x01); // 0C:shutdown register, 01:normal operation
}

// Set display on ('normal operation')
void displayOn()
{
	spi_writeWord(0x0C, 0x01); // 0C:shutdown register, 01:normal operation
}

// Set display off ('shut down')
void displayOff()
{
	spi_writeWord(0x0C, 0x00); // 0C:shutdown register, 00:shut down
}

void writeLEDDisplay(int value) {
	if (value >= -999 && value <= 9999) {
		int digits[4];
		bool isNegative = (value < 0);
		bool firstDigit = false;
		int temp = abs(value);
		
		// Calculate numbers
		digits[3] = temp % 10;
		temp /= 10;
		digits[2] = temp % 10;
		temp /= 10;
		digits[1] = temp % 10;
		digits[0] = temp / 10;
		
		for (int i = 3; i >= 0; i--) {
			spi_writeWord(i+1, digits[3-i]);
			if (!firstDigit && digits[3-i] != 0) {
				firstDigit = true;
				if (isNegative) {
					spi_writeWord(i+2, 'J');
				}
			}
			
		}
	}
}

int main(void) {
	
	DDRB = 0x01;
	spi_init();
	displayDriverInit();
	
	writeLEDDisplay(-910);
	wait(2000);
	writeLEDDisplay(12);
	wait(2000);
	writeLEDDisplay(-9);
	wait(2000);
	writeLEDDisplay(1414);

	return (1);
}

