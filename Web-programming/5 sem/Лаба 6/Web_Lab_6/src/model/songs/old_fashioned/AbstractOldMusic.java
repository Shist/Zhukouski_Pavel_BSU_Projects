package model.songs.old_fashioned;

import model.songs.Songs;

/**
 * abstract class of old music
 *
 * @author Zhukouski Pavel
 * @version 1.0
 */
public abstract class AbstractOldMusic extends Songs {

    /**
     * number of worked likes
     */
    protected int likesAmount;

    /**
     * getter of worked likes
     */
    public int getShiftsAmount() {
        return likesAmount;
    }


    /**
     * Constructor, creates songs with name, price, duration and musician
     *
     * @param name         name of songs
     * @param price       price of songs
     * @param duration   duration of songs
     * @param musician   musician of songs
     * @param likesAmount amount of worked likes
     * @throws IllegalArgumentException if price, duration or shiftAmount is below 0
     */
    protected AbstractOldMusic(String name, double price, String musician, double duration, int likesAmount) {
        super(name, price, musician, duration);
        if(price < 0 || duration < 0 || likesAmount < 0) {
            throw new IllegalArgumentException();
        }
        this.likesAmount = likesAmount;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;


        Songs songs = (Songs) obj;
        AbstractOldMusic abstractOldMusic = (AbstractOldMusic) obj;

        return (abstractOldMusic.likesAmount == this.likesAmount)
                && songs.equals(this);
    }

    @Override
    public String toString() {
        String stringFromSuper = super.toString();
        return String.format("%sMonthly worked likes amount: %d\n", stringFromSuper, likesAmount);
    }

    @Override
    public int hashCode() {
        int hashCodeFromSuper = super.hashCode();
        return hashCodeFromSuper + likesAmount * 31;
    }

}
