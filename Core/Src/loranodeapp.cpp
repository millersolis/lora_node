/*
 * loranodeapp.cpp
 *
 *  Created on: Mar 17, 2023
 *      Author: Miller Solis
 */

#include "loranodeapp.h"
#include "rylrmodule.h"
#include "moduleconf.h"

//#include <cstring>
//#include <cinttypes>

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
	  initialConfig.m_address = g_address;
	  initialConfig.m_networkId = g_networkId;
	  initialConfig.m_netPwd = g_netPwd;
	  initialConfig.m_txPower = g_txPower;
	  initialConfig.m_freq = g_freq;
	  initialConfig.m_bw = g_bw;
	  initialConfig.m_sf = g_sf;
	  initialConfig.m_cr = g_cr;
	  initialConfig.m_preamble = g_preamble;
	  initialConfig.m_baudRate = g_baudRate;

	  // Initialize module
	  m_loraModule = RYLRModule(initialConfig);
}

void LoraNodeApp::start()
{
	m_loraModule.softwareReset();
}

