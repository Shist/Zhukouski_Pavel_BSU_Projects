package model.song.Old;

import java.util.Date;

/**
 * Jazz track
 * @author Zhukouski Pavel
 * @version 1.0.0
 */
public class Jazz extends OldSong {

    /**
     * is the singer Black
     */
    protected boolean isTheSingerBlack;

    /**
     * getter if the singer is black
     *
     * @return true if necessary, false in other way
     */
    public boolean isTheSingerBlack() {
        return isTheSingerBlack;
    }

    /**
     * Constructor, creates song with name, time and dates
     *
     * @param name            name of song
     * @param time          time of song
     * @param releaseDate date when it was produced
     * @param genre  genre
     * @param Album album
     * @param isTheSingerBlack show if doctor should prescribe it to person
     */
    public Jazz(String name, double time, String releaseDate, String genre, String Album, boolean isTheSingerBlack) {
        super(name, time, releaseDate, genre, Album);
        this.isTheSingerBlack = isTheSingerBlack;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;

        OldSong oldSong = (OldSong) obj;
        Jazz jazz = (Jazz) obj;

        return (jazz.isTheSingerBlack == this.isTheSingerBlack)
                && oldSong.equals(this);
    }

    @Override
    public String toString() {
        String stringFromSuper = super.toString();
        return String.format("\n%sIs the singer black: %b\n", stringFromSuper, isTheSingerBlack);
    }

    @Override
    public int hashCode() {
        int hashCodeFromSuper = super.hashCode();
        return hashCodeFromSuper + (isTheSingerBlack ? 13 : 17) * 31;
    }

    @Override
    public String makeEffect() {
        var string = String.format("is a music genre that originated in the African-American communities of New Orleans, United States");
        return string;
    }

}
