import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.InputStreamReader;

public class TSVprocessor {
	public static void main(String args[]) {
		try {
			File file = new File("input.txt");
			file.createNewFile();
			FileWriter writer = new FileWriter(file);
			FileInputStream fstream = new FileInputStream(args[0]);
			DataInputStream in = new DataInputStream(fstream);
			BufferedReader br = new BufferedReader(new InputStreamReader(in));
			String strLine = null;
			while ((strLine = br.readLine()) != null) {
				if (!strLine.startsWith("#")) {
					String[] token = strLine.split(" ");
					writer.write(token[0] + " " + token[1] + " 1.0" + "\n");
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
