#include <set>
#include <vector>
#include "graph.h"

#ifndef CC_H
#define CC_H

using std::set;
using std::vector;

/*
    Finds the connected components in the given graph.

    Returns 0 on success, < 0 on error.
*/
int connectedComponents(const Graph& in, vector<set<Node> >& out);

#endif /* CC_H */
