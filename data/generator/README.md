This directory contains:

a synthetic graph generator derived from the Graph500 Kronecker generator

Instruction:

Run: make all

To run the program:
1. generator_seq

./generator_seq <# of vertices (log 2 base)> <average # of edges per vertex [optional: -e intNumber]> <output file [optional: -o outputName]> <seed [optional: -s intNumber]> <tsv type: 0-tsv; 1-binary tsv [optional: -f 0 / -f 1]>

2. generator_omp

./generator_omp <# of vertices (log 2 base)> <average # of edges per vertex [optional: -e intNumber]> <output file [optional: -o outputName]> <seed [optional: -s intNumber]> <tsv type: 0-tsv; 1-binary tsv [optional: -f 0 / -f 1]>

Example:

To produce the data with vertice number 2^16, average # of edges per vertex 4, with tsv output

./generator_omp	16 -e 4 -o output16.txt -f 0

