package model.songs;

import java.io.Serializable;

/**
 * abstract class which describes songs
 *
 * @author Zhukouski Pavel
 * @version 1.0
 */

public abstract class Songs implements Serializable {

    /**
     * name of the songs
     */
    protected String name;

    /**
     * getter of name
     *
     * @return name of songs
     */
    public String getName() {
        return name;
    }

    /**
     * years of work in disc
     */
    protected double duration;

    /**
     * getter of duration
     *
     * @return duration of songs
     */
    public double getDuration() {
        return duration;
    }

    /**
     * monthly price of the songs
     */
    protected double price;

    /**
     * getter of songs price
     *
     * @return songs price
     */
    public double getPrice() {
        return price;
    }

    /**
     * name of the musician songs works
     */
    protected String musician;

    /**
     * getter of musician
     *
     * @return name od musician songs works
     */
    public String getMusician() {
        return musician;
    }

    /**
     * social skills of songs
     */
    protected boolean isSocial;

    /**
     * getter of social skills
     *
     * @return social skills of songs
     */
    public boolean getSociality() {
        return isSocial;
    }

    /**
     * Constructor, creates songs with name, price and dates
     *
     * @param name            name of songs
     * @param price          price of songs
     * @param musician      musician name songs works
     * @param duration      duration of songs
     * @throws IllegalArgumentException if duration or price is bellow 0
     */
    protected Songs(String name, double price, String musician, double duration) {
        if (price <= 0 || duration <= 0) {
            throw new IllegalArgumentException();
        }
        this.name = name;
        this.price = price;
        this.musician = musician;
        this.duration = duration;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;

        Songs songs = (Songs) obj;

        return price == songs.price
                && duration == songs.duration
                && name.equals(songs.name)
                && musician.equals(songs.musician);
    }

    @Override
    public String toString() {
        return String.format("Name: %s\nPrice: %.2f\nMusician: %s\nDuration: %.1f\n",
                name, price, musician, duration);
    }

    @Override
    public int hashCode() {
        int result = name != null ? name.hashCode() : 0;
        result += musician != null ? musician.hashCode() : 0;
        result += 31 * (result + price + duration);
        return result;
    }

    /**
     * perform some work
     *
     * @return string of working process
     */
    public abstract String performWork();

}
