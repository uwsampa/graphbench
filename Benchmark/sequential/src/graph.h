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

        bool operator== (const Node& rhs) const {
            return label == rhs.label;
        }

        bool operator!= (const Node& rhs) const {
            return !operator==(rhs);
        }

        Node& operator=(const Node& rhs) {
          this->label = rhs.label;
          return *this;
        }
};

/*
	A class describing a directed graph represented by Nodes.
	Edges are unweighted.
*/
class Graph {
	private:
        std::map<Node,std::map<Node, double> > adjList;
		
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
            Add an edge to the graph with the given weight.
			Returns <0 on error.
		*/
        int addEdge(const Node& from, const Node& to, const double& weight = 1.0);

        /*
            Add an undirected edge to the graph with the given weight.
            Returns <0 on error.
        */
        int addEdgeUndirected(const Node& a, const Node& b, const double& weigh = 1.0);
		
		/*
			Remove an edge from the graph.
			Returns <0 on error.
		*/
		int removeEdge(const Node& from, const Node& to);

        /*
            Returns true if the edge exists in the graph, false otherwise.
        */
        bool edgeExists(const Node& from, const Node& to) const;
		
		/*
			Returns a const_iterator for the graph, starting at the
			lowest key.
		*/
        std::map<Node,std::map<Node, double> >::const_iterator begin(void) const;
		
		/*
			Returns a const_iterator for the end of the graph.
		*/
        std::map<Node,std::map<Node, double> >::const_iterator end(void) const;
		
		/*
			Takes a node and returns the set of edges from that node,
			through the output variable.
			Returns <0 on error.
		*/
        int getEdges(const Node& n, std::map<Node, double>* edgesOut) const;

        /*
            Returns the number of nodes in the graph.
        */
        uint32_t size() const;
};

class Triangle {
public:
    Node a, b, c;

    Triangle(Node _1, Node _2, Node _3) {
        a = _1;
        b = _2;
        c = _3;
    }

    bool operator< (const Triangle& rhs) const {
        if(a != rhs.a) {
            return a < rhs.a;
        } else if (b != rhs.b) {
            return b < rhs.b;
        } else {
            return c < rhs.c;
        }
    }
};

#endif /* GRAPH_H */
