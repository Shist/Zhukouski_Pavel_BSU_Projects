package model.song.Old;

import model.song.Song;

import java.util.Date;

/**
 * abstract class of Old song
 *
 * @author Zhukouski Pavel
 * @version 1.0.0
 */
public abstract class OldSong extends Song {

    /**
     * album
     */
    protected String Album;

    /**
     * getter of album
     *
     * @return album
     */
    public String getAlbum() {
        return Album;
    }

    /**
     * Constructor, creates song with name, time and dates
     *
     * @param name            name of song
     * @param time          time of song
     * @param releaseDate date when it was produced
     * @param genre  genre
     * @param Album album
     * @throws IllegalArgumentException if Album is bellow 0
     */
    protected OldSong(String name, double time, String releaseDate, String genre, String Album) {
        super(name, time, releaseDate, genre);
        if (Album.length() < 0)
            throw new IllegalArgumentException();
        this.Album = Album;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;


        Song song = (Song) obj;
        OldSong oldSong = (OldSong) obj;

        return (oldSong.Album == this.Album)
                && song.equals(this);
    }

    @Override
    public String toString() {
        String stringFromSuper = super.toString();
        String s=stringFromSuper + "Album: "+ Album;
        //return ("%sAlbum: %\n", stringFromSuper, Album);
        return s;
    }

    @Override
    public int hashCode() {
        int hashCodeFromSuper = super.hashCode();
        return hashCodeFromSuper +Album.hashCode() * 13;
    }

}
