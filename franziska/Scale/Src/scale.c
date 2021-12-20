/*
 * scale.h
 *
 *  Created on: Dec 18, 2021
 *      Author: Franziska
 */


#ifndef SCALE_C_
#define SCALE_C_

#include <stdio.h>
#include <stdbool.h>
#include "scale.h"
#include "stm32f4xx_hal.h"
#include "gpio.h"
#include "hx711.h"
#include "lcd_driver.h"


char msgBuf[30];
float weight;
hx711_t loadcell;


void initScale(void){
	hx711_init(&loadcell, HX711_CLK_GPIO_Port, HX711_CLK_Pin, HX711_DATA_GPIO_Port, HX711_DATA_Pin);
	hx711_coef_set(&loadcell, 354.5); 						// read afer calibration
	hx711_tare(&loadcell, 10);
}

int getWeight(void){
	HAL_Delay(500);
	weight = hx711_weight(&loadcell, 10);
	sprintf(msgBuf,"Weight: %dg", (int)weight); // fill message buffer
	lcd_clear();
	lcd_setString(4, 1, msgBuf, LCD_FONT_8, false); 		// LCD message
	lcd_setString(4, 16, "Press js to continue", LCD_FONT_8, false);
	lcd_show();
	return (int)weight;
}

#endif /* SCALE_C_ */
