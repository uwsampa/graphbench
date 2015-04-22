import java.io.File;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.Writer;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class CountFrequency {

	public static File f;
	public static InputStream in;
	public static OutputStream out;
	public static Map<Integer, Integer> memo;

	public static void main(String[] args) throws IOException {
//		f = new File("/home/yx0618/Documents/research/graphbench/data/generator/out10.txt");
		f = new File("input.txt");
		memo = new HashMap<Integer, Integer>();
		processData();
		writeData();
		out.close();
		System.out.println("finish!");
	}
	
	public static void processData() throws IOException {
		InputStream in = new FileInputStream(f);
		Scanner s = new Scanner(in);
		while (s.hasNextLine()) {
			String[] current = s.nextLine().split("\t");
			int first = Integer.parseInt(current[0]);
			int second = Integer.parseInt(current[1]);
			if (!memo.containsKey(first)) {
				memo.put(first, 1);
			} else {
				int freq = memo.get(first);
				freq++;
				memo.put(first, freq);
			}
			if (!memo.containsKey(second)) {
				memo.put(second, 1);
			} else {
				int freq = memo.get(second);
				freq++;
				memo.put(second, freq);
			}
		}
		s.close();
		in.close();
	}
	
	public static void writeData() throws IOException {
//		Writer wr = new FileWriter("/home/yx0618/Documents/research/graphbench/data/generator/out10-freq.txt");
		Writer wr = new FileWriter("output.txt");
		for (Integer i : memo.keySet()) {
			wr.write(String.valueOf(i));
			wr.write("\t");
			wr.write(String.valueOf(memo.get(i)));
			wr.write("\n");
		}
		wr.close();
	}
}
