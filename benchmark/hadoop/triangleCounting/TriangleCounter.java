// The code is based on Stephen Walkauskas's code for Counting Triangle. 
// We changed some parts to fit out input as well as removed some map 
// classes and the last reduce class.
// reference: http://www.vertica.com/2011/09/21/counting-triangles/
// github link for the code: https://github.com/vertica/Graph-Analytics----Triangle-Counting
package triangleCounting;

import java.io.IOException;
import java.util.*;

import org.apache.hadoop.fs.Path;
import org.apache.hadoop.conf.*;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapreduce.*;
import org.apache.hadoop.mapreduce.lib.input.*;
import org.apache.hadoop.mapreduce.lib.output.*;

public class TriangleCounter {

	/**
	 * Maps values to Text, LongWritable pairs
	 */
	public static class ParseTextLongPairsMapper extends
			Mapper<LongWritable, Text, Text, LongWritable> {
		Text mKey = new Text();
		LongWritable mValue = new LongWritable();

		public void map(LongWritable key, Text value, Context context)
				throws IOException, InterruptedException {
			String line = value.toString();
			String[] token = line.split("\\s+");
			if (token[0].length() > 0 && !token[0].startsWith("#")) {
				String[] tokenAgain = token[0].split(",");
				if (tokenAgain.length == 2) {
					mKey.set(token[0]);
					mValue.set(Long.parseLong(token[1]));
				} else {
					long e1 = Long.parseLong(token[0]);
					long e2 = Long.parseLong(token[1]);
					if (e1 < e2) {
						mKey.set(token[0]);
						mValue.set(e2);
					} else {
						mKey.set(token[1]);
						mValue.set(e1);
					}
				}
				context.write(mKey, mValue);
			}
		}
	}

	/**
	 * This reduce produces the original edges and triads The value 1 means:
	 * this is the missing edge we are looking for The value 0 means: this is
	 * the original edge from the input
	 */
	public static class TriadsReducer extends
			Reducer<Text, LongWritable, Text, LongWritable> {
		Text rKey = new Text();
		long[] vArray = new long[4096];
		int size;
		final static LongWritable zero = new LongWritable((byte) 0);
		final static LongWritable one = new LongWritable((byte) 1);

		public void reduce(Text key, Iterable<LongWritable> values,
				Context context) throws IOException, InterruptedException {
			Iterator<LongWritable> vs = values.iterator();
			size = 0;
			while (vs.hasNext()) {
				// resize the array if there are more edges
				if (vArray.length == size)
					vArray = Arrays.copyOf(vArray, vArray.length * 2);
				long e = vs.next().get();
				vArray[size++] = e;
				// Generate original edge.
				rKey.set(key + "," + Long.toString(e));
				context.write(rKey, zero);
			}
			Arrays.sort(vArray, 0, size);
			// Generate triads.
			// Since every element in the array is the vertex connected to the
			// apex, every pair formed is the missing edge we are looking for in
			// the next mapReduce
			for (int i = 0; i < size; ++i) {
				for (int j = i + 1; j < size; ++j) {
					rKey.set(Long.toString(vArray[i]) + ","
							+ Long.toString(vArray[j]));
					context.write(rKey, one);
				}
			}
		}
	}

	/**
	 * This reducer counts the number of triangles
	 */
	public static class CountTrianglesReducer extends
			Reducer<Text, LongWritable, Text, Text> {
		// count is the number of triangles
		int count = 0;

		public void cleanup(Context context) throws IOException,
				InterruptedException {
			context.write(new Text(
					"The total number of triangle in the graph is:"), new Text(
					"" + count));
		}

		public void reduce(Text key, Iterable<LongWritable> values,
				Context context) throws IOException, InterruptedException {
			long c = 0, n = 0;
			Iterator<LongWritable> vs = values.iterator();
			// Triad edge value=1, original edge value=0.
			while (vs.hasNext()) {
				c += vs.next().get();
				++n;
			}
			// if c != n then it means there is an original edge
			if (c != n)
				count += c;
		}
	}

	/**
	 * This method takes two arguments, the edges file and output file. Edges
	 * must not be reciprocal, that is every {source, dest} edge must not have a
	 * corresponding {dest, source}. File must be of the form: long <whitespace>
	 * long <newline> <repeat>
	 */
	public static int run(String[] args) throws Exception {
		Configuration conf = new Configuration();

		Job job1 = Job.getInstance(conf);
		job1.setJobName("triads");

		job1.setMapOutputKeyClass(Text.class);
		job1.setMapOutputValueClass(LongWritable.class);

		job1.setOutputKeyClass(Text.class);
		job1.setOutputValueClass(LongWritable.class);

		job1.setJarByClass(TriangleCounter.class);
		job1.setMapperClass(ParseTextLongPairsMapper.class);
		job1.setReducerClass(TriadsReducer.class);

		job1.setInputFormatClass(TextInputFormat.class);
		job1.setOutputFormatClass(TextOutputFormat.class);

		FileInputFormat.addInputPath(job1, new Path(args[0]));
		FileOutputFormat.setOutputPath(job1, new Path("temp"));

		Job job2 = Job.getInstance(conf);
		job2.setJobName("triangles");

		job2.setMapOutputKeyClass(Text.class);
		job2.setMapOutputValueClass(LongWritable.class);

		job2.setOutputKeyClass(LongWritable.class);
		job2.setOutputValueClass(LongWritable.class);

		job2.setJarByClass(TriangleCounter.class);
		job2.setMapperClass(ParseTextLongPairsMapper.class);
		job2.setReducerClass(CountTrianglesReducer.class);

		job2.setInputFormatClass(TextInputFormat.class);
		job2.setOutputFormatClass(TextOutputFormat.class);

		FileInputFormat.setInputPaths(job2, new Path("temp"));
		FileOutputFormat.setOutputPath(job2, new Path(args[1]));

		int ret = job1.waitForCompletion(true) ? 0 : 1;
		if (ret == 0)
			ret = job2.waitForCompletion(true) ? 0 : 1;
		return ret;
	}

	public static void main(String[] args) throws Exception {
		if (args.length != 2) {
			System.err.println("Usage: <input file> <output directory name>");
			System.exit(0);
		}
		int res = run(args);
		if (res == 0)
			System.out.println("We are done!");
		System.exit(res);
	}
}
