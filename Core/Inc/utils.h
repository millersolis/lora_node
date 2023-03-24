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
int concatenateStrToArr(T* arr, const char* str)
{
	int i = 0;
	for (; str[i] != '\0'; i++)
		arr[i] = static_cast<T> (str[i]);

//	uint8_t debug[] = "DEGUG: Concatenate cstring to array success.";
//	print(debug, sizeof(debug));

	return i;
}

// Concatenate integer to an array of type T.
// Returns number of concatenated elements
template <typename T>
int concatenateIntToArr(T* arr, int num)
{
	// handle negative numbers
	if (num < 0) {
		return 0;
	}

	// convert digits to characters in reverse order
	int i = 0;
	do {
	    arr[i] = static_cast<T> (num % 10 + '0');
	    num /= 10;
	    i++;
	} while (num != 0);

	// reverse the string in place
	int j = 0;
	int k = i - 1;
	while (j < k) {
	    T tmp = arr[j];
	    arr[j] = arr[k];
	    arr[k] = tmp;
	    j++;
	    k--;
	}

	return i;
}

int digitCount(int num)
{
	// handle negative numbers
	if (num < 0) {
		return 0;
	}

	int i = 0;
	do {
		num /= 10;
		i++;
	} while (num != 0);

	return i;
}

#endif /* INC_UTILS_H_ */
