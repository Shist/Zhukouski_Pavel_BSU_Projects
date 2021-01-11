package controller;

import exception.BusWorkException;
import model.Bus;
import model.BusStop;
import model.BusStopNameEnum;
import model.BusStopCoordinate;
import util.PassengerListGenerator;

import java.util.ArrayList;

public class Main {

    public static void main(String[] args) {

        System.out.println("Начало маршрута");

        BusStop busStopFirst = new BusStop(new BusStopCoordinate(-290, -185), BusStopNameEnum.SAINT_PETERSBURG);
        BusStop busStopSecond = new BusStop(new BusStopCoordinate(55, 55), BusStopNameEnum.VILNIUS);
        BusStop busStopThird = new BusStop(new BusStopCoordinate(430, 480), BusStopNameEnum.MINSK);
        BusStop busStopFourth = new BusStop(new BusStopCoordinate(1650, 580), BusStopNameEnum.MOSCOW);


        ArrayList<BusStop> firstRoute = new ArrayList<>();

        firstRoute.add(busStopFirst);
        firstRoute.add(busStopSecond);
        firstRoute.add(busStopThird);
        firstRoute.add(busStopFourth);

        Thread threadFirst = null;
        try {
            threadFirst = new Thread(new Bus(firstRoute, PassengerListGenerator.generatePassangers(), 10));
        } catch (BusWorkException e) {
            System.out.println("Произошла ошибка, работа автобуса невозможна");
            System.out.println( e.getMessage());
        }
        Thread threadSecond = null;
        try {
            threadSecond = new Thread(new Bus(firstRoute, PassengerListGenerator.generatePassangers(), 5));
        } catch (BusWorkException e) {
            System.out.println("Произошла ошибка, работа автобуса невозможна");
            System.out.println( e.getMessage());
        }
        Thread threadThird = new Thread(new Bus(firstRoute,5)); // Пустой автобус
        Thread threadFourth = new Thread(new Bus(firstRoute,30)); // Пустой автобус


        assert threadFirst != null;
        threadFirst.start();
        assert threadSecond != null;
        threadSecond.start();
        threadThird.start();
        threadFourth.start();

        try {
            threadFirst.join();
        } catch (InterruptedException e) {
            System.out.println( e.getMessage());
        }
        try {
            threadSecond.join();
        } catch (InterruptedException e) {
            System.out.println( e.getMessage());
        }
        try {
            threadThird.join();
        } catch (InterruptedException e) {
            System.out.println( e.getMessage());
        }
        try {
            threadFourth.join();
        } catch (InterruptedException e) {
            System.out.println( e.getMessage());
        }

        System.out.println("Завершение маршрута");
    }
}
