#include <set>
#include <cmath>
#include "sp.h"

int shortestPath(const Node& start, const Graph& in, std::map<Node, double>& out) {
    Node current;
    std::set<Node> visited;
    std::map<Node,std::set<Edge> >::const_iterator it;

    for(it = in.begin(); it != in.end(); ++it) {
        out[it->first] = HUGE_VAL;
    }

    return 1;
}
