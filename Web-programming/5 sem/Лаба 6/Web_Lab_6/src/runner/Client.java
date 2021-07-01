package runner;

import model.disc.RemoteDisc;
import model.songs.Songs;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.List;

/**
 * Client class which work with rmi methods of disc
 * @author Zhukouski Pavel
 * @version 1.0
 */
public class Client {

    /**
     * Client main method
     *
     * @param args command line params
     */
    public static void main(String[] args) {
        Registry reg;
        RemoteDisc stub;

        try {
            reg = LocateRegistry.getRegistry(9001);
            stub = (RemoteDisc)reg.lookup("Disc");
        } catch(RemoteException | NotBoundException e) {
            System.out.println(e);
            return;
        }

        int opNum = 5; // Experiments here
        try {
            System.out.println("I opened the disc");
            stub.comeIn();
            List<Songs> songs = stub.getSongs();
            printSongsList("DISC FULL SONGS LIST", songs);
            List<Songs>  detSongs;
            switch(opNum) {
                case 0:
                    detSongs = stub.selectSpecificSongs(5, "Rose Royce");
                    printSongsList("Songs of WORKMAN DEPARTMENT with duration less than 3 years", detSongs);
                    break;
                case 1:
                    detSongs = stub.selectSongsByMusician("Lil Peep");
                    printSongsList("Songs of disc", detSongs);
                    break;
                case 2:
                    detSongs = stub.selectSongsByDuration(5.0, 10.0);
                    printSongsList("Songs with duration between 5 and 10", detSongs);
                    break;
                case 3:
                    detSongs = stub.sortSongsByDuration(true);
                    printSongsList("Songs list sorted by duration IN REVERSED ORDER", detSongs);
                    break;
                case 4:
                    detSongs = stub.sortSongsByDuration(false);
                    printSongsList("Songs list sorted by duration IN NOT REVERSED ORDER", detSongs);
                    break;
                case 5:
                    int songsAmount = stub.countTotalSongsAmount();
                    System.out.println("Total amount of songs in disc : " +  songsAmount);
                    return;
                default:
                    detSongs = songs;
            }

            for(Songs songs_ : detSongs) {
                System.out.println("Try to talk to\n" + songs);
                if(stub.consultWithSongs(songs_)) {
                    System.out.println("Successful consultation");
                    System.out.println(songs_.performWork());
                    break;
                }
                System.out.println("Not lucky enough to meet this employee, try another from list");
            }

        } catch (RemoteException e) {
            System.out.println(e);
        } finally {
            try {
                stub.goOut();
            } catch(RemoteException e) {
                System.out.println(e);
            }
            System.out.println("I go out from the disc");
        }
    }

    /**
     * method to display info about all songs in disc
     * @param header that determines info for user
     * @param songsList list of described songs
     */
    public static void printSongsList(String header, List<Songs> songsList) {
        System.out.println("\n =========== " + header + " =========== ");
        if(songsList.size() > 0) {
            for(Songs songs : songsList) {
                System.out.println("\n" + songs);
            }
        }
        else {
            System.out.println("No songs");
        }
    }
}
