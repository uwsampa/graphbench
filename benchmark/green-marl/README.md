# Setup

1. Get the repo
	git clone git://github.com/stanford-ppl/Green-Marl.git
2. Change the file to allow create graph using your own input file
	1) cd Green-Marl/apps/output_cpp/gm_graph/src
	2) substitute the graph_gen.cc and graph_gen_main.cc
	3) cd ../inc
	4) substitute the graph_gen.h 
3. compile
	1) cd to the top directory where you put your source package
	2) make apps
4. generate graph
	1) cd $(top)/apps/output_cpp
	2) for undirected graph:
	bin/graph_gen data/outputName.bin pathToInputFile/inputName.txt 0

	for directed graph:
	bin/graph_gen data/outputName.bin pathToInputFile/inputName.txt 1



