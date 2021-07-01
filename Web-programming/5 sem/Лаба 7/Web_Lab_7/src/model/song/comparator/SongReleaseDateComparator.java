package model.song.comparator;

import model.song.Song;

import java.util.Comparator;

/**
 * Performances comparator class of song by manufacture date
 *
 * @author Zhukouski Pavel
 * @version 1.0.0
 */
public class SongReleaseDateComparator implements Comparator<Song> {

    @Override
    public int compare(Song o1, Song o2) {
        return o1.getReleaseDate().compareTo(o2.getReleaseDate());
    }

}
