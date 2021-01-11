import io.netty.bootstrap.Bootstrap;
import io.netty.channel.Channel;
import io.netty.channel.EventLoopGroup;
import io.netty.channel.nio.NioEventLoopGroup;
import io.netty.channel.socket.nio.NioSocketChannel;
import org.apache.log4j.LogManager;
import org.apache.log4j.Logger;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Scanner;

/**
 * Class represents chat client.
 */
public class Client {
    static Logger clientLogger = LogManager.getLogger(Client.class.getName());

    public static void main(String[] args) {
        System.out.println("Write client's name:");
        Scanner sc = new Scanner(System.in);
        String clientIndex = sc.nextLine();
        new Client(clientIndex, "localhost", 8000).run();
    }

    /**
     * host
     */
    private final String host;

    /**
     * port
     */
    private final int port;

    /**
     * name
     */
    private String name;

    public Client(String name, String host, int port) {
        this.name = name;
        this.host = host;
        this.port = port;
    }

    /**
     * Method for starting client configuration
     */
    public void run() {
        clientLogger.info("Client " + name + " started working");
        EventLoopGroup group = new NioEventLoopGroup();
        try {
            Bootstrap bootstrap = new Bootstrap()
                    .group(group)
                    .channel(NioSocketChannel.class)
                    .handler(new ClientInitializer());
            Channel channel = bootstrap.connect(host, port).sync().channel();
            BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

            while (true) {
                channel.write(in.readLine() + "\r\n");
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            group.shutdownGracefully();
        }
        clientLogger.info("Client " + name + " finished working");
    }
}

