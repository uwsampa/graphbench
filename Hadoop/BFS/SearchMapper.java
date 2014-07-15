package BFS;

import java.io.IOException;
import org.apache.hadoop.mapreduce.Mapper;

import org.apache.hadoop.io.Text;

/**
 *
 * @author Deepika Mohan
 */
/**
 * 
 * Description : Mapper class that implements the map part of Breadth-first
 * search algorithm. The nodes colored WHITE or BLACK are emitted as such. For
 * each node that is colored GRAY, a new node is emitted with the distance
 * incremented by one and the color set to GRAY. The original GRAY colored node
 * is set to BLACK color and it is also emitted.
 * 
 * Input format <key, value> : <line offset in the input file (automatically
 * assigned),
 * nodeID<tab>list_of_adjacent_nodes|distance_from_the_source|color|parent>
 * 
 * Output format <key, value> : <nodeId, (updated)
 * list_of_adjacent_nodes|distance_from_the_source|color|parent node>
 * 
 * Reference :
 * http://www.johnandcailin.com/blog/cailin/breadth-first-graph-search
 * -using-iterative-map-reduce-algorithm
 */

// the type parameters are the input keys type, the input values type, the
// output keys type, the output values type
public class SearchMapper extends Mapper<Object, Text, Text, Text> {

	// the parameters are the types of the input key, input value and the
	// Context object through which the Mapper communicates with the Hadoop
	// framework
	public void map(Object key, Text value, Context context, Node inNode)
			throws IOException, InterruptedException {

		// For each GRAY node, emit each of the adjacent nodes as a new node
		// (also GRAY)
		// if the adjacent node is already processed and colored BLACK, the
		// reducer retains the color BLACK
		if (inNode.getColor() == Node.Color.GRAY) {
			for (String neighbor : inNode.getEdges()) { 
				Node adjacentNode = new Node(); // create a new node

				adjacentNode.setId(neighbor); // set the id of the node
				adjacentNode.setDistance(inNode.getDistance() + 1); 
				adjacentNode.setColor(Node.Color.GRAY); 
				adjacentNode.setParent(inNode.getId()); 
				context.write(new Text(adjacentNode.getId()),
						adjacentNode.getNodeInfo());
			}
			inNode.setColor(Node.Color.BLACK);
		}

		// No matter what, emit the input node
		// If the node came into this method GRAY, it will be output as BLACK
		// otherwise, the nodes that are already colored BLACK or WHITE are
		// emitted by setting the key as the node Id and the value as the node's
		// information
		context.write(new Text(inNode.getId()), inNode.getNodeInfo());
	}
}