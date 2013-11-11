#include "graph_io.h"

void importGraph(char const* filename, Graph& out) {
	//TODO actually do file IO
	out.addNode(1);
	out.addEdge(1, 2);
	out.addEdge(1, 3);
	out.addEdge(1, 4);
	
	out.addNode(2);
	out.addEdge(2, 3);
	out.addEdge(2, 4);
	
	out.addNode(4);
	out.addEdge(4, 5);
	
	out.addNode(5);
}