#include "graph_io.h"

void importGraph(char const* filename, Graph& out) {
	//TODO actually do file IO
	out.addNode(1);
    out.addEdge(1, 2, 1);
    out.addEdge(1, 3, 2);
    out.addEdge(1, 4, 3);
	
	out.addNode(2);
    out.addEdge(2, 3, 1);
    out.addEdge(2, 4, 2);
	
	out.addNode(4);
    out.addEdge(4, 5, 1);
	
	out.addNode(5);
}
