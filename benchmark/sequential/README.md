

This directory includes sequential strawman implementations of graph kernels.

So far we have: 
* 'bfs': breadth-first search. Outputs the runtime as well as the base graph and resulting bfs tree.

* 'sssp': single-source shortest path. 

* 'tc': triangle counting. Output the number of triangles found in the graph, as well as the runtime.

* 'pr': pagerank. Outputs the rank for each page in the (directed) graph. Our implementation takes dangling pages into account.

* 'cc': connected components.

* 'cc': betweenness centrality.

Except for triangle counting and breadth-first search, input graph are synthetic and for testing only. 

Currently, graphs may *only* be entered in TSV or CSV format and nodes labels must be representable as an unsigned integer.

After running 'make', the resulting binaries will be called 'undirected_triangle_count', 'single_source_shortest_path', 'breadth_first_search', 'pagerank', 'connected_components', and 'betweenness_centrality'.

Below shows the usage for each of them:

./undirected_triangle_count -g graph.txt <-f csv [optional, default to tsv]>  <-o [optional, default to not print the result>

./single_source_shortest_path -g graph.txt -s startNode <-f csv [optional, default to tsv]>  <-o [optional, default to not print the result>

./page_rank -g graph.txt -g graph.txt <-d damping_factor [optional, default to 0.85]> <-f csv [optional, default to tsv]>  <-o [optional, default to not print the result>

./connected_components -g graph.txt <-f csv [optional, default to tsv]>  <-o [optional, default to not print the result>

./breadth_first_search -g graph.txt -s startnode <-f csv [optional, default to tsv]>  <-o [optional, default to not print the result>

./betweenness_centrality -g graph.txt <-f csv [optional, default to tsv]>  <-o [optional, default to not print the result>