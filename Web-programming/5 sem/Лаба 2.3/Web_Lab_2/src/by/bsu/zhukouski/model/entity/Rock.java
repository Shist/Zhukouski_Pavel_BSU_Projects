package by.bsu.zhukouski.model.entity;

import by.bsu.zhukouski.model.exception.InvalidDataException;

import java.util.Objects;

/**
 * Class Rock
 * @author Pavel Zhukouski, 3 course, 12 group
 * @version 1.0
 */

public class Rock extends AbstractComposition {

    /**
     * Enum type for the rock genre
     */
    public enum RockGenre {
        Rock_n_roll,
        Pop_rock,
        Mersibite,
        Heavy_metal,
        Glam_metal,
        Death_metal,
        Grindcore
    }


    /**
     * Hip-hop genre
     */
    private RockGenre genre;

    /**
     * Create new object
     * @see Rock#Rock(String, String, double, RockGenre)
     */
    public Rock() {
    }

    /**
     * Rock constructor
     * Create new object with given values
     * @param name    - name
     * @param authorName - name of the compositor
     * @param duration    - duration
     * @param genre   - genre
     * @throws InvalidDataException if duration is negative
     * @see Rock#Rock()
     */
    public Rock(String name, String authorName, double duration, RockGenre genre) throws InvalidDataException {
        setName(name);
        setAuthorName(authorName);
        setDuration(duration);
        setGenre(genre);
    }

    /**
     * Function for getting field value {@link Rock#genre}
     * Getter for genre
     * @return genre
     */
    public RockGenre getGenre() {
        return genre;
    }

    /**
     * Function for setting the value of the field {@link Rock#genre}
     * Setter for genre
     * @param genre - genre
     */
    public void setGenre(RockGenre genre) {
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
        Rock rock = (Rock) o;
        return name.equals(rock.name) && authorName.equals(rock.authorName) &&
                duration == rock.duration && genre == rock.genre;
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
     * Function to write an rock to a string
     * @return string
     */
    @Override
    public String toString() {
        return "Rock: " + ", name = " + name + ", author's name = " + authorName +
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
