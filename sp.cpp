#include <set>
#include <cmath>
#include "sp.h"

static void getLowestCost(std::set<Node> &toVisit,
                          std::map<Node, double>& costs,
                          Node &lowest_out) {
    std::set<Node>::const_iterator it;

    double lowest = HUGE_VAL;
    for(it = toVisit.begin(); it != toVisit.end(); ++it) {
        Node current = *it;

        if(costs[current] < lowest) {
            lowest = costs[current];
            lowest_out = current;
        }
    }
}

int shortestPath(const Node& start,
                 const Graph& in,
                 std::map<Node, double>& costs_out,
                 std::map<Node, Node>& prev_out) {
    Node current;
    double cost;
    std::set<Node> visited;
    std::set<Node> toVisit;
    std::map<Node,std::set<Edge> >::const_iterator graph_it;
    std::set<Edge>::const_iterator edge_it;
    std::set<Edge> edges;

    for(graph_it = in.begin(); graph_it != in.end(); ++graph_it) {
        costs_out[graph_it->first] = HUGE_VAL;
    }

    costs_out[start] = 0.0;
    toVisit.insert(start);

    while(!toVisit.empty()) {
        getLowestCost(toVisit, costs_out, current);
        toVisit.erase(current);
        visited.insert(current);

        // for every edge from the current node
        in.getEdges(current, &edges);

        for(edge_it = edges.begin();
            edge_it != edges.end();
            ++edge_it) {

            // if the neighboring node has not been visited
            if(visited.count(edge_it->to) == 0) {
                cost = costs_out[current] + edge_it->weight;

                // if this is the lowest cost path so far
                if(cost < costs_out[edge_it->to]) {
                    costs_out[edge_it->to] = cost;
                    prev_out[edge_it->to] = current;
                    toVisit.insert(edge_it->to);
                }
            }
        }

    }

    return 1;
}
