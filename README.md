GraphBench
==========

GraphBench is a community-driven graph benchmark suite.

Graph and irregular computation is of increasing importance to industry, the government, and the sciences. The core computational component of many “big data”, machine-learning, and security applications is an irregular computation typically done on a graph data structure.

GraphBench is a collection of graph kernels and datasets to aid graph-processing framework creators in developing their systems. Our approach is to provide specifications of important kernels, along with curation of existing datasets, data generators, and reference implementations across a wide variety of graph analytics platforms. We also provide preconfigured Docker images for many of these platforms to make it easier to get started running the kernels.

This is a community effort! We need your help to build a representative and relevant benchmark suite. Please join our Google Group, clone our GitHub repo, and contribute your favorite implementations and data sources!

Note that is work in progress; things are in flux.

What's inside
-------------
The ```benchmark``` directory contains the following:
* specifications of benchmarks,
* links to implementations maintained in other repos, and instructions for using them,
* and source code for implementations that are not found in other repos, and instructions for using them.

The ```data``` directory contains the following:
* specifications of data file formats,
* links to data and data generators maintained in other repos, and instructions for using them,
* and source code for data generators and data manipulation utilitites, with instructions for using them.

How to to use it
-------------
Right now this is a very manual process. More information will appear here in the future.

How to contribute
-------------
The file ```CONTRIBUTING.md``` describes how new benchmarks and datasets should be added to GraphBench.

License and contributors
-------------
The file ```CONTRIBUTORS.md``` lists contributors to this project. The file ```COPYING.md``` describes how the code is licensed.




GraphBench has four components:

Kernel specifications
Datasets and Synthetic data generators
Reference implementations
Instructions on using Frameworks and Docker images
