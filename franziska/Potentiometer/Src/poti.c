/*
 * poti.c
 *
 *  Created on: Dec 4, 2021
 *      Author: Franziska
 */

#include "poti.h"
#include "adc.h"
#include "stdio.h"
#include "math.h"
#include "lcd_driver.h"

char msgBuf1[30]; 	// Prepare buffer for message

HAL_StatusTypeDef potiInit(void){
	return HAL_ADC_Start(&hadc1);
}


HAL_StatusTypeDef potiRead(uint16_t* value){
	if(potiInit() == HAL_OK){
		*value = HAL_ADC_GetValue(&hadc1);
		return HAL_OK;
	}
	else
		return HAL_ERROR;
}

char msgBuf1[30]; 	// Prepare buffer for message

void potiPrint(uint16_t* value){
	lcd_clear();
	lcd_setLine(12, 15, 12, 25, 1);
	lcd_setLine(12, 15, 115, 15, 1);
	lcd_setLine(12, 25, 116, 25, 1);
	lcd_setLine(115, 15, 115, 25, 1);
	switch((int)*value/200){
	case 0:
		lcd_setString(4, 4, "Sirup percentage: 5%", LCD_FONT_8, false);
		lcd_setBar(13, 16, 18, 24);
		break;
	case 1:
		lcd_setString(4, 4, "Sirup percentage: 6%", LCD_FONT_8, false);
		lcd_setBar(13, 16, 19, 24);
		break;
	case 2:
		lcd_setString(4, 4, "Sirup percentage: 7%", LCD_FONT_8, false);
		lcd_setBar(13, 16, 20, 24);
		break;
	case 3:
		lcd_setString(4, 4, "Sirup percentage: 8%", LCD_FONT_8, false);
		lcd_setBar(13, 16, 21, 24);
		break;
	case 4:
		lcd_setString(4, 4, "Sirup percentage: 9%", LCD_FONT_8, false);
		lcd_setBar(13, 16, 22, 24);
		break;
	case 5:
		lcd_setString(4, 4, "Sirup percentage: 10%", LCD_FONT_8, false);
		lcd_setBar(13, 16, 23, 24);
		break;
	case 6:
		lcd_setString(4, 4, "Sirup percentage: 11%", LCD_FONT_8, false);
		lcd_setBar(13, 16, 24, 24);
		break;
	case 7:
		lcd_setString(4, 4, "Sirup percentage: 12%", LCD_FONT_8, false);
		lcd_setBar(13, 16, 25, 24);
		break;
	case 8:
		lcd_setString(4, 4, "Sirup percentage: 13%", LCD_FONT_8, false);
		lcd_setBar(13, 16, 26, 24);
		break;
	case 9:
		lcd_setString(4, 4, "Sirup percentage: 14%", LCD_FONT_8, false);
		lcd_setBar(13, 16, 27, 24);
		break;
	case 10:
		lcd_setString(4, 4, "Sirup percentage: 15%", LCD_FONT_8, false);
		lcd_setBar(13, 16, 28, 24);
		break;
	case 11:
		lcd_setString(4, 4, "Sirup percentage: 16%", LCD_FONT_8, false);
		lcd_setBar(13, 16, 29, 24);
		break;
	case 12:
		lcd_setString(4, 4, "Sirup percentage: 17%", LCD_FONT_8, false);
		lcd_setBar(13, 16, 30, 24);
		break;
	case 13:
		lcd_setString(4, 4, "Sirup percentage: 18%", LCD_FONT_8, false);
		lcd_setBar(13, 16, 31, 24);
		break;
	case 14:
		lcd_setString(4, 4, "Sirup percentage: 19%", LCD_FONT_8, false);
		lcd_setBar(13, 16, 32, 24);
		break;
	case 15:
		lcd_setString(4, 4, "Sirup percentage: 20%", LCD_FONT_8, false);
		lcd_setBar(13, 16, 33, 24);
		break;
	case 16:
		lcd_setString(4, 4, "Sirup percentage: 21%", LCD_FONT_8, false);
		lcd_setBar(13, 16, 34, 24);
		break;
	case 17:
		lcd_setString(4, 4, "Sirup percentage: 22%", LCD_FONT_8, false);
		lcd_setBar(13, 16, 35, 24);
		break;
	case 18:
		lcd_setString(4, 4, "Sirup percentage: 23%", LCD_FONT_8, false);
		lcd_setBar(13, 16, 36, 24);
		break;
	case 19:
		lcd_setString(4, 4, "Sirup percentage: 24%", LCD_FONT_8, false);
		lcd_setBar(13, 16, 37, 24);
		break;
	case 20:
		lcd_setString(4, 4, "Sirup percentage: 25%", LCD_FONT_8, false);
		lcd_setBar(13, 16, 38, 24);
		break;
	default:
		break;
	}
	lcd_show();
}

HAL_StatusTypeDef potiDeInit()
{
	return HAL_ADC_Stop(&hadc1);
}

