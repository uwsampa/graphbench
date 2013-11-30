#include "graph.h"

#ifndef GRAPH_UTIL_H
#define GRAPH_UTIL_H

/*
    Print the structure of the graph to the console, starting at the given node.
    Assumes a directed, acyclic graph.
*/
void printTree(Graph& graph, Node node, std::string tabbing);

#endif /* GRAPH_UTIL_H */
