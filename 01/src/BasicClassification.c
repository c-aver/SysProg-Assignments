#include "NumClass.h"

int isPrime(unsigned int n)
{
	if (n == 0) return FALSE;			// by definition, by assignment definition 1 IS prime
	for (unsigned int i = 2; i*i <= n; ++i)		// run through all number up to sqrt(n)
	{
		if (n % i == 0) return FALSE;		// if the number divides n it is not prime
	}
	return TRUE;
}

unsigned int factorial(unsigned int n)
{
	unsigned int result = 1;
	for (unsigned int i = 2; i <= n; ++i)
	{
		result *= i;
	}
	return result;
}

int isStrong(unsigned int n)
{
	unsigned int orig_n = n;
	unsigned int sum = 0;
	while (n > 0)
	{
		int d = n % RADIX;
		sum += factorial(d);
		n /= RADIX;
	}
	return sum == orig_n;
}
