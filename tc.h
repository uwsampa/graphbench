#include <set>
#include "graph.h"

#ifndef TC_H
#define TC_H

/*
    Finds the triangles present in the undirected graph.

    Reutrns <0 on error.
*/
int triangleCount(const Graph &in, std::set<Triangle> &out);

#endif /* TC_H */
