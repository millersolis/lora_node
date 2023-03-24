/*
 * rylrmodule.cpp
 *
 *  Created on: Mar 20, 2023
 *      Author: Miller Solis
 */

#include "rylrmodule.h"
#include "rylruart.h"
#include "atcommands.h"

#include "printuart.h"
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
	bool success = setAddress(m_config.address);
	success = success && setTxPower(m_config.txPower);

	if (success) {
		uint8_t debug[] = "DEGUG: RYLRModule setup success.";
		print(debug, sizeof(debug));
	}
	else {
		uint8_t debug[] = "DEGUG: ERROR - RYLRModule setup failure.";
		print(debug, sizeof(debug));
		// Spin lock, hard fault
		while (true) {}
	}

	return success;
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

	bool success = uartTransmit(command, len);

	// FIXME: Poll for response from module "+OK" or "+ERROR" from UART instead.
	HAL_Delay(DELAY_AFTER_AT);

	if (!success) {
		uint8_t debug[] = "DEGUG: ERROR - RYLRModule setup address failure.";
		print(debug, sizeof(debug));
		// Spin lock, hard fault
		while (true) {}
	}

	return success;
}

bool RYLRModule::setTxPower(const char * &pwr)
{
	constexpr int commandArrSize = sizeof(AT_CRFOP) + MAX_TXPOWER_LEN + sizeof(TERMINATION);

	// Build command
	uint8_t command[commandArrSize];

	// TODO: Check tx power range beforehand.
	int len = concatenateToArr<uint8_t>(command, AT_CRFOP);
	len += concatenateToArr<uint8_t>(command + len, pwr);
	len += concatenateToArr<uint8_t>(command + len, TERMINATION);

	bool success = uartTransmit(command, len);

	// FIXME: Poll for response from module "+OK" or "+ERROR" from UART instead.
	HAL_Delay(DELAY_AFTER_AT);

	if (!success) {
		uint8_t debug[] = "DEGUG: ERROR - RYLRModule setup tx (output) power failure.";
		print(debug, sizeof(debug));
		// Spin lock, hard fault
		while (true) {}
	}

	return success;
}

bool RYLRModule::setFrequency(Frequency &freq)
{
	return true;
}

bool RYLRModule::setParams()
{
	uint8_t command[] = "AT+RESET\r\n";
	bool success = uartTransmit(command, sizeof(command));

	// FIXME: Poll for response from module "+OK" or "+ERROR" from UART instead.
	HAL_Delay(DELAY_AFTER_AT);

	if (!success) {
		uint8_t debug[] = "DEGUG: ERROR - RYLRModule software reset failure.";
		print(debug, sizeof(debug));
		// Spin lock, hard fault
		while (true) {}
	}

	return success;
}
