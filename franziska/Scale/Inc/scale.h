/*
 * scale.h
 *
 *  Created on: Dec 18, 2021
 *      Author: Franziska Rothen
 */

#ifndef INC_SCALE_H_
#define INC_SCALE_H_

#include "hx711.h"

void initScale(void);
int getWeight(void);
int getWeight2(void);
int checkWeight(char size, int weight, int percentage);
int checkWeight2(char size, int weight, int percentage);

#endif /* INC_SCALE_H_ */
