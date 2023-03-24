/*
 * rylrmodule.cpp
 *
 *  Created on: Mar 20, 2023
 *      Author: Miller Solis
 */

#include "rylrmodule.h"
#include "rylruart.h"
#include "atcommands.h"
#include "utils.h"

#include "stm32l4xx_hal.h"

//#include <cstring>
//#include <cinttypes>

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
	return uartTransmit(command, sizeof(command));
}

bool RYLRModule::setUp()
{
	setAddress(m_config.address);

	return true;
}

bool RYLRModule::send()
{
	return true;
}

bool RYLRModule::setAddress(const char* &addr)
{
	constexpr int commandArrSize = sizeof(AT_ADDRESS) + MAX_ADDRESS_LEN + sizeof(TERMINATION);

	// Build command
	uint8_t command[commandArrSize];

	int len = concatenateToArr<uint8_t>(command, AT_ADDRESS);
	len += concatenateToArr<uint8_t>(command + len, addr);
	len += concatenateToArr<uint8_t>(command + len, TERMINATION);

	return uartTransmit(command, len);
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
	return uartTransmit(command, sizeof(command));
}
