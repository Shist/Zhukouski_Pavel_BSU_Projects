package model.songs.trendy;
/**
 * Accountant class
 *
 * @author Zhukouski Pavel
 * @version 1.0
 */
public class Pop extends AbstractNewMusic {

    /**
     * bits of calculation amount
     */
    private int calcAreasAmount;

    /**
     * getter of calculationAreas amount
     *
     * @return calculation bits amount
     */
    public int getCalculationAreasAmount() {
        return calcAreasAmount;
    }

    /**
     * Constructor, creates songs with name, price, duration and musician
     *
     * @param name                      name of songs
     * @param price                    price of songs
     * @param duration                duration of songs
     * @param musician                musician name
     * @param reportsAmount             monthly amount of reports
     * @param calcAreasAmount           calculation bits amount
     * @throws IllegalArgumentException if duration or price is bellow 0
     */
    public Pop(String name, double price, String musician,
               double duration, int reportsAmount, int calcAreasAmount) {
        super(name, price, musician, duration, reportsAmount);
        if(duration < 0 || price < 0) {
            throw new IllegalArgumentException();
        }
        this.calcAreasAmount = calcAreasAmount;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;

        AbstractNewMusic abstractNewMusic = (AbstractNewMusic) obj;
        Pop accountant = (Pop) obj;

        return (accountant.calcAreasAmount == this.calcAreasAmount)
                && abstractNewMusic.equals(this);
    }

    @Override
    public String toString() {
        String stringFromSuper = super.toString();
        return String.format("%s Calculation bits amount: %d\n", stringFromSuper, calcAreasAmount);
    }

    @Override
    public int hashCode() {
        int hashCodeFromSuper = super.hashCode();
        return hashCodeFromSuper + (calcAreasAmount < 5 ? 1 : -1) * 13;
    }

    @Override
    public String performWork() {
        return String.format("Accountant calculates" +
                "financial data of disc in %d spheres.", calcAreasAmount);
    }
}
