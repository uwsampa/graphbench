#include "bfs.h"
#include "graph.h"
#include <set>
#include <queue>

int bfs(const Node& start, const Graph& in, Graph& out) {
	Node current;
	std::set<Node> seen;
	std::queue<Node> q;
	std::set<Node> currentEdges;
	std::set<Node>::const_iterator it;
	
	out.addNode(start);
	seen.insert(start);
	q.push(start);
	
	while(!q.empty()) {
	// for every node in the graph...
		current = q.front();
		q.pop();
		
		in.getEdges(current, &currentEdges);
		for(it=currentEdges.begin();
			it !=currentEdges.end();
			++it) {
			// for every edge from that node...
			if(!seen.count(*it)) {
				// if the neighbor node has not been added
				// to the queue yet...
				
				// add to queue
				q.push(*it);
				
				// mark as seen
				seen.insert(*it);
				out.addNode(*it);
				
				// add an edge in the return graph
				out.addEdge(current, *it);
			}
		}
	}
	
	return 1;
}