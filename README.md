graphbench
==========

A graph application benchmark suite

After running 'make', run 'gb -b <benchmark> -g <graph file>' to run the banchmark.
e.g. 'gb -g facebook_combined.txt -b tc'

Legal benchmarks are 'bfs' for breadth-first search, 'sp' for single-source shortest path, and 'tc' for triangle counting.

Currently, only TSV graph files are supported (with commented lines starting with '#'), and only the undirected triangle count benchmark makes use of them.