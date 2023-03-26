/*
 * loranodeapp.h
 *
 *  Created on: Mar 17, 2023
 *      Author: Miller Solis
 */

#ifndef INC_LORANODEAPP_H_
#define INC_LORANODEAPP_H_

#include "rylrmodule.h"

class LoraNodeApp;
//struct EmSystemSettings;
//struct TempSensorData;

// Return a reference to the single instance of AeonyxApp
LoraNodeApp &getApp();

void enableRYRLDMAReceive();

class LoraNodeApp
{
public:
    LoraNodeApp();

    // This function is called at startup
    void start();

private:
    void startSender();
    void startReceiver();

    void reportSentPacket(int payloadLen, const char* data);

    RYLRModule m_loraModule;
};

#endif 	//INC_LORANODEAPP_H_
