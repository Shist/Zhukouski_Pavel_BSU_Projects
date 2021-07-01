package model;

import java.io.*;

public class Client {

    //public static String ipAddr = "localhost";
    //public static int port = 8080;

    public static void main(String[] args) throws IOException {
        File file = new File("C:/Users/user/IdeaProjects/Web_Lab_5_1/src/input.txt");
        BufferedReader br = new BufferedReader(new FileReader(file));
        FileWriter fr = new FileWriter(file, true);
        BufferedWriter bw = new BufferedWriter(fr);
        int i = 0;
        String st;
        if (br.readLine() != null) {
            while ((st = br.readLine()) != null) {
                i = Integer.parseInt(st.trim());
            }

            i++;
            bw.newLine();
            bw.write(String.valueOf(i));
        } else {
            bw.write(String.valueOf(i));
        }

        bw.close();
        br.close();
        fr.close();

        new ClientFoo("localhost", 8080);
    }
}