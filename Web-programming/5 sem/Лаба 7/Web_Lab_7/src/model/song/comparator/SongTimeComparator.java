package model.song.comparator;

import model.song.Song;

import java.util.Comparator;

/**
 * Performances comparator class of song by time
 *
 * @author Zhukouski Pavel
 * @version 1.0.0
 */
public class SongTimeComparator implements Comparator<Song> {

    @Override
    public int compare(Song o1, Song o2) {
        return Double.compare(o1.getTime(), o2.getTime());
    }

}
