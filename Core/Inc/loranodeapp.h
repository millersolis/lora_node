/*
 * loranodeapp.h
 *
 *  Created on: Mar 17, 2023
 *      Author: Miller Solis
 */

#pragma once

#include "rylrmodule.h"

class LoraNodeApp;
//struct EmSystemSettings;
//struct TempSensorData;

// Return a reference to the single instance of AeonyxApp
LoraNodeApp &getApp();

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
