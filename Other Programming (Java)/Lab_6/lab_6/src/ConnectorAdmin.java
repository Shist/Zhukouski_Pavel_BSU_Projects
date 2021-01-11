import java.io.*;
public class ConnectorAdmin {
    private String filename;

    public ConnectorAdmin( String filename ) {
        this.filename = filename;
    }

    public void write( Administrator admin) throws IOException {
        FileOutputStream fos = new FileOutputStream (filename);
        try ( ObjectOutputStream oos = new ObjectOutputStream( fos )) {
            oos.writeObject( admin );
            oos.flush();
        }
    }

    public Administrator read() throws IOException, ClassNotFoundException {
        FileInputStream fis = new FileInputStream(filename);
        try ( ObjectInputStream oin = new ObjectInputStream(fis)) {
            Administrator result=(Administrator) oin.readObject();
            return result;
        }
    }
}
