/*
 * rylruart.h
 *
 *  Created on: Mar 23, 2023
 *      Author: Miller Solis
 */

#ifndef INC_RYLRUART_H_
#define INC_RYLRUART_H_

#include "stm32l4xx.h"
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_def.h"

// UART Handle to be used to communicate with module.
// Defined in auto-generated main.c
extern UART_HandleTypeDef huart1;

inline bool uartTransmit(const uint8_t *pData, uint16_t Size, uint32_t Timeout=HAL_MAX_DELAY)
{
	HAL_StatusTypeDef result = HAL_UART_Transmit(&huart1, pData, Size, Timeout);

	return result == HAL_OK;
}

#endif /* INC_RYLRUART_H_ */
