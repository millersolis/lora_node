/*
 * rylrmodule.cpp
 *
 *  Created on: Mar 20, 2023
 *      Author: Miller Solis
 */

#include "rylrmodule.h"
#include "rylruart.h"

#include "stm32l4xx.h"
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_def.h"

//#include <cstring>
//#include <cinttypes>

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

bool RYLRModule::waitReady()
{
	// Delay to allow module to power up.
	// FIXME: Wait for incoming "+READY" command from module instead.
	// FIXME: Remove use of HAL from this class directly.
	HAL_Delay(100);

	return true;
}

bool RYLRModule::softwareReset()
{
	uint8_t command[] = "AT+RESET\r\n";
	HAL_UART_Transmit(&huart1, command, sizeof(command), 1000);
	return true;
}

bool RYLRModule::setUp()
{
	setAddress(m_config.m_address);

	return true;
}

bool RYLRModule::startSend()
{
	return true;
}

bool RYLRModule::setAddress(const char* &addr)
{
	constexpr int commandLen = 11;
	constexpr int maxAddressChar = 5;
	constexpr int commandEndLen = 2;

	constexpr int commandArrSize = commandLen + maxAddressChar + commandEndLen;
	uint8_t command[commandArrSize] = {'A','T','+','A','D','D','R','E','S','S','='};

	// Build command
	int offset = commandLen;

	// Append address
	int i = 0;
	for (; addr[i] != '\0'; i++)
	{
		command[offset + i] = (uint8_t) addr[i];
	}

	offset += i;
	// Append command ending
	command[offset + 1] = (uint8_t) '\r';
	command[offset + 2] = (uint8_t) '\n';

	int commandSize = offset + commandEndLen + 1;

	HAL_UART_Transmit(&huart1, command, commandSize, 1000);
	return true;
}

bool RYLRModule::setTxPower(const char * &pwr)
{
	return true;
}

bool RYLRModule::setFrequency(Frequency &freq)
{
	return true;
}

bool RYLRModule::setParams()
{
	uint8_t command[] = "AT+RESET\r\n";
	HAL_UART_Transmit(&huart1, command, sizeof(command), 1000);
	return true;
}
