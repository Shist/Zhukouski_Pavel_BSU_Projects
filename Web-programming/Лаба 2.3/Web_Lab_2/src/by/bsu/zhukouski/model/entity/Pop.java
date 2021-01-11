package by.bsu.zhukouski.model.entity;

import by.bsu.zhukouski.model.exception.InvalidDataException;

import java.util.Objects;

/**
 * Class Pop
 * @author Pavel Zhukouski, 3 course, 12 group
 * @version 1.0
 */

public class Pop extends AbstractComposition {

    /**
     * Enum type for the pop genre
     */
    public enum PopGenre {
        K_pop,
        Electropop,
        J_pop,
        Q_pop,
        Disco,
        Traditional_pop_music
    }


    /**
     * Pop genre
     */
    private PopGenre genre;

    /**
     * Create new object
     * @see Pop#Pop(String, String, double, PopGenre)
     */
    public Pop() {
    }

    /**
     * Pop constructor
     * Create new object with given values
     * @param name    - name
     * @param authorName - name of the compositor
     * @param duration    - duration
     * @param genre   - genre
     * @throws InvalidDataException if duration is negative
     * @see Pop#Pop()
     */
    public Pop(String name, String authorName, double duration, PopGenre genre) throws InvalidDataException {
        setName(name);
        setAuthorName(authorName);
        setDuration(duration);
        setGenre(genre);
    }

    /**
     * Function for getting field value {@link Pop#genre}
     * Getter for genre
     * @return genre
     */
    public PopGenre getGenre() {
        return genre;
    }

    /**
     * Function for setting the value of the field {@link Pop#genre}
     * Setter for genre
     * @param genre - genre
     */
    public void setGenre(PopGenre genre) {
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
        Pop pop = (Pop) o;
        return name.equals(pop.name) && authorName.equals(pop.authorName) &&
                duration == pop.duration && genre == pop.genre;
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
     * Function to write an pop to a string
     * @return string
     */
    @Override
    public String toString() {
        return "Pop: " + ", name = " + name + ", author's name = " + authorName +
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
