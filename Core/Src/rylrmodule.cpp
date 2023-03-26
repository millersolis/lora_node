/*
 * rylrmodule.cpp
 *
 *  Created on: Mar 20, 2023
 *      Author: Miller Solis
 */

#include "rylrmodule.h"
#include "configoptions.h"
#include "rylruart.h"
#include "rylrdma.h"
#include "atcommands.h"

#include "printuart.h"
#include "utils.h"

#include "stm32l4xx_hal.h"

//#include <cinttypes>

bool startReceive()
{
	return enableDMAReceive();
}

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
	HAL_Delay(150);

	return true;
}

bool RYLRModule::softwareReset()
{
	constexpr int commandArrSize = sizeof(AT_RESET) + sizeof(TERMINATION);

	// Build command
	uint8_t command[commandArrSize];
	int len = concatenateStrToArr<uint8_t>(command, AT_RESET);
	len += concatenateStrToArr<uint8_t>(command + len, TERMINATION);
	bool success = uartTransmit(command, len);

	// FIXME: Poll for response from module "+OK" or "+ERROR" from UART instead.
	HAL_Delay(DELAY_AFTER_RESET);

	if (!success) {
		uint8_t debug[] = "DEGUG: ERROR - RYLRModule software reset failure.";
		print(debug, sizeof(debug));
		// Spin lock, hard fault
		while (true) {}
	}

	return success;
}

bool RYLRModule::setUp()
{
	bool success = setAddress(m_config.address);
	success = success && setTxPower(m_config.txPower);
	success = success && setFrequency(m_config.freq);
	success = success && setParams();

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

// Payload length in bytes
bool RYLRModule::send(const char* destAddr, int payloadLen, char* data)
{
	if (payloadLen > MAX_PAYLOAD_LEN) {
		uint8_t debug[] = "DEGUG: WARNING - Max payload size exceeded, ignoring overrun.";
		print(debug, sizeof(debug));
		payloadLen = MAX_PAYLOAD_LEN;
	}
	int commandArrSize = sizeof(AT_SEND) + sizeof(destAddr) +  sizeof(PARAM_SEPARATOR) +
							digitCount(payloadLen) + sizeof(PARAM_SEPARATOR)+ payloadLen + sizeof(TERMINATION);

	// Build command
	uint8_t command[commandArrSize];
	int len = concatenateStrToArr<uint8_t>(command, AT_SEND);
	len += concatenateStrToArr<uint8_t>(command + len, destAddr);
	len += concatenateStrToArr<uint8_t>(command + len, PARAM_SEPARATOR);
	len += concatenateIntToArr<uint8_t>(command + len, payloadLen);
	len += concatenateStrToArr<uint8_t>(command + len, PARAM_SEPARATOR);
	len += concatenateToArr<uint8_t, char>(command + len, data, payloadLen);
	len += concatenateStrToArr<uint8_t>(command + len, TERMINATION);

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

const ConfigOptions RYLRModule::getCurrConfig()
{
	return m_config;
}

bool RYLRModule::setAddress(const char* &addr)
{
	constexpr int commandArrSize = sizeof(AT_ADDRESS) + MAX_ADDRESS_LEN + sizeof(TERMINATION);

	// Build command
	uint8_t command[commandArrSize];
	int len = concatenateStrToArr<uint8_t>(command, AT_ADDRESS);
	len += concatenateStrToArr<uint8_t>(command + len, addr);
	len += concatenateStrToArr<uint8_t>(command + len, TERMINATION);

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
	int len = concatenateStrToArr<uint8_t>(command, AT_CRFOP);
	len += concatenateStrToArr<uint8_t>(command + len, pwr);
	len += concatenateStrToArr<uint8_t>(command + len, TERMINATION);

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
	constexpr int commandArrSize = sizeof(AT_BAND) + FREQUENCY_LEN + sizeof(TERMINATION);

	// Build command
	uint8_t command[commandArrSize];
	// TODO: Check tx power range beforehand.
	int len = concatenateStrToArr<uint8_t>(command, AT_BAND);
	len += concatenateStrToArr<uint8_t>(command + len, frequencyToStr(freq));
	len += concatenateStrToArr<uint8_t>(command + len, TERMINATION);

	bool success = uartTransmit(command, len);

	// FIXME: Poll for response from module "+OK" or "+ERROR" from UART instead.
	HAL_Delay(DELAY_AFTER_AT);

	if (!success) {
		uint8_t debug[] = "DEGUG: ERROR - RYLRModule setup frequency (band) failure.";
		print(debug, sizeof(debug));
		// Spin lock, hard fault
		while (true) {}
	}

	return success;
}

// Sets SF, Bandwidth, Coding rate, Preamble from m_config. All at once.
// All these have to be set using a single AT command.
bool RYLRModule::setParams()
{
	constexpr int commandArrSize = sizeof(AT_PARAMETER) + MAX_SF_LEN + sizeof(PARAM_SEPARATOR) +
									BANDWIDTH_LEN + sizeof(PARAM_SEPARATOR) + CODINGRATE_LEN +
									PREAMBLE_LEN + sizeof(TERMINATION);
	// Build command
	uint8_t command[commandArrSize];
	// TODO: Check tx power range beforehand.
	int len = concatenateStrToArr<uint8_t>(command, AT_PARAMETER);
	len += concatenateStrToArr<uint8_t>(command + len, SFToStr(m_config.sf));
	len += concatenateStrToArr<uint8_t>(command + len, PARAM_SEPARATOR);
	len += concatenateStrToArr<uint8_t>(command + len, bandwidthToStr(m_config.bw));
	len += concatenateStrToArr<uint8_t>(command + len, PARAM_SEPARATOR);
	len += concatenateStrToArr<uint8_t>(command + len, codingRateToStr(m_config.cr));
	len += concatenateStrToArr<uint8_t>(command + len, PARAM_SEPARATOR);
	len += concatenateStrToArr<uint8_t>(command + len, preambleToStr(m_config.preamble));
	len += concatenateStrToArr<uint8_t>(command + len, TERMINATION);

	bool success = uartTransmit(command, len);

	// FIXME: Poll for response from module "+OK" or "+ERROR" from UART instead.
	HAL_Delay(DELAY_AFTER_AT);

	if (!success) {
		uint8_t debug[] = "DEGUG: ERROR - RYLRModule setup parameters (SF,bandwidth,codingRate,preamble) failure.";
		print(debug, sizeof(debug));
		// Spin lock, hard fault
		while (true) {}
	}

	return success;
}
