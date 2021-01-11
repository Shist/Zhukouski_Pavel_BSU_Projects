package model;


import java.io.*;
import java.net.Socket;

class ClientFoo {
    private Socket socket;
    private BufferedReader in;
    private BufferedWriter out;
    private BufferedReader inputUser;
    private String name;

    public ClientFoo(String addr, int port) {
        try {
            this.socket = new Socket(addr, port);
        } catch (IOException e) {
            System.out.println(e);
        }
        try {
            inputUser = new BufferedReader(new InputStreamReader(System.in));
            if (socket != null) {
                in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            }
            if (socket != null) {
                out = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
            }
            this.pressNickname();
            new ReadMsg().start();
        } catch (IOException e) {
            System.out.println(e);
            ClientFoo.this.downService();
        }
    }

    private void pressNickname() {
        System.out.print("Enter name: ");
        try {
            name = inputUser.readLine();
            out.write("Nice to  see you, " + name + "!\n");
            out.flush();
            System.out.println("Entered name: " + name);
        } catch (IOException e) {
            System.out.println(e);
        }

    }

    private void downService() {
        try {
            if (!socket.isClosed()) {
                System.out.println("Good Bye!");
                socket.close();
                in.close();
                out.close();
            }
        } catch (IOException e) {
            System.out.println(e);
        }
    }

    private class ReadMsg extends Thread {
        @Override
        public void run() {
            String str;
            try {
                while (true) {
                    str = inputUser.readLine();
                    if (str.equalsIgnoreCase("x")) {
                        System.out.println("You are going to leave us.");
                        ClientFoo.this.downService();
                        break;
                    }
                    System.out.println(name + " received: " + str);
                }
            } catch (IOException e) {
                System.out.println(e);
                ClientFoo.this.downService();
            }
        }
    }

}
