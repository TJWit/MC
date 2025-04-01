/*
 * EindOpd.c
 *
 * Created: 28-3-2025 13:33:48
 * Author : Kersjan14
 */ 

#define F_CPU 8e6

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdbool.h>
#include "lcd/lcd.h"

#define DHT_PIN PD6
#define DHT_IN PIND
#define DHT_DDR DDRD
#define DHT_PORT PORTD

#define DHT_LOW_PULSE_US 18000
#define DHT_HIGH_PULSE_US 100

// Structure to hold sensor data
typedef struct {
	uint16_t humidity;
	uint8_t temperature;
	uint8_t checksum;
	uint8_t error;
} dht_data;

void wait(int ms) {
	for (int i=0; i<ms; i++) {
		_delay_ms(1);
	}
}

void request_start() {
	DHT_DDR |= (1 << DHT_PIN);
	DHT_PORT &= ~(1 << DHT_PIN);
	_delay_us(DHT_LOW_PULSE_US);
	DHT_PORT |= (1 << DHT_PIN);
	_delay_us(DHT_HIGH_PULSE_US);
	DHT_DDR &= ~(1 << DHT_PIN);
}

uint8_t read_bit(void) {
	uint8_t bit_value = 0;
	
	// Wait for low pulse
	while (!(DHT_IN & (1 << DHT_PIN)));
	
	// Measure high pulse duration
	_delay_us(40);
	if (DHT_IN & (1 << DHT_PIN)) {
		bit_value = 1;
	}
	
	// Wait for end of bit
	while (DHT_IN & (1 << DHT_PIN));
	return bit_value;
}

uint8_t receive_byte(void) {
	uint8_t byte = 0;
	
	// Read 8 bits
	for (uint8_t i = 0; i < 8; i++) {
		uint8_t bit = read_bit();
		byte |= (bit << (7 - i));
	}
	
	return byte;
}

uint8_t read_dht11(dht_data *data) {
	uint8_t humidity_msb, humidity_lsb;
	uint8_t temp_msb, temp_lsb;
	uint8_t checksum;
	
	// Send start signal
	request_start();
	
	// Wait for response
	while ((DHT_IN & (1 << DHT_PIN)));  // Wait for low
	PORTA = 0x01;
	while (!(DHT_IN & (1 << DHT_PIN))); // Wait for high
	PORTA = 0x02;
	
	
	// Read data bytes
	humidity_msb = receive_byte();
	humidity_lsb = receive_byte();
	temp_msb = receive_byte();
	temp_lsb = receive_byte();
	checksum = receive_byte();
	
	// Verify checksum
	if ((humidity_msb + humidity_lsb + temp_msb + temp_lsb) != checksum) {		
		data->error = 1;
		return 0;
		
	}
	
	
	// Store valid data
	data->humidity = (humidity_msb << 8) | humidity_lsb;
	data->temperature = temp_msb;
	data->checksum = checksum;
	data->error = 0;
	
	return 1;
}

int main(void) {
	dht_data sensor_data;
	DDRA = 0xFF;
	lcd_init();
	char buffer[20];
	
	lcd_display_text("Temperature: ", true);
	lcd_set_line(1);
	lcd_display_text("Humidity:", false);
	
	while(1) {
		if (read_dht11(&sensor_data)) {
			sprintf(buffer, "%dC", sensor_data.temperature);
			lcd_set_line(0);
			lcd_set_cursor(13);
			lcd_display_text(buffer, false);

			sprintf(buffer, "%02d%%", sensor_data.humidity/100); // Add '%' for clarity
			lcd_set_line(1);
			lcd_set_cursor(10);
			lcd_display_text(buffer, false);
		} else {
			lcd_display_text("error", true);
		}
		
		//request_start();
		wait(1500);
	}
}


