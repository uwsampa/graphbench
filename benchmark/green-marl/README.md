# Setup

Get the repo

```
git clone git://github.com/stanford-ppl/Green-Marl.git
```

Change the file to allow create graph using your own input file by substituting the graph_gen.cc and graph_gen_main.cc and graph_gen.h 
```
cd Green-Marl/apps/output_cpp/gm_graph/src
cp <graphbench>/benchmark/green-marl/graph_gen.cc <graphbench>/benchmark/green-marl/graph_gen_main.cc .
cd ../inc
cp <graphbench>/benchmark/green-marl/graph_gen.h .
```

Go to the top of the Green-marl and compile

```
cd $(top)
make apps
```

Generate graph (0 for undirected and 1 for directed graph)

```
cd $(top)/apps/output_cpp
bin/graph_gen data/outputName.bin pathToInputFile/inputName.txt 0
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

