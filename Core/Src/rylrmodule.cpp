/*
 * rylrmodule.cpp
 *
 *  Created on: Mar 20, 2023
 *      Author: Miller Solis
 */

#include "rylrmodule.h"

#include "stm32l4xx.h"
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_def.h"

// defined in auto-generated main.c
extern UART_HandleTypeDef huart1;

RYLRModule::RYLRModule()
{
}

RYLRModule::RYLRModule(ConfigOptions &config) :
		m_config(config)
{
}

RYLRModule::~RYLRModule()
{
}

bool RYLRModule::softwareReset()
{
	uint8_t command[] = "AT+RESET\r\n";
	HAL_UART_Transmit(&huart1, command, sizeof(command), 1000);
	return true;
}
