/*
 * rylrmodule.h
 *
 *  Created on: Mar 17, 2023
 *      Author: Miller Solis
 */

#ifndef INC_RYLRMODULE_H_
#define INC_RYLRMODULE_H_

#include "configoptions.h"

// Module specs: https://reyax.com/products/rylr896/
class RYLRModule
{
public:
	RYLRModule();
	RYLRModule(ConfigOptions &config);
	~RYLRModule();

private:
	// Config
	ConfigOptions m_config;

	// [UNUSED] Mode
	// TODO: Implement behavior for sleep mode
	enum class Mode
	{
		READY = 0,	// default
		SLEEP = 1
	};
	 Mode m_mode = Mode::READY;

public:
	// Wait until "+READY" command from module.
	bool waitReady();

	// Software reset
	// Will not clean configs stored in EEPROM.
	bool softwareReset();

	// Applies all configs to the module through UART AT commands.
	bool setUp();

	// TODO: Allow non-blocking send in the future.
	bool send(const char* destAddress, int payloadLen, char* data);
	bool startReceive();

	// Set factory settings
	// Will reset all configs to factory defaults
	// All configs will need to be set again
	bool resetFactorySettings();	//TODO

	const ConfigOptions getCurrConfig();

	// TODO: Implement functions to change config and params from the initial.
	//=====================================================================
	// Set configs

	bool setAddress(const char* &addr);
	bool setTxPower(const char* &pwr);
	bool setNetwork(uint8_t &id);		// TODO
	bool setNetworkPwd(char * &pwd);	// TODO
	bool setFrequency(Frequency &freq);
	bool setBaudRate(BaudRate &br);		// TODO

	//---------------------------------------------------------------------
	// Set parameters

	bool setSF(SpreadingFactor &sf);	// TODO: Implement and call setParams()
	bool setBandwidth(Bandwidth &bw);	// TODO: Implement and call setParams()
	bool setCodingRate(CodingRate &cr);	// TODO: Implement and call setParams()
	bool setPreamble(Preamble &p);		// TODO: Implement and call setParams()

	// Sets SF, Bandwidth, Coding rate, Preamble from m_config. All at once.
	// All these have to be set using a single AT command.
	bool setParams();

	//=====================================================================
	// Get module info

	// Module firmware version
	const char* getFwVer();		// TODO

	// Module unique 12-byte ID (UID)
	const char* getUID();		// TODO

	// TODO: Implement functions that query the module for bits of config
	//       by using AT commands ending in '?'
};

#endif /* INC_RYLRMODULE_H_ */
