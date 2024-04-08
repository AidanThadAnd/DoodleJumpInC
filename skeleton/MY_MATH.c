#include "MY_MATH.h"

/***********************************************************************
* Name: countDigits
*
* Purpose: Counts the number of digits in a given integer.
*
* Details: If the number is zero, returns 1 since zero has one digit.
*          Otherwise, calculates the number of digits using a custom
*          logarithm base 10 function.
*
* Parameters:
*     - number: The integer for which the number of digits is counted.
* Returns:
*     - int: The number of digits in the given integer.
***********************************************************************/
int countDigits(UINT32 number) {
    if (number == 0)
        return 1;
    return log10_custom(number);
}

/***********************************************************************
* Name: log10_custom
*
* Purpose: Calculates the integer logarithm base 10 of a given number.
*
* Details: Determines the number of digits by finding the largest power
*          of 10 less than or equal to the given number.
*
* Parameters:
*     - x: The number for which the logarithm base 10 is calculated.
* Returns:
*     - int: The integer logarithm base 10 of the given number.
***********************************************************************/
int log10_custom(UINT32 x) {
    int result = 1;
    UINT32 powersOf10[10] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000,
                                 100000000, 1000000000}; 
    if (x < 10)
     return 0;
	while(x >= powersOf10[result-1])
	{
		result++;
	}
    return result-1;
}