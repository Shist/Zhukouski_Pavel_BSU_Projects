package util.comparator;

import model.songs.Songs;

import java.util.Comparator;


/**
 * Comparator class of songs by work duration in disc
 *
 * @author Zhukouski Pavel
 * @version 1.0
 */
public class SongsComparator implements Comparator<Songs> {

    @Override
    public int compare(Songs st1, Songs st2) {
        return Double.compare(st1.getDuration(), st2.getDuration());
    }

}
