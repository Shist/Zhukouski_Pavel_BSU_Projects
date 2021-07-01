package model.disc;

import model.songs.Songs;

import java.rmi.RemoteException;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

/**
 * this is disc that consists of several songs
 *
 * @author Zhukouski Pavel
 * @version 1.0
 */
public class Disc implements RemoteDisc {

    public static int TOTAL_VISITORS_ON_RECEPTION = 3;

    /**
     * lock to synchronize songs on disc
     */
    private Lock songsLock;

    /**
     * semaphore to synchronize reception
     */
    private Semaphore receptionSemaphore;

    /**
     * list of working songs
     */
    private List<Songs> songs;

    public void comeIn() throws RemoteException {
        try {
            Thread.sleep(1000);
            receptionSemaphore.acquire();
        } catch(InterruptedException e) {
            throw new RemoteException(e.getMessage());
        }
    }

    public void goOut() {
        receptionSemaphore.release();
    }

    /**
     * getter of songs
     *
     * @return songs list
     */
    public List<Songs> getSongs() {
        return songs;
    }

    /**
     * director of disc
     */
    private DiscManager director;

    /**
     * getter of director
     *
     * @return director
     */
    public DiscManager getDirector() {
        return director;
    }

    /**
     * Constructor that create songs with songs builder
     * @param director disc director
     */
    public Disc(DiscManager director) {
        this.director = director;
        songs = new ArrayList<>();
        songsLock = new ReentrantLock();
        receptionSemaphore = new Semaphore(TOTAL_VISITORS_ON_RECEPTION);
    }


    /**
     * add songs to songs list
     *
     * @param songs songs to add to list
     */
    public void addSongs(Songs songs) {
        songsLock.lock();
        this.songs.add(songs);
        songsLock.unlock();
    }

    /**
     * consult with the song
     *
     * @param songs songs that client need to consult with
     * @return true if successfully consulted with the songs
     */
    public boolean consultWithSongs(Songs songs) throws RemoteException {
        songsLock.lock();
        boolean result = this.songs.remove(songs);
        songsLock.unlock();
        return result;
    }

    /**
     * count total amount of songs in disc
     *
     * @return totalSongsAmount
     */
    public int countTotalSongsAmount() {
        songsLock.lock();
        List<Songs> curSongs = getSongs();
        songsLock.unlock();
        return director.countTotalSongsAmount(curSongs);
    }

    /**
     * select songs with certain duration
     *
     * @param minDur minimal duration of song
     * @param maxDur maximum duration of song
     * @return list of songs with defined duration
     */
    public List<Songs> selectSongsByDuration(Double minDur, Double maxDur) {
        songsLock.lock();
        List<Songs> curSongs = getSongs();
        songsLock.unlock();
        return director.selectSongsByDuration(curSongs, minDur, maxDur);
    }

    /**
     * select songs of certain musician
     *
     * @param musician name of the musician whose songs is required
     * @return list of songs from required musician
     */
    public List<Songs> selectSongsByMusician(String musician) {
        songsLock.lock();
        List<Songs> curSongs = getSongs();
        songsLock.unlock();
        return director.selectSongsByMusician(curSongs, musician);
    }

    /**
     * select songs by both parameters(musician and below certain work duration)
     *
     * @param duration maximum work duration
     * @param musician name of the musician songs works in
     * @return list of songs with required musician with duration below parameter
     */
    public List<Songs> selectSpecificSongs(double duration, String musician) {
        songsLock.lock();
        List<Songs> curSongs = getSongs();
        songsLock.unlock();
        return director.selectSpecificSongs(curSongs, duration, musician);
    }


    /**
     * sort songs by duration in disc
     *
     * @param isReversed is list should be sorted in reversed order
     * @return sorted songs list
     */
    public List<Songs> sortSongsByDuration(boolean isReversed) {
        songsLock.lock();
        List<Songs> curSongs = getSongs();
        songsLock.unlock();
        return director.sortSongsByDuration(curSongs, isReversed);
    }

}
