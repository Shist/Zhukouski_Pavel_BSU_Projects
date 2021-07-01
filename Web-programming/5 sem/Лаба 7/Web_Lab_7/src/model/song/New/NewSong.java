package model.song.New;

import model.song.Song;

import java.util.Date;

/**
 * abstract class of New song
 *
 * @author Zhukouski Pavel
 * @version 1.0.0
 */
public abstract class NewSong extends Song {

    /**
     * percent of electronic sounds
     */
    protected double electronicSoundsPercents;

    /**
     * getter of percentage
     *
     * @return percentage
     */
    public double getElectronicSoundsPercents() {
        return electronicSoundsPercents;
    }

    /**
     * Constructor, creates song with name, time and dates
     *
     * @param name            name of song
     * @param time          time of song
     * @param releaseDate date when it was produced
     * @param genre  genre
     * @param electronicSoundsPercent electronic sounds percentage
     * @throws IllegalArgumentException if electronicSoundsPercents is bellow 0 or more than 100
     */
    protected NewSong(String name, double time, String releaseDate, String genre, double electronicSoundsPercent) {
        super(name, time, releaseDate, genre);
        if (electronicSoundsPercent < 0 && electronicSoundsPercent > 100) {
            throw new IllegalArgumentException();
        }
        this.electronicSoundsPercents = electronicSoundsPercent;
    }


    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;

        Song song = (Song) obj;
        NewSong newSong = (NewSong) obj;

        return (newSong.electronicSoundsPercents == this.electronicSoundsPercents)
                && song.equals(this);
    }

    @Override
    public String toString() {
        String stringFromSuper = super.toString();
        return String.format("%s Electronic sounds percent: %.2f\n", stringFromSuper, electronicSoundsPercents);
    }

    @Override
    public int hashCode() {
        int hashCodeFromSuper = super.hashCode();
        return hashCodeFromSuper + (int) electronicSoundsPercents * 31;
    }

}
