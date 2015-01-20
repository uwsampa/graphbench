package BFS;

import java.io.IOException;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Counters;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.input.KeyValueTextInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

/**
 * This code is based on Deepika Mohan's SSSPJob:
 * http://hadooptutorial.wikispaces.com/file/view/SSSPJob.java 
 * Also reference to:
 * http://www.johnandcailin.com/blog/cailin/breadth-first-graph-search-using-
 * iterative-map-reduce-algorithm
 */

public class Main {

	// counter to determine the number of iterations or if more iterations are
	// required to execute the map and reduce functions
	static enum MoreIterations {
		numberOfIterations
	}

	/**
	 * Description : Mapper class that implements the map part of Single-source
	 * shortest path algorithm. It extends the SearchMapper class. The map
	 * method calls the super class' map method. 
	 * Input format :
	 * nodeID<tab>list_of_adjacent_nodes|distance_from_the_source|color|parent
	 */
	public static class SearchMapperMain extends SearchMapper {
		public void map(Object key, Text value, Context context)
				throws IOException, InterruptedException {
			Node inNode = new Node(key.toString() + "	" + value.toString());
			super.map(key, value, context, inNode);
		}
	}

	/**
	 * Description : Reducer class that implements the reduce part of the
	 * Single-source shortest path algorithm. This class extends the
	 * SearchReducer class that implements parallel breadth-first search
	 * algorithm. The reduce method implements the super class' reduce method
	 * and increments the counter if the color of the node returned from the
	 * super class is GRAY.
	 */
	public static class SearchReducerMain extends SearchReducer {
		public void reduce(Text key, Iterable<Text> values, Context context)
				throws IOException, InterruptedException {
			Node outNode = new Node();
			outNode = super.reduce(key, values, context, outNode);
			if (outNode.getColor() == Node.Color.GRAY)
				context.getCounter(MoreIterations.numberOfIterations)
						.increment(1L);
		}
	}

	/**
	 * This method runs the map-reduce for BFS. 
	 * @param args the command line argument
	 * @throws Exception
	 */
	public static void run(String[] args) throws Exception {
		int iterationCount = 0;
		long terminationValue = 1;
		while (terminationValue > 0) {
			Configuration conf = new Configuration();
			Job job = Job.getInstance(conf);
			job.setJarByClass(Main.class);
			job.setMapperClass(SearchMapperMain.class);
			job.setReducerClass(SearchReducerMain.class);
			job.setInputFormatClass(KeyValueTextInputFormat.class);
			job.setMapOutputKeyClass(Text.class);
			job.setMapOutputValueClass(Text.class);
			String input;
			if (iterationCount == 0)
				input = args[1] + "/part-r-00000";
			else
				input = args[2] + iterationCount;
			String output = args[2] + (iterationCount + 1);
			FileInputFormat.setInputPaths(job, new Path(input));
			FileOutputFormat.setOutputPath(job, new Path(output));
			job.waitForCompletion(true);

			Counters jobCntrs = job.getCounters();
			terminationValue = jobCntrs.findCounter(
					MoreIterations.numberOfIterations).getValue();
			iterationCount++;
		}
	}

	/**
	 * The main to run the BFS and needs three arguments
	 * first argument: the input file
	 * second argument: the intermediate path to save the initial condition
	 * third argument: the result path
	 */
	public static void main(String[] args) throws Exception {
		if (args.length != 3) {
			System.err.println("Usage: <in> <intermediate name> <output name>");
			System.exit(0);
		}
		TSVPreProcessor.main(args);
		run(args);
		System.out.println("We are done!");
	}
}
