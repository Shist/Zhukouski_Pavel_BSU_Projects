package model;


import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.LinkedList;

public class Server {

    public static LinkedList<ServerFoo> serverList = new LinkedList<>();

    public static void main(String[] args) throws IOException {
        ServerSocket server = new ServerSocket(8080);
        System.out.println("Server is working");
        try {
            while (true) {
                Socket socket = server.accept();
                try {
                    serverList.add(new ServerFoo(socket));
                } catch (IOException e) {
                    System.out.println(e);
                    //socket.close();
                }
            }
        } finally {
            server.close();
        }
    }
}