#include "graph.h"

#ifndef BFS_H
#define BFS_H

/*
	Performs a breadth-first search of the input graph, starting
	at the specified node, and returns the resulting tree through
    the output variable. Assumes a directed graph.
	Returns <0 on error.
*/
int bfs(const Node& start, const Graph& in, Graph& out);

#endif /* BFS_H */
