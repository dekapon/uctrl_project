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
char glass[30];
char size;

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
char menu3_display(int weight){
	if (weight > 190){
		sprintf(glass, "Big glass chosen");
		size = 1;
	}
	else{
		sprintf(glass, "Small glass chosen");
		size = 0;
	}
	lcd_clear();
	lcd_setString(4, 4, glass, LCD_FONT_8, false);
	lcd_show();
	return size;
}


void menu4_display(int value){
	lcd_clear();
	sprintf(msgBuf1,"%d%% sirup chosen", value); 			// fill message buffer
	lcd_setString(4, 1, msgBuf1, LCD_FONT_8, false); 		// LCD message
	lcd_show();
}

void menu5_display(void){
	lcd_clear();
	lcd_setString(4, 4, "Cheers!", LCD_FONT_8, false);
	lcd_show();
}
