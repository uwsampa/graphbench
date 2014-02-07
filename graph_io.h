#include "graph.h"

#ifndef GRAPH_IO_H
#define GRAPH_IO_H

/*
	Reutrns a graph derived from the specified file.
*/
void importTestGraph(char const* filename, Graph& out);

void importTriangleTestGraph(char const* filename, Graph& out);

/*
 * Reads in the graph from the designated file. The file must be in TSV format,
 * with comment lines starting with a '#'
 *
 * Returns 0 on success, <0 on error
 */
int importTSVGraph(char const* filename, Graph& out, bool directed);

#endif /* GRAPH_IO_H */
