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

#define RX_BUF_SIZE		10
#define MAIN_BUF_SIZE	20
uint8_t rxBuf[RX_BUF_SIZE];
uint8_t mainBuf[MAIN_BUF_SIZE];
#include <cstring>

// =================================================================================
// Handles defined in auto-generated main.c

// UART Handle to be used to communicate with module.
extern UART_HandleTypeDef huart1;

// DMA UART1 Handle to be used to receive data.
extern DMA_HandleTypeDef hdma_usart1_rx;

// =================================================================================
inline bool uartTransmit(const uint8_t *pData, uint16_t Size, uint32_t Timeout=HAL_MAX_DELAY)
{
	HAL_StatusTypeDef result = HAL_UART_Transmit(&huart1, pData, Size, Timeout);

	return result == HAL_OK;
}

inline void enableDMAReceive()
{
	HAL_UARTEx_ReceiveToIdle_DMA(&huart1, rxBuf, RX_BUF_SIZE);
	__HAL_DMA_DISABLE_IT(&hdma_usart1_rx, DMA_IT_HT);
}

extern "C"
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	if (huart->Instance == USART1) {
		memcpy(mainBuf, rxBuf, Size);
		enableDMAReceive();
	}
}

#endif /* INC_RYLRUART_H_ */
