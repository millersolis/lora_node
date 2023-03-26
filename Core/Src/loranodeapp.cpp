/*
 * loranodeapp.cpp
 *
 *  Created on: Mar 17, 2023
 *      Author: Miller Solis
 */

#include "loranodeapp.h"
#include "rylrmodule.h"
#include "moduleconf.h"
#include "printuart.h"

#include "utils.h"
#include "configoptions.h"

#include "stm32l4xx.h"
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_def.h"

#include "main.h"

//##############################################################################

LoraNodeApp &getApp()
{
    // The constructor of this static instance of loraNodeApp will
    // run only the 1st time this function is called.
    // In this manner, we are able to have a "global" loraNodeApp
    // instance, and also control when its constructor runs.
    static LoraNodeApp app;
    return app;
}

//##############################################################################

LoraNodeApp::LoraNodeApp()
{
	  /* Config only to initialize module, it can be
	   * reconfigured later if needed using RYLRModule
	   *  member functions.
	   */
	  ConfigOptions initialConfig;
	  initialConfig.address = g_address;
	  initialConfig.networkId = g_networkId;
	  initialConfig.netPwd = g_netPwd;
	  initialConfig.txPower = g_txPower;
	  initialConfig.freq = g_freq;
	  initialConfig.bw = g_bw;
	  initialConfig.sf = g_sf;
	  initialConfig.cr = g_cr;
	  initialConfig.preamble = g_preamble;
	  initialConfig.baudRate = g_baudRate;

	  // Initialize module
	  m_loraModule = RYLRModule(initialConfig);
}

void LoraNodeApp::start()
{
	// Wait until module signals it is ready for use.
	m_loraModule.waitReady();

//	m_loraModule.softwareReset();	// TODO: Needed here?
	m_loraModule.setUp();

#ifdef SENDER
	startSender();
#else
	startReceiver();
#endif	// SENDER
}

void LoraNodeApp::startSender()
{
	static int counter = 1;
	bool success;
	while (true){
		char data [digitCount(counter)];
		int len = concatenateIntToArr<char>(data, counter);

		success = m_loraModule.send(g_receiverAddr, len, data);

		if (success) {
			HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
			reportSentPacket(len, data);
		}
		counter++;
	}
}

void LoraNodeApp::startReceiver()
{
	bool success = m_loraModule.startReceive();
	if (success) {
		  HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
	}
}

// Payload length in bytes
void LoraNodeApp::reportSentPacket(int payloadLen, const char* data)
{
	ConfigOptions currentConfig = m_loraModule.getCurrConfig();
	// Format for debugging includes SF.
	// SF: <sf>, SENT: <payload>
	static int messageArrSize = sizeof("SF: ") + sizeof(SFToStr(currentConfig.sf)) + sizeof(", SENT: ") + payloadLen;

	// Build message
	uint8_t message[messageArrSize];
	int len = concatenateStrToArr<uint8_t>(message, "SF: ");
	len += concatenateStrToArr<uint8_t>(message + len, SFToStr(currentConfig.sf));
	len += concatenateStrToArr<uint8_t>(message + len, ", SENT: ");
	len += concatenateStrToArr<uint8_t>(message + len, data);

	print(message, len);
}

