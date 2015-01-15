

This directory includes sequential strawman implementations of graph kernels.

So far we have: 
* 'bfs': breadth-first search. Outputs the runtime (in ns) as well as the base graph and resulting bfs tree.

* 'sssp': single-source shortest path. 

* 'tc': triangle counting. Output the number of triangles found in the graph, as well as the runtime.

* 'pr': pagerank. Outputs the rank for each page in the (directed) graph. Our implementation takes dangling pages into account.

* 'cc': connected components.

Except for triangle counting and breadth-first search, input graph are synthetic and for testing only. We will include data-sets as we find, determine their licensing situation, and organize them. 

Currently, graphs may *only* be entered in TSV or CSV format and nodes labels must be representable as an unsigned integer.

After running 'make', the resulting binaries will be called 'undirected_triangle_count', 'single_source_shortest_path', 'breadth_first_search', 'pagerank', and 'connected_components'.

undirected_triangle_count takes two arguments; the graph file and its format
e.g. 'undirected_triangle_count -g graph.txt -f tsv' or 'undirected_triangle_count --graph graph.txt --format tsv'

single_source_shortest_path takes three arguments; the graph file, its format, and the node to start forming paths from
e.g. 'single_source_shortest_path --graph graph.txt --format tsv --start 51'

breadth_first_search takes three arguments; the graph file, its format, and the node to start forming paths from
e.g. 'breadth_first_search --graph graph.txt --format tsv --start 51'
