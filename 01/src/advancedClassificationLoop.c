#include "NumClass.h"

unsigned int digit_count(int n)
{
	unsigned int result = 0;
	while (n > 0)		// as long as digits remain
	{
		result += 1;	// increment number of digits
		n /= RADIX;	// remove the least significant digit
	}
	return result;
}

int power(int b, int e)
{
	int result = 1;		// initialize the result as 1
	while (e > 0)		// as long as exponent is positive
	{
		result *= b;	// multiply by base
		e -= 1;		// decrement exponent
	}
	return result;
}

int isArmstrong(int n)
{
	unsigned int d = digit_count(n);	// fing number of digits
	int sum = 0, orig_n = n;
	while (n > 0)				// as long as digits remain
	{
		sum += power(n%RADIX, d);	// add to the sum the least significant digit to power of the number of digits
		n /= RADIX;			// remove the LSD
	}
	return sum == orig_n;			// return whether the sum of the powers is equal to the original number
}

unsigned int get_digit(int n, unsigned int i)
{
	// divide by radix to the power of number of digits to remove (removes `i` digits) then divide to take the LSD of what's left
	return (n / power(RADIX, i)) % RADIX;
}

int isPalindrome(int n)
{
	unsigned int d = digit_count(n);
	for (unsigned int i = 0; i <= d/2; ++i)
	{
		if (get_digit(n, i) != get_digit(n, (unsigned int) d - i - 1)) return FALSE;
	}
	return TRUE;
}
