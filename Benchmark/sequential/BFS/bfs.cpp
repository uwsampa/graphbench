#include <set>
#include <map>
#include <queue>
#include "bfs.h"
#include "graph.h"

int bfs(const Node& start, const Graph& in, Graph& out) {
    Node current, next;
	std::set<Node> seen;
	std::queue<Node> q;
    std::map<Node, double> currentEdges;
    std::map<Node, double>::const_iterator it;
	
	out.addNode(start);
	seen.insert(start);
	q.push(start);
	
	while(!q.empty()) {
	// for every node in the graph...
		current = q.front();
		q.pop();
		
		in.getEdges(current, &currentEdges);
        for(it = currentEdges.begin();
            it != currentEdges.end();
			++it) {
			// for every edge from that node...
            next = it->first;
            if(!seen.count(next)) {
				// if the neighbor node has not been added
				// to the queue yet...
				
				// add to queue
                q.push(next);
				
				// mark as seen
                seen.insert(next);
                out.addNode(next);
				
				// add an edge in the return graph
                out.addEdge(current, next, it->second);
			}
		}
	}
	
	return 1;
}
