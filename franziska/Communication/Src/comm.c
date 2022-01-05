/*
 * comm.c
 *
 *  Created on: Dec 20, 2021
 *      Author: Franziska Rothen
 *
 *  Contains a function to send a message to another microcontroller using UART.
 *
 */


#include "comm.h"
#include "usart.h"
#include <string.h>
#include <stdlib.h>

void sendMessage(char *messageToSend){
	char * messageEnding = "\r\n";
	int messageLen = strlen(messageToSend) + strlen(messageEnding);
	char * message = malloc(messageLen);
	strcpy(message, messageToSend);
	strcat(message, messageEnding);
	HAL_UART_Transmit(&huart1, (uint8_t*)message, messageLen, HAL_MAX_DELAY);	// communication with second microcontroller
	HAL_UART_Transmit(&huart2, (uint8_t*)message, messageLen, HAL_MAX_DELAY);	// for debugging purposes

	free(message);
}
