/*
 * Serial.c
 *
 *  Created on: Oct 21, 2019
 *      Author: cuauhtemoc
 */

#include "Serial.h"

void serial_printf(UART_HandleTypeDef *huart, uint8_t *pData, uint32_t Timeout){
	uint16_t Size = 0;
	do{
		Size++;
	}while(pData[Size]!='\0');
	HAL_UART_Transmit(huart, pData,Size, HAL_MAX_DELAY);
}

void serial_scanf(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout){
	  uint8_t buffer2[50];
	  HAL_UART_Receive(huart, (uint8_t *)buffer2,Size+1, HAL_MAX_DELAY);
	  strncat((char *)pData,(char *)buffer2,Size);
}
