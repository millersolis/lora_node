/*
 * moduleconf.h
 *
 *  Created on: Mar 20, 2023
 *      Author: Miller Solis
 */
// Contains constants to be used for the lora module
// Defined on this file for ease of use

#ifndef INC_MODULECONF_H_
#define INC_MODULECONF_H_

// For data collection requirements, a module can be either a sender or a receiver
// ==============================================================================
//#define SENDER	// comment out to signal the module is receiver

#include "configoptions.h"


struct DefaultConfig {
	// Node address
	// Value from 0 to 65535(default 0 for RYLR)
	// Will be stored in EEPROM

	inline static const char * g_senderAddr = "1";
	inline static const char * g_receiverAddr = "2";

	#ifdef SENDER
	inline static const char * g_address = g_senderAddr;
	#else
	inline static const char * g_address = g_receiverAddr;
	#endif	/* SENDER */

	// [UNUSED] Newtwork ID
	// Value between 0 and 16
	// Will be stored in EEPROM
	// TODO: Implement functionality to use custom network id
	static const uint8_t g_networkId = 0;	// default to public LoRa network id

	// [UNUSED] Network Password (AES128)
	/**
	* Value from  00000000000000000000000000000001
	* to FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
	 */
	// TODO: Implement functionality to use network password
	inline static const char * g_netPwd = "";	// default is no password

	// Tx Power (RF output power)
	/**
	 * Value from 0dBm to 15dBm.
	 * Must be a two character value i.e. '00' to '15'.
	 * Module default is 15 but typical for SX1276 is 14.
	 * ns-3 lorawan module uses 14.
	 */
	inline static const char * g_txPower = "14";

	// Frequency
	static const Frequency g_freq = Frequency::EU_1;

	// Bandwidth
	static const Bandwidth g_bw = Bandwidth::BW_125k;	// default for EU

	// Spreading Factor
	static const SpreadingFactor g_sf = SpreadingFactor::SF_12;	// default for RYLR

	// Coding Rate
	static const CodingRate g_cr = CodingRate::CR_1;	// hard-coded for ns-3 lorawan module

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
	static const Preamble g_preamble = Preamble::P_7;

	// [UNUSED] UART Baud Rate
	/* Will be stored in EEPROM.
	 * Has to be the default to communicate with the module
	 * at the very beginning.
	 */
	// TODO: Initialize with baud rate directly from huart1
	// TODO: Implement functionality to use non-default baud rate.
	static const BaudRate g_baudRate = BaudRate::BR_115200;
};

#endif		//INC_MODULECONF_H_
