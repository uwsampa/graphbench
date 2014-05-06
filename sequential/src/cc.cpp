#include <queue>
#include <map>
#include <iostream>
#include "cc.h"

using std::vector;
using std::set;
using std::queue;
using std::map;

int connectedComponents(const Graph &in, vector<set<Node> > &out) {
    map<Node, double> edges;
    map<Node, map<Node, double> >::const_iterator graph_it;
    map<Node, double>::const_iterator it;
    set<Node> currentComponent, remainingNodes;
    queue<Node> q;
    Node n;

    // add all of the nodes to the set of nodes
    for(graph_it = in.begin(); graph_it != in.end(); ++graph_it) {
        remainingNodes.insert(graph_it->first);
    }

    while (!remainingNodes.empty()) {
        // while there are still components to find, find them!
        currentComponent.clear();

        // find a node not currently associated with a component...
        n = *(remainingNodes.begin());
        q.push(n);
        remainingNodes.erase(n);

        // and explore its component
        while (!q.empty()) {
            n = q.front();
            q.pop();

            // add the node to the current component
            currentComponent.insert(n);
            in.getEdges(n, &edges);

            for(it = edges.begin(); it != edges.end(); ++it) {
                // for all the edges leading from the current node...

                if(remainingNodes.count(it->first) > 0) {
                    // if the terminal node has not already been visited, add to the component to the queue
                    q.push(it->first);
                    remainingNodes.erase(it->first);
                }
            }
        }

        // once the component is explored, add it to the return value
        out.push_back(currentComponent);
    }

    return 0;
}
