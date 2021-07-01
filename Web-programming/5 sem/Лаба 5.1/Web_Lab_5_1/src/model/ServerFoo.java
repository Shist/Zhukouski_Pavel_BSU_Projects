package model;


import java.io.*;
import java.net.Socket;
import java.util.Scanner;

class ServerFoo extends Thread {
    private Socket socket;

    private BufferedReader in;

    private BufferedWriter out;

    private String msg="Big thank you for joining us from server!";

    public ServerFoo(Socket socket) throws IOException {
        this.socket = socket;
        in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        out = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
        start();
    }

    @Override
    public void run() {
        String word;
        try {
            word = in.readLine();
            try {
                out.write(word + "\n");
                out.flush();
            } catch (IOException e) {
                System.out.println(e);
            }
            try {
                do {
                    Scanner sc = new Scanner(new File("C:/Users/user/IdeaProjects/Web_Lab_5_1/src/input.txt"));
                    while (sc.hasNext()) {
                        System.out.println(sc.nextLine());
                    }
                    System.out.println("Choose client index");
                    Server.serverList.get(new Scanner(System.in).nextInt()).send(msg);
                } while (true);
            } catch (NullPointerException e) {
                System.out.println(e);
            }
        } catch (IOException e) {
            System.out.println(e);
            this.downService();
        }
    }

    private void send(String msg) {
        try {
            out.write(msg + "\n");
            out.flush();
        } catch (IOException e) {
            System.out.println(e);
        }
    }

    private void downService() {
        try {
            if (!socket.isClosed()) {
                socket.close();
                in.close();
                out.close();
                for (ServerFoo vr : Server.serverList) {
                    if (vr.equals(this))
                        break;
                    //vr.interrupt();
                    Server.serverList.remove(this);
                }
            }
        } catch (IOException e) {
            System.out.println(e);
        }
    }
}
