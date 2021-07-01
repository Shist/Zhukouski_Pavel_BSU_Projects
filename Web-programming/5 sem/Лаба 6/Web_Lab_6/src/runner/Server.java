package runner;

import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.AlreadyBoundException;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import util.manager.SongsManager;
import util.builder.SongsBuilder;
import model.disc.*;


/**
 * Server class that contains disc
 * @author Zhukouski Pavel
 * @version 1.0
 */
public class Server {
    /**
     * Server main method
     *
     * @param args command line params
     */
    public static void main(String[] args) {
        Disc disc = new Disc(new DiscManager());
        SongsManager manager = new SongsManager();
        SongsBuilder builder = new SongsBuilder();

        disc.addSongs(manager.provideAccountant(builder, "Growl", "EXO"));
        builder.reset();

        disc.addSongs(manager.provideAccountant(builder, "Car Wash", "Rose Royce"));
        builder.reset();

        disc.addSongs(manager.provideReceptionist(builder, "Again", "Yui"));
        builder.reset();

        disc.addSongs(manager.provideForeman(builder, "Rammstein)", "Mein Herz Brennt"));
        builder.reset();

        disc.addSongs(manager.provideLoader(builder, "Can't Help Falling in Love", "Elvis Presley"));
        builder.reset();

        disc.addSongs(manager.provideLoader(builder, "Voice of the soul", "Death"));
        builder.reset();

        disc.addSongs(manager.provideWelder(builder, "Star shopping", "Lil Peep"));
        builder.reset();

        disc.addSongs(manager.provideWelder(builder, "Slam", "Onyx"));
        builder.reset();

        System.out.println("Create disc");

        try {
            RemoteDisc stub = (RemoteDisc) UnicastRemoteObject.exportObject(disc, 0);
            Registry reg = LocateRegistry.createRegistry(9001);
            reg.bind("Disc", stub);
            System.out.println("Register disc");
        } catch(RemoteException | AlreadyBoundException e) {
            System.out.println(e);
        }
    }
}
