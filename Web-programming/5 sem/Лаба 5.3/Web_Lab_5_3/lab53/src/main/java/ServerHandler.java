import io.netty.channel.Channel;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.SimpleChannelInboundHandler;
import io.netty.channel.group.ChannelGroup;
import io.netty.channel.group.DefaultChannelGroup;
import io.netty.util.concurrent.GlobalEventExecutor;
import org.apache.log4j.LogManager;
import org.apache.log4j.Logger;


import java.io.*;
import java.util.Random;
import java.util.Scanner;

/**
 * Server handler.
 */
public class ServerHandler extends SimpleChannelInboundHandler<String> {
    /**
     * Connected channels
     */
    private static final ChannelGroup channels = new DefaultChannelGroup(GlobalEventExecutor.INSTANCE);

    /**f
     * random
     */
    final Random random = new Random();
    Logger logger = LogManager.getLogger(ServerHandler.class.getName());


    public ServerHandler() {
        new ReadMsg().start();
    }

    /**
     * Method for dealing with just joined client
     * @param ctx context
     * @throws Exception ex
     */
    @Override
    public void handlerAdded(ChannelHandlerContext ctx) throws Exception {
        logger.info(" Server handler added.");
        File file = new File("C:\\Users\\user\\IdeaProjects\\Web_Lab_5_3\\lab53\\src");
        BufferedReader br = new BufferedReader(new FileReader(file));

        String st;
        FileWriter fr = new FileWriter(file, true);
        BufferedWriter bw = new BufferedWriter(fr);
        int i = 0;
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
//
        channels.add(ctx.channel());
    }

    /**
     * Method for dealing with just left client
     * @param ctx context
     * @throws Exception ex
     */
    @Override
    public void handlerRemoved(ChannelHandlerContext ctx) throws Exception {
        logger.info(" Server handler removed.");
        Channel incoming = ctx.channel();
        for (Channel channel : channels) {
            channel.write("[Server] - " + incoming.remoteAddress() + " has left!\n");
        }
        channels.remove(ctx.channel());
    }

    /**
     * Method for dealing with just came msg
     * @param channelHandlerContext channel handler context
     * @param s msg
     * @throws Exception ex
     */
    @Override
    public void channelRead0(ChannelHandlerContext channelHandlerContext, String s) throws Exception {
        Channel incoming = channelHandlerContext.channel();
        for (Channel channel : channels) {
            if (channel != incoming) {
                channel.write("[" + incoming.remoteAddress() + "]" + s + "\n");
            }
        }
    }
    public String msg="We are happy to see you there!";
    /**
     * class for sending messages to connected clients
     */
    private class ReadMsg extends Thread {
        @Override
        public void run() {
            while (true) {
                Scanner sc = null;
                try {
                    sc = new Scanner(new File("C:\\Users\\user\\IdeaProjects\\Web_Lab_5_3\\lab53\\src\\index.txt"));
                } catch (FileNotFoundException e) {
                    e.printStackTrace();
                }
                while(sc.hasNext()) {
                    System.out.println(sc.nextLine());
                }
                System.out.println("Choose client index.txt");
                sc = new Scanner(System.in);
                int clientIndex = sc.nextInt();
                int i = 0;
                System.out.println("Client index " + clientIndex);
                for (Channel channel : channels) {
                    System.out.println("Channel:" + channel.id());
                    logger.info("Channel:" + channel.id());
                    if (i == clientIndex) {
                        System.out.println("Client "+ i+ " got a new message from server:");
                        logger.info("Client "+ i+ "got a new message:");
                        channel.write(msg);
                        System.out.println(msg);
                        logger.info(msg);
                    }
                    i++;
                }
            }
        }
    }
}
