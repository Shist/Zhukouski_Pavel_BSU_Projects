package util.manager;

import util.builder.Builder;
import model.songs.Songs;

import java.util.Random;

/**
 * manager that provides creating new songs
 *
 * @author Zhukouski Pavel
 * @version 1.0
 */
public class SongsManager {

    private Random random = new Random();

    /**
     * provide accountant creating
     *
     * @param builder    to make some songs
     * @param name       name of songs
     * @param musician musician name
     */
    public Songs provideAccountant(Builder builder, String name, String musician) {
        builder.setName(name);
        builder.setPrice(random.nextDouble() % 1500 + 400);
        builder.setDuration(random.nextDouble() % 10 + 1);
        builder.setMusician(musician);
        builder.setReportsAmount(random.nextInt() % 5 + 6);
        builder.setCalcAreasAmount(random.nextInt() % 3 + 1);
        builder.setPhysicality(false);
        builder.setSociality(false);
        return builder.makeEmployee();
    }

    /**
     * provide receptionist creating
     *
     * @param builder       to make some songs
     * @param name          name of songs
     * @param musician    musician name
     */
    public Songs provideReceptionist(Builder builder, String name, String musician) {
        builder.setName(name);
        builder.setPrice(random.nextDouble() % 1000 + 200);
        builder.setDuration(random.nextDouble() % 4 + 1);
        builder.setMusician(musician);
        builder.setReportsAmount(random.nextInt() % 6 + 7);
        builder.setCallsAmount(random.nextInt() % 200 + 50);
        builder.setPhysicality(false);
        builder.setSociality(true);
        return builder.makeEmployee();
    }

    /**
     * provide foreman creating
     *
     * @param builder       to make some songs
     * @param name          name of songs
     * @param musician    musician name
     */
    public Songs provideForeman(Builder builder, String name, String musician) {
        builder.setName(name);
        builder.setPrice(random.nextDouble() % 1500 + 200);
        builder.setDuration(random.nextDouble() % 6 + 15);
        builder.setMusician(musician);
        builder.setShiftsAmount(random.nextInt() % 5 + 15);
        builder.setSubordinatedAmount(random.nextInt() % 2 + 8);
        builder.setPhysicality(true);
        builder.setSociality(true);
        return builder.makeEmployee();
    }

    /**
     * provide loader creating
     *
     * @param builder       to make some songs
     * @param name          name of songs
     * @param musician    musician name
     */
    public Songs provideLoader(Builder builder, String name, String musician) {
        builder.setName(name);
        builder.setPrice(random.nextDouble() % 1000 + 400);
        builder.setDuration(random.nextDouble() % 6 + 15);
        builder.setMusician(musician);
        builder.setShiftsAmount(random.nextInt() % 5 + 12);
        builder.setMaxKilos(random.nextInt() % 15 + 15);
        builder.setPhysicality(true);
        builder.setWeightlifting(true);
        builder.setSociality(false);
        return builder.makeEmployee();
    }

    /**
     * provide welder creating
     *
     * @param builder       to make some songs
     * @param name          name of songs
     * @param musician    musician name
     */
    public Songs provideWelder(Builder builder, String name, String musician) {
        builder.setName(name);
        builder.setPrice(random.nextDouble() % 1500 + 200);
        builder.setDuration(random.nextDouble() % 6 + 15);
        builder.setMusician(musician);
        builder.setShiftsAmount(random.nextInt() % 5 + 15);
        builder.setIsShipbuilder(random.nextBoolean());
        builder.setPhysicality(true);
        builder.setSociality(false);
        builder.setWeightlifting(false);
        return builder.makeEmployee();
    }
}
