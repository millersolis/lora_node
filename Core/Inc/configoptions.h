/*
 * configoptions.h
 *
 *  Created on: Mar 17, 2023
 *      Author: Miller Solis
 */

#ifndef INC_CONFIGOPTIONS_H_
#define INC_CONFIGOPTIONS_H_

#include <cstdint>

// Configuration settings available for RYLR module
// Module specs: https://reyax.com/products/rylr896/
// ======================================================================================================

// Default regional lorawan parameters used in the lorawan ns-3 module as well
// https://www.thethingsnetwork.org/docs/lorawan/regional-parameters/
enum class Frequency	// in Hz
{
	EU_1 = 868100000,
	EU_2 = 868300000,
	EU_3 = 868500000,
	// TODO: Add other supported frequencies
};

// Corresponding integers taken from RYLR896 AT command datasheet
enum class Bandwidth	// in Hz
{
	BW_7k8 = 0,
	BW_10k4 = 1,
	BW_15k6 = 2,
	BW_20k8 = 3,
	BW_31k25 = 4,
	BW_41k7 = 5,
	BW_62k5 = 6,
	BW_125k = 7,
	BW_250k = 8,
	BW_500k = 9,
};

enum class SpreadingFactor
{
	SF_7 = 7,
	SF_8 = 8,
	SF_9 = 9,
	SF_10 = 10,
	SF_11 =11,
	SF_12 =12,
};

enum class CodingRate
{
	CR_1 = 1,
	CR_2 = 2,
	CR_3 = 3,
	CR_4 = 4,
};

enum class Preamble
{
	P_4 = 4,
	P_5 = 5,
	P_6 = 6,
	P_7 = 7,
};

enum class BaudRate
{
	BR_300 = 300,
	BR_1200 = 1200,
	BR_4800 = 4800,
	BR_9600 = 9600,
	BR_19200 = 19200,
	BR_28800 = 28800,
	BR_38400 = 38400,
	BR_57600 = 57600,
	BR_115200 = 115200,
};

struct ConfigOptions
{
	// Node address
	// Value from 0 to 65535(default 0 for RYLR)
	// Will be stored in EEPROM
	const char * address = "0";

	// [UNUSED] Newtwork ID
	// Value between 0 and 16
	// Will be stored in EEPROM
	// TODO: Implement functionality to use custom network id
	uint8_t networkId = 0;	// default to public LoRa network id

	// [UNUSED] Network Password (AES128)
	/**
	* Value from  00000000000000000000000000000001
	* to FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
	 */
	// TODO: Implement functionality to use network password
	const char * netPwd = "";	// default is no password

	// Tx Power (RF output power)
	/**
	 * Value from 0dBm to 15dBm.
	 * Must be a two character value i.e. '00' to '15'.
	 * Module default is 15 but typical for SX1276 is 14.
	 * ns-3 lorawan module uses 14.
	 */
	// TODO: Use enum for Tx Power values or add range checking
	const char * txPower = "14";

	// Frequency
	Frequency freq = Frequency::EU_1;

	// Bandwidth
	Bandwidth bw = Bandwidth::BW_125k;	// default for EU

	// Spreading Factor
	SpreadingFactor sf = SpreadingFactor::SF_12;	// default for RYLR

	// Coding Rate
	CodingRate cr = CodingRate::CR_1;	// hard-coded for ns-3 lorawan module

	// Programmed Preamble
	/**
	* The duration of a receive window in number of symbols. This should be
	* converted to time based or the reception parameter used.
	*
	* The downlink preamble transmitted by the gateways contains 7 symbols.
	* The receiver requires 5 symbols to detect the preamble and synchronize.
	* Therefore there must be a 5 symbols overlap between the receive window
	* and the transmitted preamble.
	* (Ref: Recommended SX1272/76 Settings for EU868 LoRaWAN Network Operation )
	 */
	Preamble preamble = Preamble::P_7;

	// [UNUSED] UART Baud Rate
	// Will be stored in EEPROM
	// TODO: Implement functionality to use non-default baud rate.
	BaudRate baudRate = BaudRate::BR_115200;
};

// Return a string representation of the enum value
const char *frequencyToStr(Frequency freq);
const char *bandwidthToStr(Bandwidth bw);
const char *SfToStr(SpreadingFactor sf);
const char *codingRateToStr(CodingRate cr);
const char *preambleToStr(Preamble preamble);
const char *baudRateToStr(BaudRate baudRate);

#endif /* INC_CONFIGOPTIONS_H_ */
