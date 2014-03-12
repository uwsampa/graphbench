#include <map>
#include "graph.h"

#ifndef PR_H
#define PR_H

/*
    Calculates the page rank of all the verticies in the given graph, returning
    a map of Nodes to their PageRank value. Assumes that the graph is directed.

    Reutrns 0 on success, <0 on error.
*/
int pageRank(const Graph &in, const float dampingFactor, std::map<Node, double> &out);

/*
    Prints each Node followed by its PageRank to stdout, one Node per line.
 */
void printPageRanks(const std::map<Node, double> &in);

#endif /* PR_H */
