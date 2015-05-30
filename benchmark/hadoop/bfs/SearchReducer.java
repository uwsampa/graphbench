package bfs;

import java.io.IOException;

import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;

/**
* @author Deepika Mohan
*/
/**
 * Description : Reducer class that implements the reduce part of parallel
 * Breadth-first search algorithm. Make a new node which combines all
 * information for this single node id that is for each key. The new node should
 * have the full list of edges, the minimum distance, the darkest Color, and the
 * parent/predecessor node
 * 
 * Input format <key,value> : 
 * <nodeId, list_of_adjacent_nodes|distance_from_the_source|color|parent_node>
 * 
 * Output format <key,value> : 
 * <nodeId, (updated)list_of_adjacent_nodes|distance_from_the_source|color|parent_node>
 */

// the type parameters are the input keys type, the input values type, the
// output keys type, the output values type

public class SearchReducer extends Reducer<Text, Text, Text, Text> {

	// the parameters are the types of the input key, the values associated with
	// the key, the Context object through which the Reducer communicates with
	// the Hadoop framework and the node whose information has to be output
	// the return type is a Node
	public Node reduce(Text key, Iterable<Text> values, Context context,
			Node outNode) throws IOException, InterruptedException {

		// set the node id as the key
		outNode.setId(key.toString());

		// since the values are of the type Iterable, iterate through the values
		// associated with the key
		// for all the values corresponding to a particular node id

		for (Text value : values) {
			Node inNode = new Node(key.toString() + "\t" + value.toString());

			// One (and only one) copy of the node will be the fully expanded
			// version, which includes the list of adjacent nodes, in other
			// cases, the mapper emits the ndoes with no adjacent nodes
			// In other words, when there are multiple values associated with
			// the key (node Id), only one will
			if (inNode.getEdges().size() > 0) {
				outNode.setEdges(inNode.getEdges());
			}

			// Save the minimum distance
			if (inNode.getDistance() < outNode.getDistance()) {
				outNode.setDistance(inNode.getDistance());

				// if the distance gets updated then the predecessor node that
				// was responsible for this distance will be the parent node
				outNode.setParent(inNode.getParent());
			}

			// Save the darkest color
			if (inNode.getColor().ordinal() > outNode.getColor().ordinal()) {
				outNode.setColor(inNode.getColor());
			}

		}
		// emit the key, value pair where the key is the node id and the value
		// is the node's information
		context.write(key, new Text(outNode.getNodeInfo()));
		return outNode;
	}
}