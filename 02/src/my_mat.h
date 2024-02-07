#pragma once
#include <stddef.h>

#define N 10		// number of vertices or size of adjacency matrix
#define FALSE 0
#define TRUE 1
#define INFTY -1

void fill_matrix(int mat[N][N]);
int path_exists(const int mat[N][N], const size_t src, const size_t dst);
int shortest_path(const int mat[N][N], const size_t src, const size_t dst);
