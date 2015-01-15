package Pagerank;

import java.io.IOException;

import org.apache.hadoop.fs.Path;
import org.apache.hadoop.conf.*;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapreduce.*;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.input.TextInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;

public class TSVPreProcessor {
	public static int TOTAL = 0;

	public static class Map extends
			Mapper<LongWritable, Text, Text, IntWritable> {

		// the required input should be in the form of
		// n1 n2
		// n3 n4 etc
		// create the intermediate file in the form of
		// b a (if b points to a)
		public void map(LongWritable key, Text value, Context context)
				throws IOException, InterruptedException {
			String line = value.toString();
			String[] token = line.split("\\s+");
			if (token[0].length() > 0 && !token[0].startsWith("#")) {
				Text k = new Text();
				k.set(token[0]);
				context.write(k, new IntWritable(Integer.parseInt(token[1])));
				context.write(new Text(token[1]), new IntWritable(-1));
			}
		}
	}

	public static class Reduce extends Reducer<Text, IntWritable, Text, Text> {

		// reduce the intermediate file to the form of
		// a b c d e f
		// if a points to b c d e f
		public void reduce(Text key, Iterable<IntWritable> values,
				Context context) throws IOException, InterruptedException {
			String s = "";
			for (IntWritable val : values) {
				if (val.get() >= 0)
					s = s + " " + val.get();
			}
			context.write(key, new Text(s));
			TOTAL++;
		}
	}

	public static void main(String[] args) throws Exception {
		Configuration conf = new Configuration();

		Job job = Job.getInstance(conf, "TSV converter");

		job.setOutputKeyClass(Text.class);
		job.setOutputValueClass(IntWritable.class);

		job.setMapperClass(Map.class);
		job.setReducerClass(Reduce.class);

		job.setInputFormatClass(TextInputFormat.class);
		job.setOutputFormatClass(TextOutputFormat.class);

		FileInputFormat.addInputPath(job, new Path(args[0]));
		FileOutputFormat.setOutputPath(job, new Path(args[1]));

		job.waitForCompletion(true);
	}

	public static int getTotal() {
		return TOTAL;
	}

}
