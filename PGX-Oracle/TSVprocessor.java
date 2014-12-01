import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.InputStreamReader;

/*
This class accept the file in the following format:
eg: a b (split by space)
    c d 
    e f
    g h
The goal is to change the file into the tab separated format:
eg: a	b (split by tab)
    c	d
    e	f
    g	h
It will ignore any line that starts with #
*/
public class TSVprocessor {
	public static void main(String args[]) {
		try {
			File file = new File("output.txt");
			file.createNewFile();
			FileWriter writer = new FileWriter(file);
			FileInputStream fstream = new FileInputStream(args[0]);
			DataInputStream in = new DataInputStream(fstream);
			BufferedReader br = new BufferedReader(new InputStreamReader(in));
			String strLine = null;
			while ((strLine = br.readLine()) != null) {
				if (!strLine.startsWith("#")) {
					String[] token = strLine.split(" ");
					writer.write(token[0] + "\t" + token[1] + "\n");
				}
			}
			in.close();
			writer.flush();
			writer.close();
		} catch (Exception e) {
			System.err.println("Error: " + e.getMessage());
		}
	}
}
