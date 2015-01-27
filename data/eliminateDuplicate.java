import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Scanner;
import java.util.Set;

public class eliminateDuplicate {
	public static OutputStream out;
	public static InputStream in;
	public static File inputFile;
	public static File outputFile;
	public static Map<String, Set<String>> memo;

	public static void main(String[] args) throws IOException {
		if (args.length != 3) {
			System.out
					.println("usage: java eliminateDuplicate <input> <output> <0 for undirected, 1 for directed>");
		} else {
			inputFile = new File(args[0]);
			outputFile = new File(args[1]);
			int directed = Integer.parseInt(args[2]);
			in = new FileInputStream(inputFile);
			out = new FileOutputStream(outputFile);
			memo = new HashMap<String, Set<String>>();
			readFile(directed);
			writeFile();
		}
	}

	// 0 for undirected, 1 for directed
	public static void readFile(int directed) {
		Scanner s = new Scanner(in);
		if (directed == 1) {
			while (s.hasNext()) {
				String[] tokens = s.nextLine().split("\t");
				// Integerint[] int_tokens = { Integer.parseInt(tokens[0]),
				// Integer.parseInt(tokens[1]) };
				if (!memo.containsKey(tokens[0]))
					memo.put(tokens[0], new HashSet<String>());
				memo.get(tokens[0]).add(tokens[1]);
			}
		} else {
			// undirected
			while (s.hasNext()) {
				String[] tokens = s.nextLine().split("\t");
				if (!memo.containsKey(tokens[0]))
					memo.put(tokens[0], new HashSet<String>());
				if (!memo.containsKey(tokens[1]))
					memo.put(tokens[1], new HashSet<String>()); 
				memo.get(tokens[0]).add(tokens[1]);
				memo.get(tokens[1]).add(tokens[0]);
			}
		}
	}

	public static void writeFile() throws IOException {
		for (String key : memo.keySet()) {
			for (String value : memo.get(key)) {
				out.write(key.getBytes());
				out.write("\t".getBytes());
				out.write(value.getBytes());
				out.write("\n".getBytes());
			}
		}
	}

}
