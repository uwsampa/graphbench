# GraphLab implementations

These directories contain implementations of benchmarks using GraphLab/PowerGraph (see http://dl.acm.org/citation.cfm?id=2387880.2387883 and http://github.com/dato-code/PowerGraph.git).

*However*, since GraphLab's build system doesn't easily support external builds, we do not provide makefiles for this code. Instead, you should build it inside the GraphLab repository like this:

```
git clone git@github.com:dato-code/PowerGraph.git
cd PowerGraph
./configure
cd release/toolkits/graph_analytics
make <benchmark>
```

On a cluster using Slurm, this command runs PageRank on a graph stored in bintsv4 format, using 4 cluster nodes and all the cores on each node. GraphLab supports other graph formats as well.
```
srun --nodes=4 --ntasks-per-node=1 -- ./pagerank --graph=/path/to/graph/file.bintsv4 --format=bintsv4
```

# Docker image

This Docker image may help in running GraphBench code:
https://github.com/StartupML/jetpack
