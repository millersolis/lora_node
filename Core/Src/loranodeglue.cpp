/*
 * loranodeglue.cpp
 *
 *  Created on: Mar 17, 2023
 *      Author: Miller Solis
 */

#include "loranodeglue.h"
#include "loranodeapp.h"

extern "C"
void loraNodeAppInit()
{
    // Force construction of the loraNodeApp instance
    (void)getApp();
}

extern "C"
void loraNodeAppStart()
{
    getApp().start();
}

extern "C"
void enableDMARcvUART1()
{
	enableRYRLDMAReceive();
}
