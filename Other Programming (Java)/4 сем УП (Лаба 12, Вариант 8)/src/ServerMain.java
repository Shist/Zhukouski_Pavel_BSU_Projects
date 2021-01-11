import java.rmi.AlreadyBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;

public class ServerMain {


    public static void main(String[] args) {

        System.out.print("Server is running... Now, power on Clients");

        try {
            CommandServer cs = new CommandServer();
            RunCommand stub = (RunCommand) UnicastRemoteObject.exportObject(cs, 0);
            Registry reg = LocateRegistry.createRegistry(12345);
            reg.bind("CommandServer", stub);
        } catch (RemoteException e) {
            e.printStackTrace();
        } catch (AlreadyBoundException e) {
            e.printStackTrace();
        }
    }
}
