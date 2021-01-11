package model.disc;

import model.songs.Songs;
import util.comparator.SongsComparator;

import java.util.Comparator;
import java.util.List;
import java.util.ArrayList;
import java.util.stream.Collectors;

/**
 * this is disc director that controls the disc
 *
 * @author Zhukouski Pavel
 * @version 1.0
 */
public class DiscManager {

    /**
     * count total amount of song in disc
     *
     * @param songs list of disc song
     * @return totalSongsAmount total amount of song in disc
     */
    public int countTotalSongsAmount(List<Songs> songs) {
        return songs.size();
    }

    /**
     * select song with certain duration
     *
     * @param songs song list
     * @param minDur minimal years of work
     * @param maxDur maximum years of work
     * @return songList list of song with appropriate duration
     */
    public List<Songs> selectSongsByDuration(List<Songs> songs, Double minDur, Double maxDur) {
        ArrayList<Songs> songList = new ArrayList<>();
        for (Songs song :
                songs) {
            if(song.getDuration() <= maxDur
                    && song.getDuration() >= minDur) {
                songList.add(song);
            }
        }
        return songList;
    }

    /**
     * select song from certain musician
     *
     * @param songs song list
     * @param musician name of the required musician
     * @return songList list of song with appropriate musician name
     */
    public List<Songs> selectSongsByMusician(List<Songs> songs, String musician) {
        ArrayList<Songs> songList = new ArrayList<>();
        for (Songs song :
                songs) {
            if(song.getMusician().equals(musician)) {
                songList.add(song);
            }
        }
        return songList;
    }

    /**
     * select specific song of disc
     *
     * @param songs list of song
     * @param duration maximum years of work in disc
     * @param musician name of musician song work
     * @return songList required song list
     */
    public List<Songs> selectSpecificSongs(List<Songs> songs, Double duration, String musician) {
        ArrayList<Songs> songList = new ArrayList<>();
        for (Songs song :
                songs) {
            if((song.getDuration() <= duration) && (song.getMusician().equals(musician))) {
                songList.add(song);
            }
        }
        return songList;
    }

    /**
     * sort song by work duration in disc
     *
     * @param songs song list of disc
     * @param isReversed is list should be sorted in reversed order
     * @return sorted song list
     */
    public List<Songs> sortSongsByDuration(List<Songs> songs, boolean isReversed) {
        Comparator<Songs> durComparator = new SongsComparator();
        if(isReversed) {
            durComparator = durComparator.reversed();
        }
        return songs.stream()
                .sorted(durComparator)
                .collect(Collectors.toList());
    }
}