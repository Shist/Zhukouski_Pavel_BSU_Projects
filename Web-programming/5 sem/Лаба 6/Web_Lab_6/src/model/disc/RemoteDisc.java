package model.disc;

import model.songs.Songs;
import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.List;


/**
 * interface that give RMI methods from disc service
 * @author Zhukouski Pavel
 * @version 1.0
 */
public interface RemoteDisc extends Remote {

    /**
     * come to disc
     *
     */
    void comeIn() throws RemoteException;

    /**
     * go out from disc
     *
     */
    void goOut() throws RemoteException;

    /**
     * return songs of the disc
     *
     * @return songs list
     */
    List<Songs> getSongs() throws RemoteException;

    /**
     * return disc director
     *
     * @return director
     */
    DiscManager getDirector() throws RemoteException;

    /**
     * count total amount of songs in disc
     *
     * @return totalSongsAmount total amount of songs in disc
     */
    int countTotalSongsAmount() throws RemoteException;

    /**
     * consult with the employee
     *
     * @param songs songs that client need to consult with
     * @return true if successfully consulted with the songs
     */
    boolean consultWithSongs(Songs songs) throws RemoteException;

    /**
     * sort songs by work duration in disc
     *
     * @param isReversed is list should be sorted in reversed order
     * @return sorted songs list
     */
    List<Songs> sortSongsByDuration(boolean isReversed) throws RemoteException;

    /**
     * select songs by both parameters(musician and below certain work duration)
     *
     * @param duration maximum work duration
     * @param musician name of the musician songs works in
     * @return list of songs with required musician with duration below parameter
     */
    List<Songs> selectSpecificSongs(double duration, String musician) throws RemoteException;

    /**
     * select songs of certain musician
     *
     * @param musician name of the musician whose songs is required
     * @return list of songs from required musician
     */
    List<Songs> selectSongsByMusician(String musician) throws RemoteException;

    /**
     * select songs with certain duration
     *
     * @param minDur minimal years of work
     * @param maxDur maximum years of work
     * @return list of songs with defined duration
     */
    List<Songs> selectSongsByDuration(Double minDur, Double maxDur) throws RemoteException;
}
