package model.songs.trendy;

import model.songs.Songs;

/**
 * abstract class of financial job
 *
 * @author Zhukouski Pavel
 * @version 1.0
 */
public abstract class AbstractNewMusic extends Songs {

    /**
     * monthly reposts amount
     */
    protected int repostsAmount;

    /**
     * getter of reposts amount
     *
     * @return amount of monthly reposts
     */
    public int getReportsAmount() {
        return repostsAmount;
    }

    /**
     * Constructor, creates songs with name, price and duration
     *
     * @param name          name of songs
     * @param price        price of songs
     * @param duration    duration of songs
     * @param musician    musician name
     * @param repostsAmount monthly amount of reposts
     * @throws IllegalArgumentException if duration or price is bellow 0
     */
    protected AbstractNewMusic(String name, double price, String musician, double duration, int repostsAmount) {
        super(name, price, musician, duration);
        if (duration < 0 || price < 0)
            throw new IllegalArgumentException();
        this.repostsAmount = repostsAmount;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;


        Songs songs = (Songs) obj;
        AbstractNewMusic finantialJob = (AbstractNewMusic) obj;

        return (finantialJob.repostsAmount == this.repostsAmount)
                && songs.equals(this);
    }

    @Override
    public String toString() {
        String stringFromSuper = super.toString();
        return String.format("%sMonthly reposts amount: %d\n", stringFromSuper, repostsAmount);
    }

    @Override
    public int hashCode() {
        int hashCodeFromSuper = super.hashCode();
        return hashCodeFromSuper + repostsAmount * 13;
    }

}
