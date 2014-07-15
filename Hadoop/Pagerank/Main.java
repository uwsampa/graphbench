package Pagerank;

/**
 * The code is based on the book "Hadoop in Practice" from Alex Holmes in chapter 7. 
 * link: https://github.com/alexholmes/hadoop-book/tree/master/src/main/java/com/manning/hip/ch7/pagerank
 */
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.*;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.input.*;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

/**
 * This calculates PageRank on a directed graph.
 * 
 * The input should be a list of edges in tab-separated value (TSV) format.
 * 
 * To run the Main class, you will need five arguments. 
 * first argument: the path of the input file 
 * second argument: the intermediate folder name to save the intermediate output without pagerank
 * third argument: the intermediate folder name to save the initial output with pagerank
 * fourth argument: the result folder name to save the result 
 * fifth argument: the max number of iterations wanted; (if set to 0, iterate
 * until convergence)
 */
public final class Main {

	public static void main(String... args) throws Exception {
		String intermediate = args[2] + "/part-r-00000";
		iterate(args, intermediate, args[3], args[4]);
	}

	public static void iterate(String[] args, String input, String output,
			String maxIteration) throws Exception {
		// what's the max number of iterations we should do?
		int maxIt = Integer.parseInt(maxIteration);
		if (maxIt == 0) { // just iterate to convergence.
			maxIt = Integer.MAX_VALUE;
		}
		Configuration conf = new Configuration();
		Path outputPath = new Path(output);
		outputPath.getFileSystem(conf).delete(outputPath, true);
		outputPath.getFileSystem(conf).mkdirs(outputPath);

		Path inputPath = new Path(input);

		System.out.println(input);
		System.out.println(output);
		int numNodes = createInputFile(args, new Path(input), inputPath);

		int iter = 0;
		double convergence = 0.0;
		double desiredConvergence = 0.01;

		do {
			Path jobOutputPath = new Path(outputPath, String.valueOf(iter));

			System.out.println("======================================");
			System.out.println("=  Iteration:    " + iter);
			System.out.println("=  Input path:   " + inputPath);
			System.out.println("=  Output path:  " + jobOutputPath);
			System.out.println("======================================");

			convergence = calcPageRank(inputPath, jobOutputPath, numNodes);
			inputPath = jobOutputPath;
			iter++;
		} while (iter < maxIt && convergence >= desiredConvergence);
		System.out.println("Iterated " + iter + " times with final error "
				+ convergence + ". We are done.");
	}

	public static int createInputFile(String[] args, Path file, Path targetFile)
			throws Exception {

		int numNodes = getNumNodes(args);
		double initialPageRank = 1.0 / (double) numNodes;

		String total = Double.toString(initialPageRank);
		String[] ag = new String[] { total, args[1], args[2] };

		InitPRPreProcessor.main(ag);
		return numNodes;
	}

	public static int getNumNodes(String[] args) throws Exception {
		TSVPreProcessor.main(args);
		return TSVPreProcessor.getTotal();
	}

	public static double calcPageRank(Path inputPath, Path outputPath,
			int numNodes) throws Exception {
		Configuration conf = new Configuration();
		conf.setInt(Reduce.CONF_NUM_NODES_GRAPH, numNodes);

		Job job = Job.getInstance(conf);
		job.setJarByClass(Main.class);
		job.setMapperClass(Map.class);
		job.setReducerClass(Reduce.class);

		job.setInputFormatClass(KeyValueTextInputFormat.class);

		job.setMapOutputKeyClass(Text.class);
		job.setMapOutputValueClass(Text.class);

		FileInputFormat.setInputPaths(job, inputPath);
		FileOutputFormat.setOutputPath(job, outputPath);

		if (!job.waitForCompletion(true)) {
			throw new Exception("Job failed");
		}

		long summedConvergence = job.getCounters()
				.findCounter(Reduce.Counter.CONV_DELTAS).getValue();
		double convergence = ((double) summedConvergence / Reduce.CONVERGENCE_SCALING_FACTOR)
				/ (double) numNodes;

		System.out.println("======================================");
		System.out.println("=  Num nodes:           " + numNodes);
		System.out.println("=  Summed convergence:  " + summedConvergence);
		System.out.println("=  Convergence:         " + convergence);
		System.out.println("======================================");

		return convergence;
	}

}
