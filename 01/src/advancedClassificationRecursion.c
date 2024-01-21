#include "NumClass.h"

unsigned int digit_count(int n)
{
	if (n == 0) return 0;
	return 1 + digit_count(n/RADIX);
}

int power(int b, int e)
{
	if (e == 0) return 1;
	return b*power(b, e-1);
}

int armstrongSum(int n, unsigned int d)
{
	if (n == 0) return 0;
	return power(n%RADIX, d) + armstrongSum(n/RADIX, d);
}

int isArmstrong(int n)
{
	int d = digit_count(n);
	return n == armstrongSum(n, d);
}

int isPalindromeD(int n, unsigned int d)
{
	if (d <= 1) return TRUE;
	int cut = power(RADIX, d-1);
	if (n%RADIX != n/cut) return FALSE;
	return isPalindromeD((n%cut)/RADIX, d - 2);
}

int isPalindrome(int n)
{
	unsigned int d = digit_count(n);
	return isPalindromeD(n, d);
}
