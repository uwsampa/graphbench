package pagerank;
import java.io.IOException;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.input.TextInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;

public class InitPRPreProcessor {

	public static double pr;

	public static void main(String[] args) throws Exception {

		pr = Double.parseDouble(args[0]);
		Configuration conf = new Configuration();

		Job job = Job.getInstance(conf, "InitialPageRank converter");

		job.setJarByClass(InitPRPreProcessor.class);
		job.setOutputKeyClass(Text.class);
		job.setOutputValueClass(Text.class);

		job.setMapperClass(InitPRPreProcessor.Map.class);
		job.setReducerClass(InitPRPreProcessor.Reduce.class);

		job.setInputFormatClass(TextInputFormat.class);
		job.setOutputFormatClass(TextOutputFormat.class);

		FileInputFormat.addInputPath(job, new Path(args[1] + "/part-r-00000"));
		FileOutputFormat.setOutputPath(job, new Path(args[2]));
		job.waitForCompletion(true);
	}

	public static class Map extends Mapper<LongWritable, Text, Text, Text> {

		public void map(LongWritable key, Text value, Context context)
				throws IOException, InterruptedException {
			String line = value.toString();
			String[] token = line.split("	");
			if (token[0].length() > 0 && !token[0].startsWith("#")) {
				Text k = new Text();
				if (token.length > 1) {
					String[] edges = token[1].split(" ");
					String s = "";
					for (int i = 0; i < edges.length; i++) {
						if (s.equals("")) {
							s = edges[i];
						} else {
							s = s + "	" + edges[i];
						}
					}
					k.set(token[0]);
					context.write(k, new Text(s));
				} else {
					context.write(new Text(token[0]), new Text());
				}
			}
		}
	}

	public static class Reduce extends Reducer<Text, Text, Text, Text> {

		public void reduce(Text key, Iterable<Text> values, Context context)
				throws IOException, InterruptedException {
			String s = "";
			for (Text val : values) {
				s = s + pr + "	" + val;

			}
			context.write(key, new Text(s));
		}
	}
}
