#include <stdio.h>

#include "NumClass.h"

void print_armstrongs(unsigned int min, unsigned int max)
{
	printf("The Armstrong numbers are:");
	for (unsigned int i = min; i <= max; ++i)
	{
		if (isArmstrong(i))
		{
			printf(" %u", i);
		}
	}
	printf("\n");
}

void print_palindromes(unsigned int min, unsigned int max)
{
	printf("The Palindromes are:");
	for (unsigned int i = min; i <= max; ++i)
	{
		if (isPalindrome(i))
		{
			printf(" %u", i);
		}
	}
	printf("\n");
}

void print_primes(unsigned int min, unsigned int max)
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

void print_strongs(unsigned int min, unsigned int max)
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
	print_armstrongs(min, max);
	print_palindromes(min, max);
	print_primes(min, max);
	print_strongs(min, max);
	return 0;
}
