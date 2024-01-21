#include "NumClass.h"

unsigned int digit_count(int n)
{
	unsigned int result = 0;
	while (n > 0)
	{
		result += 1;
		n /= RADIX;
	}
	return result;
}

int power(int b, int e)
{
	int result = 1;
	while (e > 0)
	{
		result *= b;
		e -= 1;
	}
	return result;
}

int isArmstrong(int n)
{
	unsigned int d = digit_count(n);
	int sum = 0, orig_n = n;
	while (n > 0)
	{
		sum += power(n%RADIX, d);
		n /= RADIX;
	}
	return sum == orig_n;
}

unsigned int get_digit(int n, unsigned int i)
{
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
