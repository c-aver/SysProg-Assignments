#include "NumClass.h"

int isPrime(int n)
{
	if (n == 0) return FALSE;		// by assignment definition 1 IS prime
	for (int i = 2; i*i <= n; ++i)		// run through all numbers up to and including sqrt(n)
	{
		if (n % i == 0) return FALSE;	// if the number divides n it is not prime
	}
	return TRUE;				// if none of them divide n it is prime
}

unsigned int factorial(int n)
{
	unsigned int result = 1;
	for (int i = 2; i <= n; ++i)
	{
		result *= i;			// multiply be each number from 2 to n
	}
	return result;
}

int isStrong(int n)
{
	unsigned int orig_n = n;	// save the original number for comparison at the end
	unsigned int sum = 0;		// the sum of digits' factorials
	while (n > 0)			// run as long as there are digits left
	{
		int d = n % RADIX;	// the least significant digit
		sum += factorial(d);	// add its factorial to the sum
		n /= RADIX;		// divide the number to remove the used digit
	}
	return sum == orig_n;		// return whether the sum is the original number
}
