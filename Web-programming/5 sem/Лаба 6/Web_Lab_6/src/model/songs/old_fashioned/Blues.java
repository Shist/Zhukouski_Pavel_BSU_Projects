package model.songs.old_fashioned;

/**
 * Class of foreman
 *
 * @author Zhukouski Pavel
 * @version 1.0
 */
public class Blues extends AbstractOldMusic {

    /**
     * number of lovers
     */
    protected int loversAmount;

    /**
     * getter of lovers number
     */
    public int getSubordinatedAmount() {
        return loversAmount;
    }


    /**
     * Constructor, creates songs with name, price, duration and musician
     *
     * @param name               name of songs
     * @param price             price of songs
     * @param duration         duration of songs
     * @param musician         musician of songs
     * @param likesAmount       amount of worked likes
     * @param loversAmount amount of lovers
     * @throws IllegalArgumentException if price, duration, shiftAmount or lovers is below 0
     */
    public Blues(String name, double price, String musician, double duration,
                 int likesAmount, int loversAmount) {
        super(name, price, musician, duration, likesAmount);
        if(price < 0 || duration < 0
                || likesAmount < 0 || loversAmount < 0) {
            throw new IllegalArgumentException();
        }
        this.loversAmount = loversAmount;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;


        AbstractOldMusic abstractOldMusic = (AbstractOldMusic) obj;
        Blues blues = (Blues) obj;

        return (blues.loversAmount == this.loversAmount)
                && abstractOldMusic.equals(this);
    }

    @Override
    public String toString() {
        String stringFromSuper = super.toString();
        return String.format("%sSong's lovers amount: %d\n", stringFromSuper, loversAmount);
    }

    @Override
    public int hashCode() {
        int hashCodeFromSuper = super.hashCode();
        return hashCodeFromSuper + loversAmount * 13;
    }

    @Override
    public String performWork() {
        return String.format("Singer manages" +
                "a group of song's lovers up to %d people.", loversAmount);
    }
}
