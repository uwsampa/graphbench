#include <set>
#include "graph.h"

#ifndef TC_H
#define TC_H

/*
    Finds the triangles present in the undirected graph.
    Assumes that, if an edge between a and b exists, where
    a < b, the edge is represented as 'from a to b' in 'in'.

    A Triangle is defined as a collection of 3 verticies a, b, c
    where the edges a-b, b-c, and a-c exist in the graph.

    Reutrns <0 on error.
*/
int undirectedTriangleCount(const Graph &in, std::set<Triangle> &out);

#endif /* TC_H */
