import java.io.IOException;
import java.rmi.AlreadyBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.*;

public class CommandServer implements RunCommand {
    public CommandServer() {

    }

    @Override
    public List<String> runCommand(String command) throws java.rmi.RemoteException {
        ArrayList<String> res = new ArrayList<String>();
        try {
            ProcessBuilder builder = new ProcessBuilder("cmd", "/c", command);
            Process p;
            p = builder.start();
            if (!p.isAlive())
                p.wait(1000);
            Scanner sc = new Scanner(p.getInputStream(), "cp866");
            while (sc.hasNext())
                res.add(sc.nextLine());
        } catch (IOException e) {
            e.printStackTrace();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        return res;
    }
}
