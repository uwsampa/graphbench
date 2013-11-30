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

int Graph::addEdge(const Node& from, const Node& to, const double& weight) {
    adjList[from][to] = weight;
	
	return 1;
}

int Graph::addEdgeUndirected(const Node& a, const Node& b, const double& weight) {
    int result;

    if((result = addEdge(a, b, weight)) < 0) {
        return result;
    }

    if((result = addEdge(b, a, weight)) < 0) {
        removeEdge(a, b);
    }

    return result;
}

int Graph::removeEdge(const Node& from, const Node& to) {
    // find from's edges
    std::map<Node,std::map<Node, double> >::iterator from_itr = adjList.find(from);

    // if from is not in the graph, return error
    if(from_itr == adjList.end()) {
        return -1;
    }

    // find to
    std::map<Node, double>::iterator to_itr = from_itr->second.find(to);

    // if to was not found in the edge list, return error
    if(to_itr == from_itr->second.end()) {
        return -1;
    }

    from_itr->second.erase(to_itr);

    return 1;
}

bool Graph::edgeExists(const Node& from, const Node& to) const{
    // find from's edges
    std::map<Node,std::map<Node, double> >::const_iterator from_itr = adjList.find(from);

    // if from was not found in the graph, return false
    if(from_itr == adjList.end()) {
        return false;
    }

    // find to in the set of edges
    std::map<Node, double>::const_iterator to_itr = from_itr->second.find(to);

    // if to was found, return true
    return to_itr != from_itr->second.end();
}

std::map<Node,std::map<Node, double> >::const_iterator Graph::begin(void) const {
	return adjList.begin();
}

std::map<Node,std::map<Node, double> >::const_iterator Graph::end(void) const {
	return adjList.end();
}

int Graph::getEdges(const Node& n, std::map<Node, double>* edgesOut) const{
    std::map<Node,std::map<Node, double> >::const_iterator edges = adjList.find(n);
	if(edges == adjList.end()) return -1;

	*edgesOut = edges->second;
	
	return 1;
}
