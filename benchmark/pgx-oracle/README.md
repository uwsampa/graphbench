
# Instruction

## Installation without pgx console
Download Oracle PGX

```
http://www.oracle.com/technetwork/oracle-labs/parallel-graph-analytics/downloads/index.html
```

Unzip the files and set PGX_HOME to the correct directory. 

More instruction for how to use it, check the README.md in each sub-directory.

## Installation for using pgx console
Download Oracle PGX and Groovy (2.4.0 is a hard require)

```
http://www.oracle.com/technetwork/oracle-labs/parallel-graph-analytics/downloads/index.html
http://dl.bintray.com/groovy/maven/groovy-binary-2.4.0.zip 
```
Notice: the newest version for grooxy is 2.4.3 right now and it is not going to work

Unzip the files and set PGX_HOME and GROOVY_HOME to the correct directory. 

## Test

```
cd $PGX_HOME
./bin/pgx
```

### SSSP example using pgx console

Use the build-in Dijkstra Algorithm to solve SSSP and BFS.

The only difference between SSSP and BFS is that the cost for SSSP might not always be 1.0.

You can adjust the input file accordingly.

--------------------------------------
When you type: 'help dijkstra' in the console of pgx, you will see:

usage: dijkstra [String graphName] [String costPropName] [Object src] [Object dst] [String parentName] [String parentEdgeName] 

Compute shortest path using Dijkstra's algorithm. Time complexity: O(N log N) with N = number of nodes
Arguments:
graphName - graph id
costPropName - (input) the edge property name (of type double) holding the edge costs of the graph
src - (input) source node (has to be of type 'nodekey' as specified in loader config of graph)
dst - (input) destination node (has to be of type 'nodekey' as specified in loader config of graph)
parentName - (output) the node property name (of type NodeProperty.class) to store parent node information
parentEdgeName - (output) the node property name (of type EdgeProperty.class) to store parent edge information
Returns: <code>true</code> if path exists, <code>false</code> otherwise

Equivalent Java API: PgxFuture<Boolean> PathFinding#shortestPathDijkstra(String sessionId, String graphName, String costPropName, Object src, Objecft dst, String parentName, String parentEdgeName)

---------------------------------------

Try the following example.

The input file (input.txt)is :

```
0 1 1.0
0 2 2.0
3
1 2 1.0
```

(there are four nodes: 0, 1, 2, 3 and three edges: 0->1 (1.0), 0->2 (2.0), 1->2 (1.0))

The test.edge.json file is :

```json
{
  "uri": "input.txt", 
  "format": "adj_list",
  "edge_props": [{ 
    "name": "cost", 
    "type": "double" 
  }],
  "separator": " "
}
```

#### Steps

1. :loadGraph test.edge.json test
[the .json file config the graph and 'test' is the name of the graph]

2. :createNodeProperty test NODE node
[create NodeProperty for parentName]

3. :createNodeProperty test EDGE edge
[create NodeProperty for parentEdgeName]

4. :dijkstra test cost 0 3 node edge
[find if there is a path between 0 and 3(will return false)]

5. :dijkstra test cost 0 2 node edge
[find if there is a path between 0 and 2(will return true)]

#### Notice

for our sample input, we have the format of:

node1 node2

node1 node3

...

[it is separated by tab instead of space, also, it does not have the 'cost']

Use the convert.java in the parent directory to convert the sample input into the application format.

We assume the cost is 1.0 for any edge.

### BC example using pgx console
Use the build-in approximateNodeBetweennessCentrality.

-------------------------------------------------------------
When you type: 'help approximateNodeBetweennessCentrality' in the console of pgx, you will see:

usage: approximateNodeBetweennessCentrality <String graphName> <int k> <String bcName> 

approximate node betweenness centrality (without considering edge length). The algorithm performs a BFS only from randomly selected k seed nodes instead of every node. time complexity: O(K * E) with E = number of edges, K is a given constant (# of seed nodes)
Arguments:
graphName - graph name
k - how many random selected seed nodes to use
bcName - (output) name of double node property to store result
Equivalent Java API: PgxFuture<Void> Ranking#approximateNodeBetweennessCentrality(String sessionId, String graphName, int k, String bcName)
-------------------------------------------------------------

Try the following example.

The input file (input.txt)is the facebook_combined.txt file from :
http://snap.stanford.edu/data/egonets-Facebook.html

It has the format:
node1 node2
node1 node3
node2 node4
...
[separated by white space]


The test.edge.json file is :
{
    "type": "EDGE_LIST",
    "uri": "facebook_combined.txt",
    "separator": " "
}


1. loadGraph test.edge.json test
-- the .json file config the graph and 'test' is the name of the graph

2. createNodeProperty test DOUBLE bc
-- create node property to store the result

3. approximateNodeBetweennessCentrality test 100 bc
-- calculate the BC for 100 random selected seeds and save to bc

4. nodePropValue test bc 2
-- see the output for node 2

5. (optional) printTopK test bc 20
-- you can see the top 20 nodes with this command


Notice: for the input file that is Tab-separated, there are two options:
1. change the separator in json file
2. change line 30 and 31 in the convert.java to convert tab-separated into white-space separated




## More Details
check the original documentation from Oracle

https://docs.oracle.com/cd/E56133_01/index.html

More tutorial after installation:

https://docs.oracle.com/cd/E56133_01/tutorials/index.html


# Notice
Keep all the .java and .sh file in the same directory. 

Run the .sh file, pass in the correct parameters and the output will measure the processing time for the particular algorithm.   

For now, only the pgx-oracle framework is included. We will update when other frameworks are available.

