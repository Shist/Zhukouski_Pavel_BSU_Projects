import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;

public class Client {
    private static BufferedWriter out;

    public Client() {
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        InetSocketAddress addr = new InetSocketAddress("localhost", 1111);
        SocketChannel client = SocketChannel.open(addr);
        System.out.println("Connecting to Server...");
        System.out.println("Enter your name:");
        String name = reader.readLine();
        if (name != null) {
            while(true) {
                String data;
                do {
                    ByteBuffer buffer = ByteBuffer.allocate(1024);
                    client.read(buffer);
                    data = (new String(buffer.array())).trim();
                } while(data.length() <= 0);

                System.out.println(name + " received message: " + data);
                if (data.equalsIgnoreCase("exit")) {
                    client.finishConnect();
                    System.out.println(name + "connection closed...");
                }
            }
        }

    }
}
