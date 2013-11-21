graphbench
==========

A graph application benchmark suite

After running 'make', run 'gb -b <benchmark> -g <graph file>' to run the banchmark.
Legal benchmarks are 'bfs' for breadth-first search and 'sp' for single-source shortest path.
Currently, graphs are programmically defined. BFS will output the runtime (in ns) as well as the base graph and resulting bfs tree.