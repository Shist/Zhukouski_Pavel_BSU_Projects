package by.bsu.zhukouski.model.entity;

import by.bsu.zhukouski.model.exception.InvalidDataException;

import java.util.Objects;

/**
 * Class Hip-hop
 *
 * @author Pavel Zhukouski, 3 course, 12 group
 * @version 1.0
 */

public class HipHop extends AbstractComposition {

    /**
     * Enum type for the hip-hop genre
     */
    public enum HipHopGenre {
        AlternativeHipHop,
        ChicanoRap,
        FreestyleRap,
        GangstaRap,
        HardcoreRap,
        TrapRap,
        MumbleRap,
        EmoRap
    }

    /**
     * Hip-hop genre
     */
    private HipHopGenre genre;

    /**
     * Create new object
     * @see HipHop#HipHop(String, String, double, HipHopGenre)
     */
    public HipHop() {
    }

    /**
     * HipHop constructor
     * Create new object with given values
     * @param name    - name
     * @param authorName - name of the compositor
     * @param duration    - duration
     * @param genre   - genre
     * @throws InvalidDataException if duration is negative
     * @see HipHop#HipHop()
     */
    public HipHop(String name, String authorName, double duration, HipHopGenre genre) throws InvalidDataException {
        setName(name);
        setAuthorName(authorName);
        setDuration(duration);
        setGenre(genre);
    }

    /**
     * Function for getting field value {@link HipHop#genre}
     * Getter for genre
     * @return genre
     */
    public HipHopGenre getGenre() {
        return genre;
    }

    /**
     * Function for setting the value of the field {@link HipHop#genre}
     * Setter for genre
     * @param genre - genre
     */
    public void setGenre(HipHopGenre genre) {
        this.genre = genre;
    }

    /**
     * Function for comparing objects
     * @param o - object to compare
     * @return Returns true - objects are equal, false - objects are not equal
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        HipHop hipHop = (HipHop) o;
        return name.equals(hipHop.name) && authorName.equals(hipHop.authorName) &&
                duration == hipHop.duration && genre == hipHop.genre;
    }

    /**
     * Function for finding hashCode
     * @return hashCode
     */
    @Override
    public int hashCode() {
        return Objects.hash(name, authorName, duration, genre);
    }

    /**
     * Function to write an hip-hop to a string
     * @return string
     */
    @Override
    public String toString() {
        return "Hip-hop: " + ", name = " + name + ", author's name = " + authorName +
                ", duration = " + duration + ", genre = " + genre + "\n";
    }

    /**
     * Function for placing the product on the disc
     * @param disc - disc
     * @return operation result
     */
    @Override
    public String recordOnDisc(Disc disc) {
        String result = "Hip-hop was recorded to the disc...";
        if (!disc.addToDisc(this)) {
            result = "Hip-hop was not recorded to the disc...";
        }
        return result;
    }
}
