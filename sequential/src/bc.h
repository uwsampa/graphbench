#include <map>
#include "graph.h"

#ifndef BC_H
#define BC_H

/*
    Determines the betweenness centrality score for every node
    in the unweighted graph.

*/
int unweightedBetweennessCentrality(const Graph &in, std::map<Node, double> &out);

#endif /* BC_H */
