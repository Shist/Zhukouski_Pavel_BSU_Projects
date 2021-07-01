package util.builder;

import model.songs.Songs;
import model.songs.old_fashioned.Blues;
import model.songs.old_fashioned.Jazz;
import model.songs.old_fashioned.Country;
import model.songs.trendy.Pop;
import model.songs.trendy.Rock;

/**
 * Songs builder class that manage employees
 *
 * @author Zhukouski Pavel
 * @version 1.0
 */
public class SongsBuilder implements Builder {

    /**
     * songs name
     */
    private String name;

    /**
     * songs price
     */
    private Double price;

    /**
     * songs work duration
     */
    private Double duration;

    /**
     * musician songs works in
     */
    private String musician;

    /**
     * physical work or not
     */
    private Boolean isPhysical;

    /**
     * social songs or not
     */
    private Boolean isSocial;

    /**
     * weightlifting skills of songs
     */
    private Boolean isStrong;

    /**
     * number of worked shifts
     */
    protected Integer shiftsAmount;

    /**
     * monthly reports amount
     */
    protected Integer reportsAmount;

    /**
     * skill of shipbuilding
     */
    protected Boolean isShipbuilder;

    /**
     * maximum kilos loader is able to lift
     */
    protected Integer maxKilos;

    /**
     * number of subordinated
     */
    protected Integer subordinatedAmount;

    /**
     * received calls amount
     */
    private Integer callsAmount;

    /**
     * areas of calculation amount
     */
    private Integer calcAreasAmount;

    /**
     * set name
     */
    @Override
    public void setName(String name) {
        this.name = name;
    }

    /**
     * set price
     */
    @Override
    public void setPrice(double price) {
        this.price = price;
    }

    /**
     * set duration
     */
    @Override
    public void setDuration(double duration) {
        this.duration = duration;
    }

    /**
     * set musician
     */
    @Override
    public void setMusician(String musician) {
        this.musician = musician;
    }

    /**
     * set physicality of work
     */
    @Override
    public void setPhysicality(boolean isPhysical) {
        this.isPhysical = isPhysical;
    }

    /**
     * set social skills
     */
    @Override
    public void setSociality(boolean isSocial) {
        this.isSocial = isSocial;
    }

    /**
     * set weightlifting skills
     */
    @Override
    public void setWeightlifting(boolean isStrong) {
        this.isStrong = isStrong;
    }

    /**
     * set amount of shifts
     */
    @Override
    public void setShiftsAmount(int shiftsAmount) {
        this.shiftsAmount = shiftsAmount;
    }

    /**
     * set amount of reports
     */
    @Override
    public void setReportsAmount(int reportsAmount) {
        this.reportsAmount = reportsAmount;
    }

    /**
     * set shipbuilding skills
     */
    @Override
    public void setIsShipbuilder(boolean isShipbuilder) {
        this.isShipbuilder = isShipbuilder;
    }

    /**
     * set max kilos amount
     */
    @Override
    public void setMaxKilos(int maxKilos) {
        this.maxKilos = maxKilos;
    }

    /**
     * set subordinated amount
     */
    @Override
    public void setSubordinatedAmount(int subordinatedAmount) {
        this.subordinatedAmount = subordinatedAmount;
    }

    /**
     * set calls amount
     */
    @Override
    public void setCallsAmount(int callsAmount) {
        this.callsAmount = callsAmount;
    }

    /**
     * set calculation areas amount
     */
    @Override
    public void setCalcAreasAmount(int calcAreasAmount) {
        this.calcAreasAmount = calcAreasAmount;
    }


    /**
     * make all fields as null
     */
    @Override
    public void reset() {
        name = null;
        price = null;
        duration = null;
        musician = null;
        isPhysical = null;
        isSocial = null;
        isStrong = null;
        shiftsAmount = null;
        reportsAmount = null;
        isShipbuilder = null;
        maxKilos = null;
        subordinatedAmount = null;
        callsAmount = null;
        calcAreasAmount = null;
    }

    /**
     * make new employee
     *
     * @return disc employee with configured fields
     * @throws IllegalArgumentException if some field doesn't set
     */
    @Override
    public Songs makeEmployee() {
        if (name == null
                || price == null
                || duration == null) {
            throw new IllegalArgumentException();
        }
        else {
            if(shiftsAmount != null) {
                if(isPhysical) {
                    if(isSocial && (subordinatedAmount != null)) {
                        return new Blues(name, price, "Rose Royce", duration,
                                shiftsAmount, subordinatedAmount);
                    }
                    else if(isStrong && (maxKilos != null)) {
                        return new Jazz(name, price, "Elvis Presley", duration,
                                shiftsAmount, maxKilos);
                    }
                    else if(isShipbuilder != null) {
                        return new Country(name, price, "Onyx", duration,
                                shiftsAmount, isShipbuilder);
                    }
                }
            }
            else if(reportsAmount != null) {
                if(isSocial && (callsAmount != null)) {
                    return new Rock(name, price, "Lil Peep", duration,
                            reportsAmount, callsAmount);
                }
                else if(calcAreasAmount != null) {
                    return new Pop(name, price, "Yui", duration,
                            reportsAmount, calcAreasAmount);
                }
            }
            else {
                throw new IllegalArgumentException();
            }
        }
        throw new IllegalArgumentException();
    }
}
