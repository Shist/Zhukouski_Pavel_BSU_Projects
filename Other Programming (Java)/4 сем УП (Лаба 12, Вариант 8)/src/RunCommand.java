import java.util.List;

public interface RunCommand extends java.rmi.Remote{
    public List<String> runCommand(String command) throws java.rmi.RemoteException;
}
