GraphBench
==========

The goal of GraphBench is to aggregate application kernels, reference implementations, data-sets, data-set generators, documentation, specifications for generating standardized performance results, and a hosting service (http://graphbench.org) to provide public access to the benchmark and datasets as well as aggregate and publish results by all users of the benchmark suite.   

This repository contains sequential strawman implementations of graph kernels. Implementations for other frameworks will be linked from graphbench.org. 

This is work in progress. Please submit your implementations!

So far we have: 
* 'bfs': breadth-first search. Outputs the runtime (in ns) as well as the base graph and resulting bfs tree.

* 'sssp': single-source shortest path. 

* 'tc': triangle counting. Output the number of triangles found in the graph, as well as the runtime.

Except for triangle counting and breadth-first search, input graph are synthetic and for testing only. We will include data-sets as we find, determine their licensing situation, and organize them. 

Currently, graphs may *only* be entered in TSV form and nodes labels must be representable as an unsigned integer.

After running 'make', the resulting binaries will be called 'undirected_triangle_count', 'single_source_shortest_path', and 'breadth_first_search.'

undirected_triangle_count takes one argument; the graph file
e.g. 'undirected_triangle_count -g graph.txt' or 'undirected_triangle_count --graph graph.txt'

single_source_shortest_path takes two argumetns; the graph file and the node to start forming paths from
e.g. 'single_source_shortest_path --graph graph.txt --start 51'

breadth_first_search takes two argumetns; the graph file and the node to start forming paths from
e.g. 'single_source_shortest_path --graph graph.txt --start 51'