package model.song.Old;

import java.util.Date;

/**
 * Disco track
 *
 * @author Zhukouski Pavel
 * @version 1.0.0
 */
public class Disco extends OldSong {

    /**
     * is it Cher
     */
    private boolean isThisCher;

    /**
     * getter is it Cher
     *
     * @return is it Cher
     */
    public boolean getIsThisCher() {
        return isThisCher;
    }

    /**
     * Constructor, creates song with name, time and dates
     *
     * @param name            name of song
     * @param time          time of song
     * @param releaseDate date when it was produced
     * @param genre  genre
     * @param Album album
     * @param isThisCher if Cher is playing
     * @throws IllegalArgumentException if dose in mg is bellow 0
     */
    public Disco(String name, double time, String releaseDate, String genre, String Album, boolean isThisCher) {
        super(name, time, releaseDate, genre, Album);
        this.isThisCher = isThisCher;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;

        OldSong oldSong = (OldSong) obj;
        Disco disco = (Disco) obj;

        return (disco.isThisCher == this.isThisCher)
                && oldSong.equals(this);
    }

    @Override
    public String toString() {
        String stringFromSuper = super.toString();
        return String.format("%sIs this Cher: %b\n", stringFromSuper, isThisCher);
        //return String.format("%Is this Cher : %.2f\n", stringFromSuper, isThisCher);
    }

    @Override
    public int hashCode() {
        int hashCodeFromSuper = super.hashCode();
        return hashCodeFromSuper + (isThisCher  ? 13 : 17) * 31;
    }

    @Override
    public String makeEffect() {
        var string = String.format("Disco is a genre of dance music and a subculture that emerged in the 1970s from the United States' urban nightlife scene.\n" + "\n");
        return string;
    }
}