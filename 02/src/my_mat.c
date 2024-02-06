#include <assert.h>
#include <stdio.h>
#include <stddef.h>

#include "my_mat.h"

void fill_matrix(int mat[N][N])
{
	int w;
	for (size_t i = 0; i < N*N; ++i)
	{
		scanf("%d", &w);
		mat[i/N][i%N] = w;
	}
}

int is_edge(int mat[N][N], size_t i, size_t j)
{
	return mat[i][j] != 0;
}

int get_weight(int mat[N][N], size_t i, size_t j)
{
	return mat[i][j];
}

typedef struct {
	size_t value;
	int priority;
} Queue_Node;

typedef struct {
	Queue_Node items[N];	// guaranteed to never have more than N values inserted
	size_t begin;			// the index of the first element (lowest priority)
	size_t end;				// the next available index in the array
} Queue;

size_t queue_count(Queue *q)
{
	return q->end - q-> begin;
}

void queue_add_with_priority(Queue *q, size_t value, int priority)
{
	size_t i = q->end;			// the index where we will insert the node
	if (priority != INFTY)		// if the priority is finite we might need to bubble 
		for (; i > q->begin && (q->items[i-1].priority == INFTY || q->items[i].priority < q->items[i-1].priority); --i)	// start from `end` (the next available index) and run as long as you have items before you and they are with higher priority
			q->items[i] = q->items[i-1];	// move the higher priority node to the empty spot
	q->items[i] = (Queue_Node) { value, priority };	// at the end, put the new node in the empty spot
	q->end += 1;						// increase the end point to the next available spot
}

size_t queue_extract_min(Queue *q)
{
	return q->items[q->begin++].value;	// return value of node at the beginning and then increment `begin`
}

void queue_decrease_priority(Queue *q, size_t value, int priority)
{
	size_t i;
	for (i = q->begin; i < q->end && q->items[i].value != value; ++i);	// find item with given value
	assert(i != q->end && "Can't decrease priority of value not in queue");
	// if (i == q->end) return;
	q->items[i].priority = priority;				// set its priority to the new priority
	for (; i > q->begin && (q->items[i-1].priority == INFTY || q->items[i].priority < q->items[i-1].priority); --i)
	{
		Queue_Node t = q->items[i];
		q->items[i] = q->items[i-1];
		q->items[i-1] = t;
	}
}

// ported from https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm#Using_a_priority_queue
int shortest_path(int mat[N][N], size_t src, size_t dst)
{
	if (src == dst) return INFTY;	// assignment definition
	int dist[N];
	dist[src] = 0;
	Queue q = { 0 };
	for (size_t v = 0; v < N; ++v)
	{
		if (v != src) dist[v] = INFTY;
		queue_add_with_priority(&q, v, dist[v]);
	}
	while (queue_count(&q) > 0)
	{
		size_t u = queue_extract_min(&q);
		// if (dist[u] == INFTY) break;		// we ran out of vertices in src's connected component
		for (size_t v = 0; v < N; ++v)
		{
			if (!is_edge(mat, u, v)) continue;
			int alt = (dist[u] == INFTY ? INFTY : dist[u] + get_weight(mat, u, v));
			if ((dist[v] == INFTY && alt != INFTY) || alt < dist[v])
			{
				dist[v] = alt;
				queue_decrease_priority(&q, v, alt);
			}
		}
	}
	return dist[dst];
}

// very similar to above, except instead of tracking dist we only need to know which were visited, priority does not matter, and return as soon as we first find dst
int path_exists(int mat[N][N], size_t src, size_t dst)
{
	int visited[N];
	Queue q = { 0 };
	for (size_t i = 0; i < N; ++i) visited[i] = FALSE;
	visited[src] = TRUE;
	queue_add_with_priority(&q, src, 0);
	while (queue_count(&q) > 0)
	{
		size_t u = queue_extract_min(&q);
		for (size_t v = 0; v < N; ++v)
		{
			if (!is_edge(mat, u, v) || visited[v]) continue;
			if (v == dst) return TRUE;
			queue_add_with_priority(&q, v, 0);
			visited[v] = TRUE;
		}
	}
	return FALSE;
}
