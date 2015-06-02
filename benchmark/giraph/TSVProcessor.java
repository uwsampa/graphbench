import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;


public class TSVProcessor {
	
	public static File f;
	public static InputStream in;
	public static OutputStream out;
	public static Map<Integer, Set<Integer>> memo;
	
	
	public static void main(String[] args) {
		try {
			File file = new File("giraph-standard-input.txt");
			file.createNewFile();
			FileWriter writer = new FileWriter(file);
			FileInputStream fstream = new FileInputStream(args[0]);
			DataInputStream in = new DataInputStream(fstream);
			BufferedReader br = new BufferedReader(new InputStreamReader(in));
			String strLine = null;
			memo = new HashMap<Integer, Set<Integer>>();
			while ((strLine = br.readLine()) != null) {
				if (!strLine.startsWith("#")) {
					String[] token = strLine.split("	");
					int from = Integer.parseInt(token[0]);
					int to = Integer.parseInt(token[1]);
					if (memo.keySet().contains(from)) {
						memo.get(from).add(to);
					} else {
						memo.put(from, new HashSet<Integer>());
						memo.get(from).add(to);
					}
				}
			}
			in.close();
			for (Integer i : memo.keySet()) {
				int from = i;
				writer.write("[" + from + ",0,");
				writer.write("[");
				int left = memo.get(i).size();
				for (Integer j : memo.get(i)) {
					writer.write("[" + j + ",1]");
					left--;
					if (left != 0) {
						writer.write(",");
					}
				}
				writer.write("]]\n");
			}
			writer.flush();
			writer.close();
		} catch (Exception e) {
			System.err.println("Error: " + e.getMessage());
		}
		
	}
}
