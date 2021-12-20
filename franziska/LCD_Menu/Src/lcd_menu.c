/*
 * lcd_menu.c
 *
 *  Created on: Dec 5, 2021
 *      Author: Franziska
 */

#include "lcd_menu.h"
#include "lcd_driver.h"
#include "main.h"

char msgBuf1[30];
char glass[10];

void welcome_display(void){
	lcd_clear();
	lcd_setString(4, 4, "WELCOME!", LCD_FONT_8, false);
	lcd_show();
	HAL_Delay(3000);
}

void menu1_display(void){
	lcd_clear();
	lcd_setString(4, 4, "To continue", LCD_FONT_8, false);
	lcd_setString(4, 16, "press joystick!", LCD_FONT_8, false);
	lcd_show();
}

void menu2_display(void){
	lcd_clear();
	lcd_setString(4, 4, "Place the glass", LCD_FONT_8, false);
	lcd_setString(4, 16, "on the scale", LCD_FONT_8, false);
	lcd_show();
}

// which glass has been chosen
void menu3_display(int weight){
	if (weight > 300)
		sprintf(glass, "Big");
	else
		sprintf(glass, "Small");
	lcd_clear();
	lcd_setString(4, 4, "Glass chosen:", LCD_FONT_8, false);
	lcd_setString(4, 16, glass, LCD_FONT_8, false);
	lcd_show();
}


void menu4_display(uint16_t* value){
	lcd_clear();
	sprintf(msgBuf1,"%i%% sirup chosen", ((int)*value/200)+5); 	// fill message buffer
	lcd_setString(4, 1, msgBuf1, LCD_FONT_8, false); 		// LCD message
	lcd_show();
}

