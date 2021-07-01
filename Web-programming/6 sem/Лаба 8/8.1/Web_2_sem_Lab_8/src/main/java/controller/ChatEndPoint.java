package controller;

import javax.websocket.OnMessage;
import javax.websocket.Session;
import javax.websocket.server.ServerEndpoint;
import java.io.IOException;
import java.util.HashMap;
import java.util.List;

@ServerEndpoint("/chat")

public class ChatEndPoint {

    private HashMap<String, List<String>> buffer = new HashMap<>();

    @OnMessage
    public void onMessage(Session session, String msg) {
        if (!session.getUserProperties().containsKey("sender")) {
            String[] someInfo = msg.split(":=:");
            session.getUserProperties().put("sender", someInfo[1]);
        } else {
            String sender = (String) session.getUserProperties().get("sender");
            String receiverName;
            String message;
            switch (sender) {
                case "Pavel":
                    String[] someInfo = msg.split(":=:");
                    receiverName = someInfo[0];
                    message = someInfo[1];
                    break;
                default:
                    receiverName = "Pavel";
                    message = msg;
            }

            for (Session sessionReceiver : session.getOpenSessions()) {
                if (sessionReceiver.isOpen()) {
                    if (sessionReceiver.getUserProperties().containsKey("sender")) {
                        String sessionSenderName = (String) sessionReceiver.getUserProperties().get("sender");
                        if (sessionSenderName.equals(receiverName)) {
                            try {
                                sessionReceiver.getBasicRemote().sendText(sender + ": " + message);
                            } catch (IOException e) {
                                e.printStackTrace();
                            }
                        }
                    }
                }
            }
        }

    }
}
