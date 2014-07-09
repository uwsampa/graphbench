/**
 * The code is based on the book "Hadoop in Practice" from Alex Holmes in chapter 7. 
 * link: https://github.com/alexholmes/hadoop-book/tree/master/src/main/java/com/manning/hip/ch7/pagerank
 */
import org.apache.commons.io.*;
import org.apache.commons.lang.StringUtils;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.*;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.input.*;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

import java.io.*;
import java.util.*;

/**
 * To run the Main class, you will need four arguments. first argument: the path
 * of the input file second argument: the intermediate folder name to save the
 * intermediate output third argument: the result folder name to save the result
 * fourth argument: the number of iteration wanted, greater than 0
 */
public final class Main {

	public static void main(String... args) throws Exception {
		String intermediate = args[1] + "part-r-00000";
		PreProcessor.main(args);
		iterate(intermediate, args[2], args[3]);
	}

	public static void iterate(String input, String output, String numIteration)
			throws Exception {
		int numIt = Integer.parseInt(numIteration);
		assert (numIt > 0);
		Configuration conf = new Configuration();
		Path outputPath = new Path(output);
		outputPath.getFileSystem(conf).delete(outputPath, true);
		outputPath.getFileSystem(conf).mkdirs(outputPath);

		Path inputPath = new Path(outputPath, "input.txt");

		int numNodes = createInputFile(new Path(input), inputPath);

		int iter = 1;
		while (iter <= numIt) {
			Path jobOutputPath = new Path(outputPath, String.valueOf(iter));

			System.out.println("======================================");
			System.out.println("=  Iteration:    " + iter);
			System.out.println("=  Input path:   " + inputPath);
			System.out.println("=  Output path:  " + jobOutputPath);
			System.out.println("======================================");

			calcPageRank(inputPath, jobOutputPath, numNodes);
			inputPath = jobOutputPath;
			iter++;
		}
		System.out.println("Iteration " + numIt + " times. We are done.");
	}

	public static int createInputFile(Path file, Path targetFile)
			throws IOException {
		Configuration conf = new Configuration();
		FileSystem fs = file.getFileSystem(conf);

		int numNodes = getNumNodes(file);
		double initialPageRank = 1.0 / (double) numNodes;

		OutputStream os = fs.create(targetFile);
		LineIterator iter = IOUtils.lineIterator(fs.open(file), "UTF8");

		while (iter.hasNext()) {
			String line = iter.nextLine();

			String[] parts = StringUtils.split(line);

			Node node = new Node().setPageRank(initialPageRank)
					.setAdjacentNodeNames(
							Arrays.copyOfRange(parts, 1, parts.length));
			IOUtils.write(parts[0] + '\t' + node.toString() + '\n', os);
		}
		os.close();
		return numNodes;
	}

	public static int getNumNodes(Path file) throws IOException {
		Configuration conf = new Configuration();
		FileSystem fs = file.getFileSystem(conf);

		return IOUtils.readLines(fs.open(file), "UTF8").size();
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
