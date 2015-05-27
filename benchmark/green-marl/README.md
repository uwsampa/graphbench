# Setup

Get the repo

```
git clone git://github.com/stanford-ppl/Green-Marl.git
```

Change the file to allow create graph using your own input file
```
cd Green-Marl/apps/output_cpp/gm_graph/src
```

	Task : substitute the graph_gen.cc and graph_gen_main.cc

```
cd ../inc
```

	Task : substitute the graph_gen.h 

compile

	Task : cd to the top directory where you put your source package
```
make apps
```

generate graph

```
cd $(top)/apps/output_cpp
```
	for undirected graph:

```
bin/graph_gen data/outputName.bin pathToInputFile/inputName.txt 0
```
	
	for directed graph:
	
```
bin/graph_gen data/outputName.bin pathToInputFile/inputName.txt 1
```
	

## Notice 
Flex might not be installed if 

```
flex: command not found
```
Run below in ubuntu:

```
sudo apt-get install flex
```

