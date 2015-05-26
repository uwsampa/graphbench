# How to run SSSP

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

## Steps

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

### Notice

for our sample input, we have the format of:

node1 node2

node1 node3

...

[it is separated by tab instead of space, also, it does not have the 'cost']

Use the convert.java in the parent directory to convert the sample input into the application format.

We assume the cost is 1.0 for any edge.
