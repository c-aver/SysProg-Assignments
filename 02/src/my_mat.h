#include <stddef.h>

#define N 10
#define FALSE 0
#define TRUE 1
#define INFTY -1

void fill_matrix(int mat[N][N]);
int path_exists(int mat[N][N], size_t src, size_t dst);
int shortest_path(int mat[N][N], size_t src, size_t dst);
