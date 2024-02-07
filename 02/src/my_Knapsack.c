#include <stdio.h>

#define TRUE 1
#define FALSE 0

#define C 20	// knapsack capacity
#define N 5		// total number of items
#define STR_MAX_LEN (20 + 1)	// 20 for string plus 1 for null terminator

void input_items(char names[N][STR_MAX_LEN], int values[N], int weights[N])
{
	for (size_t i = 0; i < N; ++i)
	{
		scanf("%s %d %d", names[i], &values[i], &weights[i]);
	}
}

int max(const int a, const int b)
{
	return a > b ? a : b;
}

// first part ported from https://en.wikipedia.org/wiki/Knapsack_problem#0-1_knapsack_problem
int knapSack(const int weights[N], const int values[N], int selected_bool[N])
{
	int dp[N+1][C+1];
	for (size_t c = 0; c <= C; ++c) dp[0][c] = 0;
	for (size_t n = 1; n <= N; ++n) dp[n][0] = 0;
	for (size_t n = 1; n <= N; ++n)
	{
		for (size_t c = 1; c <= C; ++c)
		{
			if ((unsigned int) weights[n-1] > c) dp[n][c] = dp[n-1][c];
			else dp[n][c] = max(dp[n-1][c], dp[n-1][c-weights[n-1]] + values[n-1]);
		}
	}

	int result = dp[N][C];
	
	// from here on algorithm is not ported from Wikipedia but from me
	size_t w = C;	// the current weight of the optimal solution
	
	for (size_t n = N; n > 0; --n)	// run backwards through the items to reconstruct solution
	{
		if (w < (unsigned int) weights[n-1] || dp[n][w] == dp[n-1][w])	// check which option was taken
			selected_bool[n-1] = FALSE;	// the item was not taken
		else
		{
			selected_bool[n-1] = TRUE;	// the item was taken
			w -= weights[n-1];			// decreaes the remaining weight in the solution
		}
	}

	return result;
}

int main(void)
{
	int weights[N], values[N];
	char names[N][STR_MAX_LEN];
	input_items(names, values, weights);
	int selected_bool[N];
	int selected_value = knapSack(weights, values, selected_bool);
	printf("Maximum profit: %d\n", selected_value);
	printf("Selected items:");
	for (size_t i = 0; i < N; ++i)
	{
		if (selected_bool[i]) printf(" %s", names[i]);
	}
}
