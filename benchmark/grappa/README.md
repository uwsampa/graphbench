# Grappa implementations

These directories contain implementations of benchmarks using Grappa, a system for distributed parallel computation. More info is available at http://grappa.io.

## 1. Download, compile, and install Grappa

Consult https://github.com/uwsampa/grappa/blob/master/BUILD.md for more detail on building Grappa. Here's an example build:

```
git clone git@github.com:uwsampa/grappa.git
cd grappa
./configure --prefix=<path at which to install Grappa>
cd build/Make+Release
make -j <number of CPU cores to use for build>
make install
```

Grappa writes a ```settings.sh``` file into its installation directory that you should source to pick up key library paths and environment variables.

## 2. Build Graphbench Grappa code

Here's how to build all Grappa benchmarks in GraphBench:

```
cd graphbench/benchmark/grappa
source <path to Grappa installation>/bin/settings.sh
make
```

## 3. Run a Grappa benchmark

The Grappa benchmarks here can either read a graph from a file, or use a built-in synthetic Kronecker graph generator.

On a cluster using Slurm, this command runs PageRank on a Kronecker graph with 2^25 vertices, using 4 cluster nodes and 10 tasks/cores per node:
```
srun --nodes=4 --ntasks-per-node=10 -- ./pagerank/pagerank_vertex_centric --scale=25
```

This command runs the Beamer-optimized BFS on a graph file in ASCII TSV format. The Graphlab-style binary bintsv4 format is also supported.per node:
```
srun --nodes=4 --ntasks-per-node=10 -- ./bfs/bfs_beamer --path=/path/to/graph.tsv --format=tsv
```

# Docker image

Here's a Docker image for Grappa: https://registry.hub.docker.com/u/uwsampa/grappa. More info on using it is at the Grappa repo: https://github.com/uwsampa/grappa.
