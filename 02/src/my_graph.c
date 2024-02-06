#include <stdio.h>

#include "my_mat.h"

int main(void)
{
	int mat[N][N] = { 0 };
	int quit = FALSE;
	char action;
	size_t src, dst;
	int result;
	do
	{
		if (scanf("%c", &action) == EOF) break;
		switch (action)
		{
		case 'D':
			quit = TRUE;
			break;
		case 'A':
			fill_matrix(mat);
			break;
		case 'B':
			scanf("%zu %zu", &src, &dst);
			result = path_exists(mat, src, dst);
			printf("%s\n", result == TRUE ? "True" : "False");
			break;
		case 'C':
			scanf("%zu %zu", &src, &dst);
			result = shortest_path(mat, src, dst);
			printf("%d\n", result);
			break;
		}
	} while (!quit);
	return 0;
}
