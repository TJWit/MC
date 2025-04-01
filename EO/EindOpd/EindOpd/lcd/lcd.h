/*
 * lcd.h
 *
 * Created: 28-2-2025 10:44:53
 *  Author: Kersjan14
 */ 


#ifndef LCD_H_
#define LCD_H_

#include <stdbool.h>

void lcd_init();
void lcd_display_text(char *str, bool clear);
void lcd_set_cursor(int position);
void lcd_clear();

#endif /* LCD_H_ */