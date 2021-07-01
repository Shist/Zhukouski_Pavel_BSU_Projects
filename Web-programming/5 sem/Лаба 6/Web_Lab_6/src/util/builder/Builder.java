package util.builder;

import model.songs.Songs;

/**
 * Builder interface
 *
 * @author Zhukouski Pavel
 * @version 1.0
 */
public interface Builder {

    void setName(String name);

    void setPrice(double price);

    void setMusician(String musician);

    void setDuration(double duration);

    void setPhysicality(boolean isPhysical);

    void setSociality(boolean isSocial);

    void setWeightlifting(boolean isStrong);

    void setShiftsAmount(int shiftsAmount);

    void setReportsAmount(int reportsAmount);

    void setIsShipbuilder(boolean isShipbuilder);

    void setMaxKilos(int maxKilos);

    void setSubordinatedAmount(int subordinatedAmount);

    void setCallsAmount(int callsAmount);

    void setCalcAreasAmount(int calcAreasAmount);

    void reset();

    Songs makeEmployee();
}
