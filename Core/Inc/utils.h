/*
 * utils.h
 *
 *  Created on: Mar 24, 2023
 *      Author: Miller Solis
 */

#ifndef INC_UTILS_H_
#define INC_UTILS_H_

#include "printuart.h"

#include <cstdint>

// Concatenate cstring terminated on '\0' to an array of type T.
// Returns number of concatenated elements.
template <typename T>
int concatenateToArr(T* arr, const char* str)
{
	int i = 0;
	for (; str[i] != '\0'; i++)
		arr[i] = static_cast<T> (str[i]);

//	uint8_t debug[] = "DEGUG: Concatenate cstring to array success.";
//	print(debug, sizeof(debug));

	return i;
}

#endif /* INC_UTILS_H_ */
