package model.song.New;

import java.util.Date;

/**
 * @author Zhukouski Pavel
 * @version 1.0.0
 */
public class Rap extends NewSong {

    /**
     * Rap track
     */
    private boolean isFast;

    /**
     * getter if it is fast
     *
     * @return is fast
     */
    public boolean isFast() {
        return isFast;
    }

    /**
     * Constructor, creates song with name, time and dates
     *
     * @param name            name of song
     * @param time          time of song
     * @param releaseDate date when it was produced
     * @param genre  genre
     * @param electronicsPercent electronic sounds percentage
     * @param isFast       if is fast
     */
    public Rap(String name, double time, String releaseDate, String genre, double electronicsPercent, boolean isFast) {
        super(name, time, releaseDate, genre, electronicsPercent);
        this.isFast = isFast;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;

        NewSong newSong = (NewSong) obj;
        Rap rap = (Rap) obj;

        return (rap.isFast == this.isFast)
                && newSong.equals(this);
    }

    @Override
    public String toString() {
        String stringFromSuper = super.toString();
        return String.format("%sIs fast: %b\n", stringFromSuper, isFast);
    }

    @Override
    public int hashCode() {
        int hashCodeFromSuper = super.hashCode();
        return hashCodeFromSuper + (isFast ? 1 : -1) * 31;
    }

    @Override
    public String makeEffect() {
        var string = String.format("Rap is a new genre (song type) that can be angry or chill %s", (isFast ? " and is fast" : ""));
        return string;
    }

}
