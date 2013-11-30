graphbench
==========

A graph application benchmark suite

After running 'make', run './gb -b <benchmark> -g <graph file>' to run the banchmark.

Legal benchmarks are 'bfs' for breadth-first search, 'sp' for single-source shortest path, and 'tc' for triangle counting.
Currently, graphs are programmically defined. BFS will output the runtime (in ns) as well as the base graph and resulting bfs tree. TC will output the number of triangles found in the graph, as well as the triangles themselves.