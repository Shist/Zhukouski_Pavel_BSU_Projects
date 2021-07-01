package model;

import util.PassengerListGenerator;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Exchanger;
import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

/**
 * common resource for buses
 *
 * @author Zhukouski Pavel
 */
public class BusStop {

    /**
     * passengers list waiting on bus stop
     */
    private List<Passenger> passengers;


    /**
     * getter of passengers
     */
    public List<Passenger> getPassengers() {
        return passengers;
    }

    /**
     * setter of passengers
     */
    public void setPassengers(List<Passenger> passengers) {
        this.passengers = passengers;
    }

    /**
     * exchanger passengers list going to next bus
     */
    private Exchanger<List<Passenger>> exchanger = new Exchanger<>();

    /**
     * getter of exchanger passengers
     */
    public Exchanger<List<Passenger>> getExchanger() {
        return exchanger;
    }

    /**
     * bus stop position
     */
    private BusStopCoordinate busStopCoordinate;

    /**
     * getter of bus stop position
     */
    public BusStopCoordinate getPosition() {
        return busStopCoordinate;
    }

    /**
     * bus stop name
     */
    private BusStopNameEnum name;

    /**
     * getter of bus stop name
     */
    public BusStopNameEnum getName() {
        return name;
    }

    /**
     * max buses can take place on bus stop at one time
     */
    private final int maxBusesAmount = 2;

    /**
     * synchronize busesSemaphore buses on bus stop
     */
    private Semaphore busesSemaphore;

    /**
     * getter of synchronize busesSemaphore
     */
    public Semaphore getBusesSemaphore() {
        return busesSemaphore;
    }

    /**
     * list of buses, which occupied station
     */
    private ArrayList<Bus> busArrayList = new ArrayList<>(maxBusesAmount);

    /**
     * getter of occupied station buses
     */
    public ArrayList<Bus> getBusArrayList() {
        return busArrayList;
    }

    /**
     * lock for passengers on bus stop
     */
    private Lock passengersBusStopLock;

    /**
     * getter of passengers locker
     */
    public Lock getPassengersBusStopLock() {
        return passengersBusStopLock;
    }

    /**
     * constructor of bus stop
     *
     * @param busStopCoordinate        position of bus stop
     * @param busStopNameEnum name of bus stop
     */
    public BusStop(BusStopCoordinate busStopCoordinate, BusStopNameEnum busStopNameEnum) {
        passengers = PassengerListGenerator.generatePassangers();
        this.busStopCoordinate = busStopCoordinate;
        this.name = busStopNameEnum;
        busesSemaphore = new Semaphore(maxBusesAmount, false);
        passengersBusStopLock = new ReentrantLock();
    }

    /**
     * calcilate distance between two bus stops
     *
     * @param next next bus stop
     * @return distance between two bus stops
     */
    public double distanceTo(BusStop next) {
        return busStopCoordinate.distanceTo(next.busStopCoordinate);
    }

    @Override
    public String toString() {
        return "BusStop{" +
                ", position=" + busStopCoordinate +
                ", name='" + name + '\'' +
                '}';
    }


    /**
     * synchronized method to add bus to bus station
     * *
     * @param bus bus
     * @throws InterruptedException if cant semaphore
     * @return position at bus stop
     */
    public int arriveToBusStop(Bus bus) throws InterruptedException {
        busesSemaphore.acquire();
        busArrayList.add(bus);
        return busArrayList.size() - 1;
    }

    /**
     * remove bus to bus station
     *
     * @param bus bus
     */
    public void leaveBusStop(Bus bus) {
        busArrayList.remove(bus);
        busesSemaphore.release();
    }
}
