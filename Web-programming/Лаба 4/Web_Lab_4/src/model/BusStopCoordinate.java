package model;

/**
 * This class helps us to define place of each BusStop on map
 * Use it when we need distance between two stations
 *
 * @author Zhukouski Pavel
 */
public class BusStopCoordinate {

    /**
     * x, y coordinates
     */
    private final int x, y;

    /**
     * getter of x coordinate
     *
     * @return x coordinate
     */
    public int getX() {
        return x;
    }

    /**
     * getter of y coordinate
     *
     * @return y coordinate
     */
    public int getY() {
        return y;
    }

    /**
     * constructor
     *
     * @param x x coordinate
     * @param y y coordinate
     */
    public BusStopCoordinate(int x, int y) {
        this.x = x;
        this.y = y;
    }


    /**
     * calcilate distance between two points
     *
     * @param next next position
     * @return distance between two points
     */
    public double distanceTo(BusStopCoordinate next) {
        int prevX = this.getX();
        int prevY = this.getY();
        int nextX = next.getX();
        int nextY = next.getY();

        return Math.hypot(prevX - nextX, prevY - nextY);
    }

}
