package model.iTunes;

import model.song.Song;

import java.rmi.RemoteException;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

/**
 * this is iTunes that store and sell songs
 *
 * @author Zhukouski Pavel
 * @version 1.0.0
 */
public class iTunes {

    /**
     * list of stored songs
     */
    private List<Song> songs;

    /**
     * getter of songs
     *
     * @return song list
     */
    public List<Song> getSongs() {
        return songs;
    }

    /**
     * manager of iTunes
     */
    private iTunesManager manager;

    /**
     * getter of manager
     *
     * @return manager
     */
    public iTunesManager getManager() {
        return manager;
    }

    /**
     * Constructor that create songs with builder
     * @param manager iTunes manager
     */
    public iTunes(iTunesManager manager) {
        this.manager = manager;
        songs = new ArrayList<>();
    }

    /**
     * add song to songs list
     *
     * @param song song to add to list
     */
    public void addSong(Song song) {

        songs.add(song);

    }
    /**
     * count the total time of songs
     *
     * @return totalPrice
     */
    public double countTotalTime() {
        List<Song> tmpSongs = getSongs();
        return manager.countTotalTime(tmpSongs);
    }

    public boolean buySong(Song s) {
        boolean result = songs.remove(s);
        return result;
    }
    /**
     * sort songs by time
     *
     * @param isReversed is list should be reversed
     * @return sorted songs list
     */
    public List<Song> sortSongsByTime(boolean isReversed) {

        List<Song> tmpS = getSongs();
        return manager.sortSongsbyTime(tmpS, isReversed);
    }

    /**
     * sort songs by name
     *
     * @param isReversed is list should be reversed
     * @return sorted songs list
     */
    public List<Song> sortSongsByName(boolean isReversed) {
        List<Song> tmpS = getSongs();
        return manager.sortSongsByName(tmpS, isReversed);
    }

    /**
     * sort songs by genre
     *
     * @param isReversed is list should be reversed
     * @return sorted songs list
     */
    public List<Song> sortSongsByGenre(boolean isReversed) {

        List<Song> tmpS = getSongs();
        return manager.sortSongsByGenre(tmpS, isReversed);
    }

    /**
     * sort songs by release date
     *
     * @param isReversed is list should be reversed
     * @return sorted songs list
     */
    public List<Song> sortSongsByReleaseDate(boolean isReversed) {
        List<Song> tmpS = getSongs();

        return manager.sortSongsByReleaseDate(tmpS, isReversed);
    }

    /**
     * select items equal to time
     *
     * @param time some list
     * @return selected songs list
     */
    public List<Song> selectSongsByTime(double time) {

        List<Song> tmpS = getSongs();
        return manager.selectSongsByTimeRange(tmpS, time, time);
    }

    /**
     * select items between times
     *
     * @param mint some list
     * @param maxt some list
     * @return selected songs list
     */
    public List<Song> selectSongsByTimeRange(double mint, double maxt) {
        List<Song> tmpS = getSongs();

        return manager.selectSongsByTimeRange(tmpS, mint, maxt);
    }

    /**
     * select items by name
     *
     * @param name name of song
     * @return selected songs list
     */
    public List<Song> selectSongsByName(String name) {

        List<Song> tmpS = getSongs();
        return manager.selectSongsByName(tmpS, name);
    }

}
