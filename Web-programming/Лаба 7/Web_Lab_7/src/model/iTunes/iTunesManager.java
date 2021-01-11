package model.iTunes;

import model.song.Song;
import model.song.comparator.SongGenreComparator;
import model.song.comparator.SongNameComparator;
import model.song.comparator.SongReleaseDateComparator;
import model.song.comparator.SongTimeComparator;

import java.util.Comparator;
import java.util.List;
import java.util.stream.Collectors;

/**
 * this is iTunes  manager that control iTunes
 *
 * @author Zhukouski Pavel
 * @version 1.0.0
 */
public class iTunesManager {

    /**
     * count the total time of songs
     *
     * @param songs list of songs
     * @return totalPrice
     */
    public double countTotalTime(List<Song> songs) {
        double totalTime = 0;
        for (Song song :
                songs) {
            totalTime += song.getTime();
        }
        return totalTime;
    }

    /**
     * sort songs by time
     *
     * @param songs  list of songs
     * @param isReversed is list should be reversed
     * @return sorted songs list
     */
    public List<Song> sortSongsbyTime(List<Song> songs, boolean isReversed) {
        Comparator<Song> timeComparator = new SongTimeComparator();
        if (isReversed) {
            timeComparator = timeComparator.reversed();
        }
        return sortListWithComparator(songs, timeComparator);
    }

    /**
     * sort songs by name
     *
     * @param songs  list of songs
     * @param isReversed is list should be reversed
     * @return sorted songs list
     */
    public List<Song> sortSongsByName(List<Song> songs, boolean isReversed) {
        Comparator<Song> nameComparator = new SongNameComparator();
        if (isReversed) {
            nameComparator = nameComparator.reversed();
        }
        return sortListWithComparator(songs, nameComparator);
    }

    /**
     * sort songs by genre
     *
     * @param songs  list of songs
     * @param isReversed is list should be reversed
     * @return sorted songs list
     */
    public List<Song> sortSongsByGenre(List<Song> songs, boolean isReversed) {
        Comparator<Song> genreComparator = new SongGenreComparator();
        if (isReversed) {
            genreComparator = genreComparator.reversed();
        }
        return sortListWithComparator(songs, genreComparator);
    }

    /**
     * sort songs by release date
     *
     * @param songs  list of songs
     * @param isReversed is list should be reversed
     * @return sorted songs list
     */
    public List<Song> sortSongsByReleaseDate(List<Song> songs, boolean isReversed) {
        Comparator<Song> ReleaseDateComparator = new SongReleaseDateComparator();
        if (isReversed) {
            ReleaseDateComparator = ReleaseDateComparator.reversed();
        }
        return sortListWithComparator(songs, ReleaseDateComparator);
    }

    /**
     * sort list by comparator
     *
     * @param list       some list
     * @param comparator condition to sort
     * @return sorted medicines list
     */
    private List<Song> sortListWithComparator(List<Song> list, Comparator<Song> comparator) {
        return list.stream()
                .sorted(comparator)
                .collect(Collectors.toList());
    }

    /**
     * select items equal to time
     *
     * @param songs list of songs
     * @param time    some list
     * @return selected songs list
     */
    public List<Song> selectSongsByTime(List<Song> songs, double time) {
        return selectSongsByTimeRange(songs, time, time);
    }

    /**
     * select items between time
     *
     * @param songs list of songs
     * @param minT  some list
     * @param maxT some list
     * @return selected songs list
     */
    public List<Song> selectSongsByTimeRange(List<Song> songs, double minT, double maxT) {
        return songs.stream()
                .filter(song -> song.getTime() >= minT && song.getTime() <= maxT)
                .collect(Collectors.toList());
    }

    /**
     * select items by name
     *
     * @param songs list of songs
     * @param name      name of song
     * @return selected songs list
     */
    public List<Song> selectSongsByName(List<Song> songs, String name) {
        return songs.stream()
                .filter(song -> song.getName().equals(name))
                .collect(Collectors.toList());
    }
}
