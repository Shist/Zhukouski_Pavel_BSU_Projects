package model;

import exception.BusWorkException;
import java.util.ArrayList;
import java.util.List;

public class Bus implements Runnable {

    /**
     * time in milisec to board or get of passenger
     */
    private final int TIME_FOR_ONE_PASSENGER = 1000;

    /**
     * bus route
     */
    private List<BusStop> route;

    /**
     * passenger list in bus
     */
    private ArrayList<Passenger> passengers = new ArrayList<>(20);


    /**
     * speed of bus
     */
    private double speed;

    /**
     * position at bus stop
     */
    private int positionAtBusStop;

    /**
     * constructor of bus
     *
     * @param busStops list of bus stops
     * @param speed    speed of bus
     */
    public Bus(List<BusStop> busStops, double speed) {
        this.route = busStops;
        this.speed = speed;
    }

    /**
     * constructor of bus
     *
     * @param busStops   list of bus stops
     * @param passengers inittial passengers
     * @param speed      speed of bus
     */
    public Bus(List<BusStop> busStops, List<Passenger> passengers, double speed) throws BusWorkException {
        this.route = busStops;
        this.speed = speed;
        if (passengers.size() > 20)
            throw new BusWorkException("Слишком много пассажиров для автобуса!");
        this.passengers.addAll(passengers);
    }

    @Override
    public void run() {
        String currentThreadName = Thread.currentThread().getName();

        for (int i = 0; i < route.size() - 1; i++) {

            BusStop previousBusStop = route.get(i);
            BusStop currentBusStop = route.get(i + 1);

            var busArrayList = currentBusStop.getBusArrayList();
            var currentBusStopExchanger = currentBusStop.getExchanger();
            var passengersOnStation = currentBusStop.getPassengers();

            double timeNecessaryForRide = previousBusStop.distanceTo(currentBusStop) / speed;

            try {
                System.out.println(currentThreadName + " напрвляется в " + currentBusStop.getName());
                Thread.sleep((long) timeNecessaryForRide);
                System.out.println(currentThreadName + " прибыл в " + currentBusStop.getName() + " и ожидает, пока на остановке освободится одно из двух мест...");
            } catch (InterruptedException e) {
                System.out.println(" не может заехать на остановку ");
                System.out.println(e.getMessage());
                continue;
            }

            try {
                positionAtBusStop = currentBusStop.arriveToBusStop(this);
                System.out.println(currentThreadName + " заехал на остановку " + currentBusStop.getName());
                System.out.println(currentBusStop.getName() + " - на данный момент здесь " + busArrayList.size() + "/2 автобус(а)");
                System.out.println(currentThreadName + " ждёт пассажиров ");
            } catch (InterruptedException e) {
                System.out.println(" кто-то помешал этому автобусу, он направляется к следующей остановке ");
                System.out.println(e.getMessage());
                continue;
            }

            int count = 0;
            ArrayList<Passenger> stayPassengers = new ArrayList<>();
            for (Passenger passenger : passengers) {
                if (passenger.getDestinationGoal().getName().equals(currentBusStop.getName().getName())) {
                    count += 1;
                    System.out.println(currentThreadName + " высадил " + passenger);
                    continue;
                }
                stayPassengers.add(passenger);
            }
            passengers = stayPassengers;
            try {
                currentBusStop.getPassengersBusStopLock().lock();
                Thread.sleep(count * TIME_FOR_ONE_PASSENGER);
                System.out.println(currentThreadName + " завершил высадку. Пассажиров вышло: " + count);
            } catch (InterruptedException e) {
                System.out.println(" Что-то помешало работе автобуса ");
                System.out.println(e.getMessage());
            }
            finally {
                currentBusStop.getPassengersBusStopLock().unlock();
            }
            count = 0;
            stayPassengers = new ArrayList<>();

            try {
                currentBusStop.getPassengersBusStopLock().lock();
                for (Passenger passenger :
                        passengersOnStation) {
                    for (int j = i + 1; j < route.size() - 1; j++) {
                        if (passenger.getDestinationGoal().equals(route.get(j).getName()) && passengers.size() < 20) {
                            passengers.add(passenger);
                            count += 1;
                            System.out.println(currentThreadName + " добавил " + passenger);
                            continue;
                        }
                        stayPassengers.add(passenger);
                    }
                }
                currentBusStop.setPassengers(stayPassengers);
            } finally {
                currentBusStop.getPassengersBusStopLock().unlock();
            }

            try {
                Thread.sleep(count * TIME_FOR_ONE_PASSENGER);
                System.out.println(currentThreadName + " завершил посадку. Пассажиров зашло: " + count);
            } catch (InterruptedException e) {
                System.out.println("Посадка отменена");
                System.out.println(e.getMessage());
            }

            try {
                if (currentBusStop.getBusArrayList().size() > 1) {
                    List<Passenger> passengerExchangeList = new ArrayList<>();
                    stayPassengers = new ArrayList<>();
                    for (Passenger passenger : passengers) {
                        if (positionAtBusStop != 1) {
                            if (passenger.isCantWaitAnyMore()) {
                                passengerExchangeList.add(passenger);
                            } else {
                                stayPassengers.add(passenger);
                            }
                        } else {
                            if (!passenger.isCantWaitAnyMore()) {
                                passengerExchangeList.add(passenger);
                            } else {
                                stayPassengers.add(passenger);
                            }
                        }
                    }
                    passengers = stayPassengers;
                    passengerExchangeList = currentBusStopExchanger.exchange(passengerExchangeList);
                    count = 0;
                    if (passengers.size() + passengerExchangeList.size() > 20) {
                        System.out.println(" не может обменять пассажиров, часть из них останется на остановке");
                        for (Passenger passenger : passengerExchangeList) {
                            if (passengers.size() > 20) {
                                currentBusStop.getPassengersBusStopLock().lock();
                                currentBusStop.getPassengers().add(passenger);
                                currentBusStop.getPassengersBusStopLock().unlock();
                            } else {
                                passengers.add(passenger);
                                count++;
                            }
                        }
                    } else {
                        count = passengerExchangeList.size();
                        passengers.addAll(passengerExchangeList);
                    }
                    System.out.println(currentThreadName + " принял " + count + " пассажиров от другого автобуса");
                }
            } catch (InterruptedException e) {
                System.out.println(" Что-то помешало работе автобуса ");
                System.out.println(e.getMessage());
            }

            System.out.println(currentThreadName + " покинул остановку с названием " + currentBusStop.getName());
            currentBusStop.leaveBusStop(this);

        }

        System.out.println(currentThreadName + " завершил работу ");
    }

}
