#include <map>
#include "graph.h"

#ifndef SP_H
#define SP_H

/*
    Calculates the cost of the shortest path from the given node
    to all other nodes in the graph.
*/
int shortestPath(const Node& start, const Graph& in, std::map<Node, double>& out);

#endif /* SP_H */
