import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.List;
import java.util.Scanner;

public class CommandClient {
    private RunCommand stub;
    private String PS1;
    public CommandClient() throws RemoteException, NotBoundException {
        Registry reg = LocateRegistry.getRegistry("localhost", 12345);
        stub = (RunCommand) reg.lookup("CommandServer");
        PS1 = stub.runCommand("cd").get(0);
    }

    public String exec(String command) throws  RemoteException{
        command = command.trim();
        List<String> res = stub.runCommand("cd /D" + PS1 + " && " + command + "&& cd");
        if (res.size() < 1)
            return "Server resuming his work...\n";
        String ret = "";
        if (!res.get(res.size() - 1).equals(PS1))
            PS1 = res.get(res.size() - 1);
        for (int i = 0; i < res.size() - 1; ++i)
            ret += res.get(i) + "\n";
        return ret;
    }

    public String getPS1() {
        return PS1;
    }
}
