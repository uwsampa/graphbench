#include <set>
#include <cmath>
#include "sp.h"

static void getLowestCost(std::set<Node> &toVisit, std::map<Node, double>& costs) {

}

int shortestPath(const Node& start, const Graph& in, std::map<Node, double>& costs_out) {
    Node current;
    std::set<Node> visited;
    std::set<Node> toVisit;
    std::map<Node,std::set<Edge> >::const_iterator it;

    for(it = in.begin(); it != in.end(); ++it) {
        out[it->first] = HUGE_VAL;
    }

    out[start] = 0.0;
    q.push(start);

    return 1;
}
