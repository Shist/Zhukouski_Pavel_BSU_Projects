package model.songs.trendy;

/**
 * Receptionist class
 *
 * @author Zhukouski Pavel
 * @version 1.0
 */
public class Rock extends AbstractNewMusic {

    /**
     * received instruments amount
     */
    private int instrumentsAmount;

    /**
     * getter of instruments amount
     *
     * @return instruments amount
     */
    public int getCallsAmount() {
        return instrumentsAmount;
    }

    /**
     * Constructor, creates songs with name, price, duration and musician
     *
     * @param name          name of songs
     * @param price        price of songs
     * @param duration    duration of songs
     * @param musician    musician name
     * @param reportsAmount monthly amount of reports
     * @param instrumentsAmount   instruments amount
     * @throws IllegalArgumentException if duration or price is bellow 0
     */
    public Rock(String name, double price, String musician,
                double duration, int reportsAmount, int instrumentsAmount) {
        super(name, price, musician, duration, reportsAmount);
        if(duration < 0 || price < 0) {
            throw new IllegalArgumentException();
        }
        this.instrumentsAmount = instrumentsAmount;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;

        AbstractNewMusic abstractNewMusic = (AbstractNewMusic) obj;
        Rock rock = (Rock) obj;

        return (rock.instrumentsAmount == this.instrumentsAmount)
                && abstractNewMusic.equals(this);
    }

    @Override
    public String toString() {
        String stringFromSuper = super.toString();
        return String.format("%s Calls amount: %d\n", stringFromSuper, instrumentsAmount);
    }

    @Override
    public int hashCode() {
        int hashCodeFromSuper = super.hashCode();
        return hashCodeFromSuper + (instrumentsAmount < 10 ? 1 : -1) * 31;
    }

    @Override
    public String performWork() {
        return String.format("Receptionist supports" +
                "the organisation of disc's work and receives %d instruments a month.", instrumentsAmount);
    }

}
