#include <map>
#include "graph.h"

#ifndef PR_H
#define PR_H

/*
    Calculates the page rank of all the verticies in the given graph, returning
    a map of Nodes to their PageRank value. The current implementation accounts for dangling pages.
    Assumes that the graph is directed.
    The sum of all page ranks will be N, where N is the number of nodes in the graph.

    Reutrns 0 on success, <0 on error.
*/
int pageRank(const Graph &in, const float dampingFactor, std::map<Node, double> &out);

/*
    Prints each Node followed by its PageRank to stdout, one Node per line.
 */
void printPageRanks(const std::map<Node, double> &in);

#endif /* PR_H */
