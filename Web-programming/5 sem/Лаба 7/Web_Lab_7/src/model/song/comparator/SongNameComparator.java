package model.song.comparator;

import model.song.Song;

import java.util.Comparator;

/**
 * Performances comparator class of song by name
 *
 * @author Zhukouski Pavel
 * @version 1.0.0
 */
public class SongNameComparator implements Comparator<Song> {

    @Override
    public int compare(Song o1, Song o2) {
        return o1.getName().compareTo(o2.getName());
    }

}
