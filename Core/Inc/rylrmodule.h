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

	// Mode
	enum class Mode
	{
		READY = 0,	// default
		SLEEP = 1
	};
	// TODO: Implement behavior for sleep mode
	// Mode m_mode = Mode::READY;

public:
	// Software reset
	// Will not clean configs stored in EEPROM
	bool softwareReset();

	// Set factory settings
	// Will reset all configs to factory defaults
	// All configs will need to be set again
	bool resetFactorySettings();	//TODO

	//=====================================================================
	// Set configs

	bool setAddress(const char* &addr);
	bool setNetwork(uint8_t &id);		// TODO
	bool setNetworkPwd(char * &pwd);	// TODO
	bool setFrequency(Frequency &freq);
	bool setBaudRate(BaudRate &br);		// TODO

	//---------------------------------------------------------------------
	// Set parameters

	// Sets SF, Bandwidth, Coding rate, Preamble at once
	// All these have to be set at once using a single AT command
	bool setParams();

	bool setSF(SpreadingFactor &sf);
	bool setBandwidth(Bandwidth &bw);
	bool setCodingRate(CodingRate &cr);
	bool setPreamble(Preamble &p);

	//=====================================================================
	// Get module info

	// Module firmware version
	const char* getFwVer();		// TODO

	// Module unique 12-byte ID (UID)
	const char* getUID();		// TODO
};

#endif /* INC_RYLRMODULE_H_ */
