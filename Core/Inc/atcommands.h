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
#define AT_ADDRESS "AT+ADDRESS="
#define AT_CRFOP	"AT+CRFOP="		// Tx Power = Output Power

// Command Ending
#define TERMINATION "\r\n"

// Max param length
#define MAX_ADDRESS_LEN 5
#define MAX_TXPOWER_LEN 2			// Tx Power = Output Power

// Delay
// FIXME: Poll for response from module "+OK" or "+ERROR" from UART instead.
#define DELAY_AFTER_AT 1000

#endif /* INC_ATCOMMANDS_H_ */
