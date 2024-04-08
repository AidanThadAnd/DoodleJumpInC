/*
Author: Aidan & Jacky
Date: March 15, 2024

Purpose:
    - Defines functions for mathematical operations related to integer digits and logarithms.

Functions:
    Function Name: countDigits
        Purpose:
            - Counts the number of digits in a given integer.
        Details:
            - If the number is zero, returns 1 since zero has one digit. Otherwise, calculates the number of digits using a custom logarithm base 10 function.
        Parameters:
            - number: The integer for which the number of digits is counted.
        Returns:
            - int: The number of digits in the given integer.

    Function Name: log10_custom
        Purpose:
            - Calculates the integer logarithm base 10 of a given number.
        Details:
            - Determines the number of digits by finding the largest power of 10 less than or equal to the given number.
        Parameters:
            - x: The number for which the logarithm base 10 is calculated.
        Returns:
            - int: The integer logarithm base 10 of the given number.
*/
#ifndef MY_MATH_H
#define MY_MATH_H

#include "types.h"

int log10_custom(UINT32 x);
int countDigits(UINT32 number);

#endif