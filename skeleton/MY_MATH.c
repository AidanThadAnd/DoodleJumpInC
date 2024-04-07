#include "MY_MATH.h"


int countDigits(UINT32 number) {
    if (number == 0)
        return 1;
    return log10_custom(number);
}


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