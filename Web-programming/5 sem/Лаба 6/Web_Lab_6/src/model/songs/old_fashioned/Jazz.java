package model.songs.old_fashioned;

/**
 * Class of Loader
 *
 * @author Zhukouski Pavel
 * @version 1.0
 */
public class Jazz extends AbstractOldMusic {

    /**
     * maximum kilos loader is able to lift
     */
    protected int maxKilos;

    /**
     * getter of max kilos amount
     */
    public int getMaxKilos() {
        return maxKilos;
    }


    /**
     * Constructor, creates songs with name, price, duration and musician
     *
     * @param name         name of songs
     * @param price       price of songs
     * @param duration   duration of songs
     * @param musician   musician of songs
     * @param likesAmount amount of worked likes
     * @param maxKilos     amount of lovers
     * @throws IllegalArgumentException if price, duration, shiftAmount or maxKilos is below 0
     */
    public Jazz(String name, double price, String musician, double duration,
                int likesAmount, int maxKilos) {
        super(name, price, musician, duration, likesAmount);
        if(price < 0 || duration < 0
                || likesAmount < 0 || maxKilos < 0) {
            throw new IllegalArgumentException();
        }
        this.maxKilos = maxKilos;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;


        AbstractOldMusic abstractOldMusic = (AbstractOldMusic) obj;
        Jazz jazz = (Jazz) obj;

        return (jazz.maxKilos == this.maxKilos)
                && abstractOldMusic.equals(this);
    }

    @Override
    public String toString() {
        String stringFromSuper = super.toString();
        return String.format("%sMax versions to sing: %d\n", stringFromSuper, maxKilos);
    }

    @Override
    public int hashCode() {
        int hashCodeFromSuper = super.hashCode();
        return hashCodeFromSuper + maxKilos * 31;
    }

    @Override
    public String performWork() {
        return String.format("Loader can sing" +
                "up to %d vesrions.", maxKilos);
    }
}

