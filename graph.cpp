#include "graph.h"

int Graph::addNode(const Node& n) {
	//This might do something at some point when the graph representation changes.
	adjList[n];
	return 1;
}

int Graph::removeNode(const Node& n) {
	adjList.erase(n);
	
	return 1;
}

int Graph::addEdge(const Node& from, const Node& to) {
	adjList[from].insert(to);
	
	return 1;
}

int Graph::removeEdge(const Node& from, const Node& to) {
	adjList[from].erase(to);
	
	return 1;
}

std::map<Node,std::set<Node> >::const_iterator Graph::begin(void) const {
	return adjList.begin();
}

std::map<Node,std::set<Node> >::const_iterator Graph::end(void) const {
	return adjList.end();
}

int Graph::getEdges(const Node& n, std::set<Node>* edgesOut) const{
	std::map<Node,std::set<Node> >::const_iterator edges = adjList.find(n);
	if(edges == adjList.end()) return -1;
	*edgesOut = edges->second;
	
	return 1;
}