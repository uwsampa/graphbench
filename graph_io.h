#include "graph.h"

#ifndef GRAPH_IO_H
#define GRAPH_IO_H

/*
	Reutrns a graph derived from the specified file.
*/
void importTestGraph(char const* filename, Graph& out);

void importTriangleTestGraph(char const* filename, Graph& out);

#endif /* GRAPH_IO_H */
