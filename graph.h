#include <stdint.h> // for uint32_t
#include <set>
#include <map>

#ifndef GRAPH_H
#define GRAPH_H

/*
	A class describing a single node in a graph.
*/
class Node {
	private:
		uint32_t label;
		
	public:
        Node(uint32_t _label) : label(_label) {}
        Node(void) : label(0) {}
		
        uint32_t getLabel(void) const {return label;}
		
		bool operator< (const Node& rhs) const {
			return label < rhs.label;
        }
};

/*
	A class describing a directed graph represented by Nodes.
	Edges are unweighted.
*/
class Graph {
	private:
		std::map<Node,std::set<Node> > adjList;
		
	public:
		Graph() : adjList() {}

		/*
			Add a node to the graph.
			Returns <0 on error.
		*/
		int addNode(const Node& n);
		
		/*
			Remove a node and all related edges from the graph.
			Returns <0 on error.
		*/
		int removeNode(const Node& n);
		
		/*
			Add an edge to the graph.
			Returns <0 on error.
		*/
		int addEdge(const Node& from, const Node& to);
		
		/*
			Remove an edge from the graph.
			Returns <0 on error.
		*/
		int removeEdge(const Node& from, const Node& to);
		
		/*
			Returns a const_iterator for the graph, starting at the
			lowest key.
		*/
		std::map<Node,std::set<Node> >::const_iterator begin(void) const;
		
		/*
			Returns a const_iterator for the end of the graph.
		*/
		std::map<Node,std::set<Node> >::const_iterator end(void) const;
		
		/*
			Takes a node and returns the set of edges from that node,
			through the output variable.
			Returns <0 on error.
		*/
		int getEdges(const Node& n, std::set<Node>* edgesOut) const;
};

#endif /* GRAPH_H */
