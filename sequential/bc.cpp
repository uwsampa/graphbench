/*
 * Based on the betweenness centrality algorithm described in
 *  A Faster Algorithm for Betweenness Centrality.
 *  Ulrik Brandes, Journal of Mathematical Sociology 25(2):163-177, 2001.
 *  http://www.inf.uni-konstanz.de/algo/publications/b-fabc-01.pdf
 *
 */

#include <stack>
#include <cmath>
#include <iomanip>
#include <queue>
#include <list>
#include <iostream>
#include "bc.h"

using std::map;
using std::stack;
using std::list;
using std::queue;

int unweightedBetweennessCentrality(const Graph &in, map<Node, double> &out) {
    stack<Node> S;
    map<Node, list<Node> > P;
    queue<Node> Q;
    map<Node, int> dist, num_sp;
    map<Node, double> edges, pair_dep;
    map<Node, map<Node, double> >::const_iterator graph_it, tmp_it;
    map<Node, double>::iterator edge_it;
    list<Node>::iterator sp_it;

    int iteration = 0;

    // initialize centrality to 0
    for (graph_it = in.begin(); graph_it != in.end(); graph_it++) {
        out[graph_it->first] = 0.0;
    }

    // for each node in the graph...
    for (graph_it = in.begin(); graph_it != in.end(); graph_it++) {
        P.clear();
        dist.clear();
        num_sp.clear();
        pair_dep.clear();
        Node s = graph_it->first;

        // print progress
        double progress = (++iteration / (double)in.size());
        std::cout << std::setprecision(4) <<std::fixed << progress * 100.0 << "%\r";
        std::cout.flush();

        // initialize distances from current node to -1
        // and num shortest paths through each node to 0
        // initialize pair dependencies to 0
        for (tmp_it = in.begin(); tmp_it != in.end(); tmp_it++) {
            dist[tmp_it->first] = -1;
            num_sp[tmp_it->first] = 0;
            pair_dep[tmp_it->first] = 0.0;
        }

        // for the current node,
        // initialize distance to 0
        // and num shortest paths to 1
        dist[s] = 0;
        num_sp[s] = 1;

        Q.push(s);
        while (!Q.empty()) {
            Node v = Q.front();
            Q.pop();
            S.push(v);
            in.getEdges(v, &edges);

            // for each neighbor w of v...
            for (edge_it = edges.begin(); edge_it != edges.end(); ++edge_it) {
                Node w = edge_it->first;
                // if we have not seen w yet...
                if (dist[w] < 0) {
                    Q.push(w);
                    dist[w] = dist[v] + 1;
                }

                if (dist[w] == dist[v] + 1) {
                    num_sp[w] += num_sp[v];
                    P[w].push_back(v);
                }
            }
        }

        while (!S.empty()) {
            Node w = S.top();
            S.pop();

            for (sp_it = P[w].begin(); sp_it != P[w].end(); ++sp_it) {
                Node v = *sp_it;
                pair_dep[v] += ((double)num_sp[v]/(double)num_sp[w]) * (1 + pair_dep[w]);
            }
            if (w != s) {
                out[w] += pair_dep[w];
            }
        }
    }

    return 0;
}
