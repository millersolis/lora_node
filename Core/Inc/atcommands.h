/*
 * atcommands.h
 *
 *  Created on: Mar 24, 2023
 *      Author: Miller Solis
 */

#ifndef INC_ATCOMMANDS_H_
#define INC_ATCOMMANDS_H_
// Configuration settings available for RYLR module
// Module specs: https://reyax.com/products/rylr896/


// Commands
#define AT_RESET				"AT+RESET"
#define AT_ADDRESS				"AT+ADDRESS="
#define AT_CRFOP				"AT+CRFOP="			// Tx Power = Output Power
#define AT_BAND					"AT+BAND="			// Frequency
#define AT_PARAMETER			"AT+PARAMETER="		// AT+PARAMETER=<SF>,<Bandwidth>,<Coding Rate>,<Preamble>
#define AT_SEND					"AT+SEND="			// AT+SEND=<Address>,<Payload Length>,<Data>

// Parameter Separator
#define PARAM_SEPARATOR			","

// Command Ending
#define TERMINATION				"\r\n"

// Param length
#define MAX_ADDRESS_LEN 		5
#define MAX_TXPOWER_LEN 		2			// Tx Power = Output Power
#define MAX_SF_LEN				2
#define MAX_PAYLOAD_LEN			254			// in bytes
#define FREQUENCY_LEN 			9			// Fixed length for frequency
#define BANDWIDTH_LEN			1			// Digit
#define CODINGRATE_LEN			1			// Digit
#define PREAMBLE_LEN			1			// Digit

// Delay
// FIXME: Poll for response from module "+OK" or "+ERROR" from UART instead.
#define DELAY_AFTER_AT 			1000
#define DELAY_AFTER_RESET		3000

#endif /* INC_ATCOMMANDS_H_ */
