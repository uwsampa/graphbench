# Data generation and data download for GraphBench

This directory contains four things:
* code using synthetic graph generators
* links and code for downloading real datasets
* code to check dataset properties

## Kronecker graph generator
The ```generator``` directory contains a synthetic graph generator derived from the Graph500 Kronecker generator.

## Social network datasets 
The ```download.sh``` script can be used to download some real-world datasets at multiple scales. All the datasets will be downloaded to the ```data-downloaded``` directory. 

"Scale" here refers to the base 2 log of the number of vertices in the network. The wide variation in scale here is intended to allow experiments to be run with appropriately-sized datasets on many platforms, from slow hardware simulators on the low end to small clusters on the high end.

The datasets chosen include:

Scale |    Vertices |          Edges | Short name    | Description
------|-------------|----------------|---------------|--------------
12    |       4,039 |         88,234 | facebook      | Facebook dataset from the Stanford SNAP project: http://snap.stanford.edu/data/egonets-Facebook.html
16    |      81,306 |      1,768,149 | twitter-small | Small Twitter dataset from the Stanford SNAP project: http://snap.stanford.edu/data/egonets-Twitter.html
16    |      77,360 |        905,468 |  slashdot0811 | Slashdot social network (November 2008), from the Stanford SNAP project: http://snap.stanford.edu/data/soc-Slashdot0811.html
16    |      82,168 |        948,464 |  slashdot0902 | Slashdot social network (February 2009), from the Stanford SNAP project: http://snap.stanford.edu/data/soc-Slashdot0902.html
21    |   1,632,803 |     30,622,564 |         pokec | Pokec online social network, from the Stanford SNAP project: http://snap.stanford.edu/data/soc-pokec.html
22    |   4,847,571 |     68,993,773 |   livejournal | LiveJournal social network from the Stanford SNAP project: http://snap.stanford.edu/data/com-LiveJournal.html
25    |  ~41,700,000 | ~1,470,000,000 | twitter-large | Large Twitter dataset from Haewoon Kwak, Changhyun Lee, Hosung Park, and Sue Moon's publication "What is Twitter, a Social Network or a News Media?": http://an.kaist.ac.kr/traces/WWW2010.html
26    |  65,608,366 |  1,806,067,135 |    friendster | Friendster social network dataset from the Stanford SNAP project: http://snap.stanford.edu/data/com-Friendster.html

### How to run download.sh
Usage:

```
./download.sh [-s 12|16|21|22|25|26] [-n facebook|twitter|livejournal|pokec|slashdot08|slashdot09|friendster|twitter-large]
```

Specify which to download by scale, name or both.

For example, to download the dataset with scale 2^12:

```
./download.sh -s 12
```

## Links to other datasets and generators

### The Web Data Commons hyperlink graph

http://webdatacommons.org/hyperlinkgraph/

The full dataset has 3.5 billion nodes and 128 billion (directed) edges, but they provide a number of smaller, summarized versions of the dataset. All are still fairly large, though.

### Linked Data Benchmark Council Social Network generator

As part of their [Social Network benchmark](http://ldbcouncil.org/developer/snb), the [Linked Data Benchmark Council](http://ldbcouncil.org/) has developed the LDBC-SNB data generator:
https://github.com/ldbc/ldbc_snb_datagen

This builds a synthetic social network. Together with the [SNB query driver](https://github.com/ldbc/ldbc_driver) it may be used to generate a number of interesting graphs found in social networks, along with appropriate access patterns.

## Description of file formats

We support two file formats. Both represent unweighted directed or undirected graphs. Vertex IDs are not required to be contiguous in either format.

### ASCII TSV format

This format is commonly used to represent edge lists. Each line of the file consists of a pair of tab-separated vertex IDs. Vertex IDs are ASCII-encoded decimal numbers. There is no limitation on edge count imposed by the file format.

Example:
```
<vertex ID 1>\t<vertex ID 2>\n
```

### Binary bintsv4 format

This format can be used by GraphLab and Grappa. It consists simply of pairs of 32-bit vertex IDs represented as integers. Note that this limits the number of vertices in the graph to 2^32-1; there is no limitation on edge count imposed by the file format.

## Code for checking dataset properties

Currently the ```data-verify``` directory contains a single utility for plotting the degree distribution of a graph, along with plots from some of the datasets described above.
