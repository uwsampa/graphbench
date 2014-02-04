GraphBench
==========

The goal of GraphBench is to aggregate application kernels, reference implementations, data-sets, data-set generators, documentation, specifications for generating standardized performance results, and a hosting service (http://graphbench.org) to provide public access to the benchmark and datasets as well as aggregate and publish results by all users of the benchmark suite.   

This repository contains sequential strawman implementations of graph kernels. Implementations for other frameworks will be linked from graphbench.org. 

This is work in progress. Please submit your implementations!

Input graphs are synthetic for now. We will include data-sets as we find, determine their licensing situation and organize them. 

So far we have: 
* 'bfs': breadth-first search. Outputs the runtime (in ns) as well as the base graph and resulting bfs tree.

* 'sp': single-source shortest path. 

* 'tc': triangle counting. Output the number of triangles found in the graph, as well as the triangles themselves.


After running 'make', run './gb -b <benchmark> -g <graph file>' to run the benchmark.

