#include <map>
#include "graph.h"

#ifndef SSSP_H
#define SSSP_H

/*
    Calculates the cost of the shortest path from the given node
    to all other nodes in the graph.

    Returns <0 on error.
*/
int singleSourceShortestPath(const Node& start,
                 const Graph& in,
                 std::map<Node,double>& costs_out,
                 std::map<Node, Node>& prev_out);

#endif /* SSSP_H */
