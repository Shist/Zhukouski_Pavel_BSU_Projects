package model.song;

import java.io.Serializable;
import java.text.Format;
import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * abstract class which describes a song
 *
 * @author Zhukouski Pavel
 * @version 1.0.0
 */
public abstract class Song implements Serializable {

    /**
     * name of song
     */
    protected String name;

    /**
     * getter of name
     *
     * @return name of song
     */
    public String getName() {
        return name;
    }

    /**
     * time of song
     */
    protected double time;

    /**
     * getter of time
     *
     * @return time of song
     */
    public double getTime() {
        return time;
    }

    /**
     * the date when song was released
     */
    protected String releaseDate;

    /**
     * getter of production date
     *
     * @return date of production
     */
    public String getReleaseDate() {
        return releaseDate;
    }

    /**
     * the genre
     */
    protected String Genre;

    /**
     * getter of genre
     *
     * @return genre
     */
    public String getGenre() {
        return Genre;
    }


    /**
     * Constructor, creates song with name, time and dates
     *
     * @param name            name of song
     * @param time           time of song
     * @param releaseDate date when it was released
     * @param Genre  genre
     * @throws IllegalArgumentException if time is bellow 0 or releaseDate after Genre
     */
    protected Song(String name, double time, String releaseDate, String Genre) {
        if (time <= 0 ) {
            throw new IllegalArgumentException();
        }
        this.name = name;
        this.time = time;
        this.Genre = Genre;
        this.releaseDate = releaseDate;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;

        Song song = (Song) obj;

        return time == song.time
                && name.equals(song.name)
                && Genre.equals(song.Genre)
                && releaseDate.equals(song.releaseDate);
    }

    @Override
    public String toString() {
        //Format formatter = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");

        return String.format("Name: %s\nTime: %.2f\nReleased date: %s\nGenre: %s\n",
                name, time, releaseDate, Genre);
    }

    @Override
    public int hashCode() {
        int result = name != null ? name.hashCode() : 0;
        result += 31 * (result + Genre.hashCode() + releaseDate.hashCode() + time);
        return result;
    }

    /**
     * perform some work
     *
     * @return some string of song effect
     */
    public abstract String makeEffect();


}
