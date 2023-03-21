/*
 * loranodeglue.h
 *
 *  Created on: Mar 17, 2023
 *      Author: Miller Solis
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// Ensure the loraNodeApp constructor is called
void loraNodeAppInit();

// To be called from main() to start the C++ application code
void loraNodeAppStart();

#ifdef __cplusplus
} // extern "C"
#endif
