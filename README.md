GraphBench
==========

GraphBench is a community-driven graph benchmark suite.

Graph and irregular computation is of increasing importance to industry, the government, and the sciences. The core computational component of many “big data”, machine-learning, and security applications is an irregular computation typically done on a graph data structure.

GraphBench is a collection of graph kernels and datasets to aid graph-processing framework creators in developing their systems. We've collected a number of existing datasets and reference implementations across a wide variety of graph analytics platforms. We've also collected Docker images to help get started with the configuration process for some frameworks.

This is a community effort! We need your help to build a representative and relevant benchmark suite. Please [join our Google Group](http://groups.google.com/d/forum/graphbench), [clone our GitHub repo](https://github.com/uwsampa/graphbench), and contribute your favorite implementations and data sources!

Note that is work in progress; things are in flux.

What's inside
-------------

GraphBench is not a traditional plug-and-play benchmark suite with a do-everything run script. Instead we provide components you can use to assemble your own evaluation strategy. We believe this is the right strategy given the diversity of graph frameworks out there.

The ```benchmark``` directory contains reference implementations for different frameworks. Read the README.md file in each framework's directory for instructions on building and running them.

The ```data``` directory contains the following:
* specifications of data file formats,
* links to data and data generators maintained in other repos, and instructions for using them,
* and source code for data generators and data manipulation utilitites, with instructions for using them.

How to contribute
-------------
The file ```CONTRIBUTING.md``` describes how new benchmarks and datasets should be added to GraphBench.

License and contributors
-------------
The file ```CONTRIBUTORS.md``` lists contributors to this project. The file ```COPYING.md``` describes how the code is licensed.

