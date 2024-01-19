#include <stdio.h>

#include "NumClass.h"

void check_primes(unsigned int min, unsigned int max)
{
	printf("The Prime numbers are:");
	for (unsigned int i = min; i <= max; ++i)
	{
		if (isPrime(i))
		{
			printf(" %u", i);
		}
	}
	printf("\n");
}

void check_strongs(unsigned int min, unsigned int max)
{
	printf("The Strong numbers are:");
	for (unsigned int i = min; i <= max; ++i)
	{
		if (isStrong(i))
		{
			printf(" %u", i);
		}
	}
	printf("\n");
}

int main(void)
{
	unsigned int min, max;
	scanf("%u %u", &min, &max);
	// check_armstrongs(min, max);
	// check_palindromes(min, max);
	check_primes(min, max);
	check_strongs(min, max);
	return 0;
}
