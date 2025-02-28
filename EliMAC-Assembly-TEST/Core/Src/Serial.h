/*
 * Serial.h
 *
 *  Created on: Oct 21, 2019
 *      Author: cuauhtemoc
 */

#ifndef SERIAL_H_
#define SERIAL_H_

#include "stm32f7xx_hal.h"
#include "string.h"


void serial_printf(UART_HandleTypeDef *huart, uint8_t *pData, uint32_t Timeout);
void serial_scanf(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout);
#endif /* SERIAL_H_ */
