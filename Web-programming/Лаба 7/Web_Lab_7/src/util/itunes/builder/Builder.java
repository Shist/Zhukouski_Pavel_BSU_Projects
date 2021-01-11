package util.itunes.builder;

import model.song.Song;

import java.util.Date;

/**
 * Builder interface
 *
 * @author Zhukouski Pavel
 * @version 1.0.0
 */
public interface Builder {

    void setName(String name);

    void setTime(double time);

    void setReleaseDate(String date);

    void setGenre(String genre);

    void setElectronicSoundsPercent(double percent);

    void setAlbum(String album);

    void isFast(boolean isFast);

    void isSlow(boolean isSlow);

    void setIsCher(boolean isCher);

    void setIsSingerBlackAgain(boolean IsBlackAgain);

    void setIsSingerBlack(boolean isBlack);

    void reset();

    Song buildSongItem();
}
