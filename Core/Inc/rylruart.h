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

// =================================================================================
// Handles defined in auto-generated main.c

// UART Handle to be used to communicate with module.
extern UART_HandleTypeDef huart1;

// DMA UART1 Handle to be used to receive data.
extern DMA_HandleTypeDef hdma_usart1_rx;

// =============================================================================================
inline bool uartTransmit(const uint8_t *pData, uint16_t Size, uint32_t Timeout=HAL_MAX_DELAY)
{
	HAL_StatusTypeDef result = HAL_UART_Transmit(&huart1, pData, Size, Timeout);

	return result == HAL_OK;
}

// =============================================================================================
// FIXME: Decouple received data reporting from DMA UART receive.
#include "configoptions.h"
#include "printuart.h"
#include "utils.h"

#include <cstring>
// =================================================================================
// DMA buffer
#define RX_BUF_SIZE		300
#define MAIN_BUF_SIZE	300
uint8_t rxBuf[RX_BUF_SIZE];
uint8_t mainBuf[MAIN_BUF_SIZE];
SpreadingFactor currSF;

inline void initRcvReporting(SpreadingFactor sf)
{
	currSF = sf;
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
		// Debugging
		// memcpy(mainBuf, rxBuf, Size);

		// Format for debugging includes SF.
		// SF: <sf>, +RCV=<Address>,<Length>,<Data>,<RSSI>,<SNR>
		uint16_t len = concatenateStrToArr<uint8_t>(mainBuf, "SF: ");
		len += concatenateStrToArr<uint8_t>(mainBuf + len, SFToStr(currSF));
		len += concatenateStrToArr<uint8_t>(mainBuf + len, " ");
		len += concatenateToArr<uint8_t, uint8_t>(mainBuf + len, rxBuf, Size);

		// Report
		print(mainBuf, len);

		// Re-enable DMA for UART1
		enableDMAReceive();
	}
}

#endif /* INC_RYLRUART_H_ */
