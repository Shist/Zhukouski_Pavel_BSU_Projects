package model;

/**
 * name of bus stops
 *
 * @author Zhukouski Pavel
 */
public enum BusStopNameEnum {

    MINSK("Minsk"),
    VILNIUS("Vilnius") ,
    SAINT_PETERSBURG("Saint Petersburg"),
    MOSCOW("Moscow");

    private String name;

    BusStopNameEnum(String name) {
        this.name = name;
    }

    public String getName() {
        return "station " + name;
    }

}
