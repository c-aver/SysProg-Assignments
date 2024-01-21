#include "NumClass.h"

unsigned int digit_count(int n)
{
	if (n == 0) return 0;			// base case of no digits
	return 1 + digit_count(n/RADIX);	// otherwise 1 + number of digits with one digit removed
}

int power(int b, int e)
{
	if (e == 0) return 1;		// base case of exponent of 0
	return b*power(b, e-1);		// otherwise b*b^(e-1)
}

int armstrongSum(int n, unsigned int d)
{
	if (n == 0) return 0;					// base case of no digits to sum
	return power(n%RADIX, d) + armstrongSum(n/RADIX, d);	// otherwise remove the LSD but add it to the power of the number of digits
}

int isArmstrong(int n)
{
	return n == armstrongSum(n, digit_count(n));	// return whether the number is equal to its armstrong sum
}

int isPalindromeD(int n, unsigned int d)	// this function checks for a palindrome with fixed number of digits
						// this avoids things such as `01` counting as a palindrome because it is technically 1
{
	if (d <= 1) return TRUE;		// if there is only one digit it must be a palindrome
	int cut = power(RADIX, d-1);		// this is the number required to cut the most significant digit out
	if (n%RADIX != n/cut) return FALSE;	// if the LSD and MSD are different the number is not a palindrome
	return isPalindromeD((n%cut)/RADIX, d - 2);	// otherwise, cut out MSD and LSD and check again, with 2 fewer digits
}

int isPalindrome(int n)
{
	return isPalindromeD(n, digit_count(n));	// use helper function isPalindromeD
}
