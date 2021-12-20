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


char msgBuf[30];
float weight;

/*
initScale(loadcell){
	hx711_init(&loadcell, HX711_CLK_GPIO_Port, HX711_CLK_Pin, HX711_DATA_GPIO_Port, HX711_DATA_Pin);
	hx711_coef_set(&loadcell, 354.5); 						// read afer calibration
	hx711_tare(&loadcell, 10);
	return loadcell;
}

void getWeight(loadcell){
	HAL_Delay(500);
	weight = hx711_weight(&loadcell, 10);
	sprintf(msgBuf,"weight: %f g \r\n", weight); // fill message buffer
	puts(msgBuf); // Uart message
}
*/
#endif /* SCALE_C_ */
