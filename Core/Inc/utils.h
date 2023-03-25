/*
 * utils.h
 *
 *  Created on: Mar 24, 2023
 *      Author: Miller Solis
 */

#ifndef INC_UTILS_H_
#define INC_UTILS_H_

#include <cstdint>

// Copy items form one array to another of different type.
// Returns number of copied elements.
template <typename T, typename D>
inline int concatenateToArr(T* arr1, D* arr2, int len)
{
	int i = 0;
	for (; i < len; i++)
		arr1[i] = static_cast<T> (arr2[i]);

	return i;
}

// Copy cstring terminated on '\0' to an array of type T.
// Returns number of copied elements.
template <typename T>
inline int concatenateStrToArr(T* arr, const char* str)
{
	int i = 0;
	for (; str[i] != '\0'; i++)
		arr[i] = static_cast<T> (str[i]);

	return i;
}

// Copy char representation of an integer to an array of type T.
// Returns number of copied elements
template <typename T>
inline int concatenateIntToArr(T* arr, int num)
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

// Count how many digits an integer has
inline int digitCount(int num)
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
