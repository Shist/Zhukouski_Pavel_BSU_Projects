package by.bsu.zhukouski.view;

import by.bsu.zhukouski.controller.Manager;
import by.bsu.zhukouski.model.entity.*;
import by.bsu.zhukouski.model.exception.InvalidDataException;

/**
 * Class Main
 * @author Pavel Zhukouski, 3 course, 12 group
 * @version 1.0
 * Variant 5. Sound recording. Determine the hierarchy of musical compositions. Write the assembly to disk. Calculate the
 * duration. Carry out rearrangement of disc compositions based on one of the parameters. Find a composition that
 * matches a given range of parameters.
 */
public class Main {

    /**
     * Program entry point
     * @param args - arguments
     */
    public static void main(String[] args) {

        Manager wr = new Manager();

        AbstractComposition pop1 = null;
        AbstractComposition pop2 = null;
        AbstractComposition pop3 = null;
        AbstractComposition rock1 = null;
        AbstractComposition rock2 = null;
        AbstractComposition rock3 = null;
        AbstractComposition hip_hop1 = null;
        AbstractComposition hip_hop2 = null;
        AbstractComposition hip_hop3 = null;

        try {
            pop1 = new Pop(
                    "Growl",
                    "EXO",
                    207,
                    Pop.PopGenre.K_pop
            );
            pop2 = new Pop(
                    "Car Wash",
                    "Rose Royce",
                    379,
                    Pop.PopGenre.Disco
            );
            pop3 = new Pop(
                    "Again",
                    "Yui",
                    255,
                    Pop.PopGenre.J_pop
            );
            rock1 = new Rock(
                    "Rammstein",
                    "Mein Herz Brennt",
                    480,
                    Rock.RockGenre.Heavy_metal
            );
            rock2 = new Rock(
                    "Can't Help Falling in Love",
                    "Elvis Presley",
                    180,
                    Rock.RockGenre.Rock_n_roll
            );
            rock3 = new Rock(
                    "Voice of the soul",
                    "Death",
                    225,
                    Rock.RockGenre.Death_metal
            );
            hip_hop1 = new HipHop(
                    "Star shopping",
                    "Lil Peep",
                    244,
                    HipHop.HipHopGenre.EmoRap
            );
            hip_hop2 = new HipHop(
                    "Slam",
                    "Onyx",
                    217,
                    HipHop.HipHopGenre.HardcoreRap
            );
            hip_hop3 = new HipHop(
                    "Life is Good (feat. Drake)",
                    "Future",
                    237,
                    HipHop.HipHopGenre.MumbleRap
            );
        } catch (InvalidDataException e) {
            e.printStackTrace();
        }

        /*
         * Recording all tracks on disc
         * */

        assert pop1 != null;
        assert pop2 != null;
        assert pop3 != null;
        assert rock1 != null;
        assert rock2 != null;
        assert rock3 != null;
        assert hip_hop1 != null;
        assert hip_hop2 != null;
        assert hip_hop3 != null;

        pop1.recordOnDisc(Disc.getInstance());
        pop2.recordOnDisc(Disc.getInstance());
        pop3.recordOnDisc(Disc.getInstance());
        rock1.recordOnDisc(Disc.getInstance());
        rock2.recordOnDisc(Disc.getInstance());
        rock3.recordOnDisc(Disc.getInstance());
        hip_hop1.recordOnDisc(Disc.getInstance());
        hip_hop2.recordOnDisc(Disc.getInstance());
        hip_hop3.recordOnDisc(Disc.getInstance());

        System.out.println("Printing all information about the music on disc:");
        wr.printDisc(Disc.getInstance());
        System.out.println("Now, sorting all information:");
        wr.printSort();
        wr.printFind();
        System.out.println("Now, we will look for song Rammstein:");
        wr.printFindByName("Rammstein");
        System.out.println("Now, we will look for compositor Yui:");
        wr.printFindByAuthorName("Yui");
        System.out.println("Now, we will look for music with duration 244 seconds:");
        wr.printFindByDuration(244);
        System.out.println("Now, we will look for songs with name from A to M:");
        wr.printFindByNameRange('A', 'M');
        System.out.println("Now, we will look for songs with author's name from K to Y:");
        wr.printFindByAuthorNameRange('K', 'Y');
        System.out.println("Now, we will look for songs with duration from 195 to 235 seconds:");
        wr.printFindByDurationRange(195, 235);
        System.out.println("Whole duration of the album on the disc:");
        wr.printCountSum(Disc.getInstance());
        System.out.println("Clearing disc...");
        Disc.getInstance().clearDisc();
        System.out.println("Trying to print some information after clearing disc...");
        wr.printDisc(Disc.getInstance());
    }
}
