#include "graph_io.h"

void importTestGraph(char const* filename, Graph& out) {
	//TODO actually do file IO
	out.addNode(1);
    out.addEdge(1, 2, 1);
    out.addEdge(1, 3, 2);
    out.addEdge(1, 4, 3);
	
	out.addNode(2);
    out.addEdge(2, 3, 1);
    out.addEdge(2, 4, 2);

    out.addNode(3);
	
	out.addNode(4);
    out.addEdge(4, 5, 1);
	
	out.addNode(5);
}

void importTriangleTestGraph(char const* filename, Graph& out) {
    //TODO actually do file IO
    out.addNode(1);
    out.addNode(2);
    out.addNode(3);
    out.addNode(4);
    out.addNode(5);
    out.addNode(6);
    out.addNode(7);

    // 1-2-3
    out.addEdgeUndirected(1, 2, 1);
    out.addEdgeUndirected(1, 3, 1);
    out.addEdgeUndirected(3, 2, 1);

    // 3-4-5
    out.addEdgeUndirected(3, 4, 1);
    out.addEdgeUndirected(5, 4, 1);
    out.addEdgeUndirected(3, 5, 1);

    // red herrings
    out.addEdgeUndirected(1, 6, 1);
    out.addEdgeUndirected(4, 7, 1);
}
