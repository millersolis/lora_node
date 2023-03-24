/*
 * printuart.h
 *
 *  Created on: Mar 24, 2023
 *      Author: Miller Solis
 */

#ifndef INC_PRINTUART_H_
#define INC_PRINTUART_H_

#include "stm32l4xx.h"
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_def.h"

#include <cstring>

// UART Handle to be used for printing to external console.
// Defined in auto-generated main.c
extern UART_HandleTypeDef huart2;

inline bool print(const uint8_t *pData, uint16_t Size, uint32_t Timeout=HAL_MAX_DELAY)
{
	// Add termination
	int outputSize = Size + 2;
	uint8_t output[outputSize];
	memcpy(output, pData, Size);
	output[outputSize - 2] = (uint8_t) '\r';
	output[outputSize - 1] = (uint8_t) '\n';

	HAL_StatusTypeDef result = HAL_UART_Transmit(&huart2, output, outputSize, Timeout);

	return result == HAL_OK;
}

#endif /* INC_PRINTUART_H_ */
