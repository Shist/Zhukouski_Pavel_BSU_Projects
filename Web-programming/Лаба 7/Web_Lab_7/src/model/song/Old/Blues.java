package model.song.Old;

import java.util.Date;

/**
 * Blues track
 *
 * @author Zhukouski Pavel
 * @version 1.0.0
 */
public class Blues extends OldSong {

    /**
     * the isTheSingerBlackAgain
     */
    private boolean isTheSingerBlackAgain;

    /**
     * getter of isTheSingerBlackAgain
     *
     * @return isTheSingerBlackAgain
     */
    public boolean getTheSingerBlackAgain() {
        return isTheSingerBlackAgain;
    }

    /**
     * Constructor, creates song with name, time and dates
     *
     * @param name            name of song
     * @param time          time of song
     * @param releaseDate date when it was produced
     * @param genre  genre
     * @param Album album
     * @param isTheSingerBlackAgain isTheSingerBlackAgain
     */
    public Blues(String name, double time, String releaseDate, String genre, String Album, boolean isTheSingerBlackAgain) {
        super(name, time, releaseDate, genre, Album);
        this.isTheSingerBlackAgain = isTheSingerBlackAgain;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;

        OldSong oldSong = (OldSong) obj;
        Blues blues = (Blues) obj;

        return (blues.isTheSingerBlackAgain == this.isTheSingerBlackAgain)
                && oldSong.equals(this);
    }

    @Override
    public String toString() {
        String stringFromSuper = super.toString();
        return String.format("\n%sIs the singer black again: %b\n", stringFromSuper, isTheSingerBlackAgain);
    }

    @Override
    public int hashCode() {
        int hashCodeFromSuper = super.hashCode();
        return hashCodeFromSuper + (isTheSingerBlackAgain ? 13 : 17) * 31;
    }

    @Override
    public String makeEffect() {
        var string = String.format("Blues is a  musical form which was originated in the Deep South of the United States around the 1870s by African-Americans");
        return string;
    }
}
