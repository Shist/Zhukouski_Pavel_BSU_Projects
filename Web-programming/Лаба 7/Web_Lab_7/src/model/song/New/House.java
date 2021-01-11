package model.song.New;

import java.util.Date;

/**
 * House track
 *
 * @author Zhukouski Pavel
 * @version 1.0.0
 */
public class House extends NewSong {

    /**
     * is it slow
     */
    private boolean isSlow;


    /**
     * getter if it is slow
     *
     * @return is slow
     */
    public boolean isSlow() {
        return isSlow;
    }


    /**
     * Constructor, creates song with name, time and dates
     *
     * @param name            name of song
     * @param time          time of song
     * @param releaseDate date when it was produced
     * @param genre  genre
     * @param electronicsPercent electronic sounds percentage
     * @param isSlow       if it is slow
     */
    public House(String name, double time, String releaseDate, String genre, double electronicsPercent, boolean isSlow) {
        super(name, time, releaseDate, genre, electronicsPercent);
        this.isSlow = isSlow;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;

        NewSong newSong = (NewSong) obj;
        House house = (House) obj;

        return (house.isSlow == this.isSlow)
                && newSong.equals(this);
    }

    @Override
    public String toString() {
        String stringFromSuper = super.toString();
        return String.format("%sIs slow: %b\n", stringFromSuper, isSlow);
    }

    @Override
    public int hashCode() {
        int hashCodeFromSuper = super.hashCode();
        return hashCodeFromSuper + (isSlow ? 2 : -2) * 13;
    }

    @Override
    public String makeEffect() {
        var string = String.format("House is a new song type that is relaxing %s", (isSlow ? " and is slow" : ""));
        return string;
    }

}
