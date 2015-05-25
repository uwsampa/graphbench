# Data generation and data download for GraphBench

This directory contains three things:
* code using synthetic graph generators
* code downloading real datasets
* code verifying datasets


## Kronecker graph generator
The ```generator``` directory contains a synthetic graph generator derived from the Graph500 Kronecker generator.

## download.sh
The ```download.sh``` contains all the code to download the datasets we found useful and interesting to take a look at different scales. 

The datasets chosen include:

2^12 - facebook; 

2^16 - twitter, slashdot0811, slashdot0902;

2^21 - pokec;

2^22 - livejournal;

2^25 - twitter-large;

2^26 - friendster

### How to run download.sh


## data-verify
The ```data-verify``` directory contains verify.py and the outputs after running the program on the datasets picked.
