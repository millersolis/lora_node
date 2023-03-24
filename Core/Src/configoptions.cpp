/*
 * configoptions.cpp
 *
 *  Created on: Mar 20, 2023
 *      Author: Miller Solis
 */

#include "configoptions.h"

const char *frequencyToStr(Frequency freq)
{
	switch (freq) {
	case Frequency::EU_1: 	return "868100000";
	case Frequency::EU_2: 	return "868300000";
	case Frequency::EU_3: 	return "868500000";

	default: 				return nullptr;
	}
}

const char *bandwidthToStr(Bandwidth bw)
{
	switch (bw) {
	case Bandwidth::BW_7k8:		return "0";
	case Bandwidth::BW_10k4:	return "1";
	case Bandwidth::BW_15k6:	return "2";
	case Bandwidth::BW_20k8:	return "3";
	case Bandwidth::BW_31k25:	return "4";
	case Bandwidth::BW_41k7:	return "5";
	case Bandwidth::BW_62k5:	return "6";
	case Bandwidth::BW_125k:	return "7";
	case Bandwidth::BW_250k:	return "8";
	case Bandwidth::BW_500k:	return "9";

	default: 					return nullptr;
	}
}

const char *SFToStr(SpreadingFactor sf)
{
	switch (sf) {
	case SpreadingFactor::SF_7:		return "7";
	case SpreadingFactor::SF_8:		return "8";
	case SpreadingFactor::SF_9:		return "9";
	case SpreadingFactor::SF_10:	return "10";
	case SpreadingFactor::SF_11:	return "11";
	case SpreadingFactor::SF_12:	return "12";

	default: 						return nullptr;
	}
}

const char *codingRateToStr(CodingRate cr)
{
	switch (cr) {
	case CodingRate::CR_1:		return "1";
	case CodingRate::CR_2:		return "2";
	case CodingRate::CR_3:		return "3";
	case CodingRate::CR_4:		return "4";

	default: 					return nullptr;
	}
}

const char *preambleToStr(Preamble preamble)
{
	switch (preamble) {
	case Preamble::P_4:		return "4";
	case Preamble::P_5:		return "5";
	case Preamble::P_6:		return "6";
	case Preamble::P_7:		return "7";

	default: 				return nullptr;
	}
}

const char *baudRateToStr(BaudRate baudRate)
{
	switch (baudRate) {
	case BaudRate::BR_300:			return "300";
	case BaudRate::BR_1200:			return "1200";
	case BaudRate::BR_4800:			return "4800";
	case BaudRate::BR_9600:			return "9600";
	case BaudRate::BR_19200:		return "19200";
	case BaudRate::BR_28800:		return "28800";
	case BaudRate::BR_38400:		return "38400";
	case BaudRate::BR_57600:		return "57600";
	case BaudRate::BR_115200:		return "115200";

	default: 						return nullptr;
	}
}
