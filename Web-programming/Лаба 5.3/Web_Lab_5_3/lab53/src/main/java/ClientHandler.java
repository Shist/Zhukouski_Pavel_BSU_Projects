import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.SimpleChannelInboundHandler;
import org.apache.log4j.LogManager;
import org.apache.log4j.Logger;


/**
 * client handler class.
 */
public class ClientHandler extends SimpleChannelInboundHandler<String> {
    Logger logger = LogManager.getLogger(ClientHandler.class.getName());

    /**
     * method for dealing with the received message
     * @param channelHandlerContext channel handler
     * @param s message
     * @throws Exception ex
     */
    @Override
    public void channelRead0(ChannelHandlerContext channelHandlerContext, String s) throws Exception {
        logger.info(s);
    }
}
