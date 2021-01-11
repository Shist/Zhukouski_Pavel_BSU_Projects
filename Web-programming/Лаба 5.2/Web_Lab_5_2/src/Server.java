import java.io.File;
import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Scanner;
import java.util.Set;

public class Server {
    private static String msg = "exit";

    public Server() {
    }

    public static void main(String[] args) throws IOException {
        ArrayList<SocketChannel> clients = new ArrayList();
        Selector selector = Selector.open();
        ServerSocketChannel servSocket = ServerSocketChannel.open();
        InetSocketAddress addr = new InetSocketAddress("localhost", 1111);
        servSocket.bind(addr);
        servSocket.configureBlocking(false);
        int ops = servSocket.validOps();
        servSocket.register(selector, ops, (Object)null);
        boolean cont = true;

        while(cont) {
            System.out.println("Server is working");
            selector.select();
            Set<SelectionKey> keys = selector.selectedKeys();
            Iterator iter = keys.iterator();

            while(iter.hasNext()) {
                SelectionKey myKey = (SelectionKey)iter.next();
                if (myKey.isAcceptable()) {
                    SocketChannel client = servSocket.accept();
                    client.configureBlocking(false);
                    client.register(selector, 1);
                    System.out.println("Connection Accepted: " + client.getLocalAddress() + "\n");
                    clients.add(client);
                    System.out.println("Do you want to continue adding clients(yes=1, no=2)?");
                    int res = (new Scanner(System.in)).nextInt();
                    if (res == 2) {
                        cont = false;
                    }
                }
            }
        }

        while(true) {
            try {
                while(true) {
                    Scanner sc = new Scanner(new File("C:\\Users\\user\\IdeaProjects\\Web_Lab_5_2\\src\\input.txt"));

                    while(sc.hasNext()) {
                        System.out.println(sc.nextLine());
                    }

                    System.out.println("Choose client index");
                    int clientId = (new Scanner(System.in)).nextInt();
                    byte[] message = msg.getBytes();
                    ByteBuffer buffer = ByteBuffer.wrap(message);
                    ((SocketChannel)clients.get(clientId)).write(buffer);
                    buffer.clear();
                }
            } catch (NullPointerException var13) {
                System.out.println(var13);
            }
        }
    }
}
