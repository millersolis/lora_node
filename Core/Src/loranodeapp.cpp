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
	m_loraModule.send();
}

void LoraNodeApp::startReceiver()
{
	m_loraModule.receive();
}
