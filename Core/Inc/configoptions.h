/*
 * configoptions.h
 *
 *  Created on: Mar 17, 2023
 *      Author: Miller Solis
 */

#ifndef INC_CONFIGOPTIONS_H_
#define INC_CONFIGOPTIONS_H_

#include <cstdint>


// Default regional lorawan parameters used in the lorawan ns-3 module as well
// https://www.thethingsnetwork.org/docs/lorawan/regional-parameters/
enum class Frequency	// in Hz
{
	EU_1 = 868100000,
	EU_2 = 868300000,
	EU_3 = 868500000,
};

enum class Bandwidth	// in Hz
{
	BW_7k8 = 0,
	BW_10k4 = 1,
	BW_15k6 = 2,
	BW_20k8 = 3,
	BW_31k25 = 4,
	BW_41k7 = 5,
	BW_62k5 = 6,
	BW_125k = 7,
	BW_250k = 8,
	BW_500k = 9
};

enum class SpreadingFactor
{
	SF_7 = 7,
	SF_8 = 8,
	SF_9 = 9,
	SF_10 = 10,
	SF_11 =11,
	SF_12 =12
};

enum class CodingRate
{
	CR_1 = 1,
	CR_2 = 2,
	CR_3 = 3,
	CR_4 = 4
};

enum class Preamble
{
	P_4 = 4,
	P_5 = 5,
	P_6 = 6,
	P_7 = 7
};

struct ConfigOptions
{
	// Node address
	uint32_t m_address;

	// Frequency
	Frequency m_freq = Frequency::EU_1;

	// Bandwidth
	Bandwidth m_bw = Bandwidth::BW_125k;	// default for EU

	// Spreading Factor
	SpreadingFactor m_sf = SpreadingFactor::SF_12;	// default for RYLR

	// Coding Rate
	CodingRate m_cr = CodingRate::CR_1;	// hard-coded for ns-3 lorawan module

	// Programmed Preamble
	/**
	* The duration of a receive window in number of symbols. This should be
	* converted to time based or the reception parameter used.
	*
	* The downlink preamble transmitted by the gateways contains 7 symbols.
	* The receiver requires 5 symbols to detect the preamble and synchronize.
	* Therefore there must be a 5 symbols overlap between the receive window
	* and the transmitted preamble.
	* (Ref: Recommended SX1272/76 Settings for EU868 LoRaWAN Network Operation )
	*/
	Preamble m_preamble = Preamble::P_7;
};


#endif /* INC_CONFIGOPTIONS_H_ */
