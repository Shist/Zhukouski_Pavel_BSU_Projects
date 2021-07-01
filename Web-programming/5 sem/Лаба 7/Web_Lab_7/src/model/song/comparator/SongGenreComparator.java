package model.song.comparator;

import model.song.Song;

import java.util.Comparator;


/**
 * Performances comparator class of song by expiration date
 *
 * @author Zhukouski Pavel
 * @version 1.0.0
 */
public class SongGenreComparator implements Comparator<Song> {

    @Override
    public int compare(Song o1, Song o2) {
        return o1.getGenre().compareTo(o2.getGenre());

    }

}
