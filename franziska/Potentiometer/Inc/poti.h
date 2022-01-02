/*
 * poti.h
 *
 *  Created on: Dec 4, 2021
 *      Author: Franziska Rothen
 */

#ifndef INC_MAIN_H_
#define INC_MAIN_H_

#define MAXPOTI 4100
#include "stm32f4xx_hal.h"

uint16_t rawValue;

HAL_StatusTypeDef potiInit(void);
HAL_StatusTypeDef potiRead(uint16_t* value);
int potiPrint(uint16_t* value);
HAL_StatusTypeDef potiDeInit();

#endif /* INC_MAIN_H_ */
