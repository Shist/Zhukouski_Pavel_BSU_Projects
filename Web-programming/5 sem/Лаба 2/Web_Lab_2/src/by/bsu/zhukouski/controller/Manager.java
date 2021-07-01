package by.bsu.zhukouski.controller;

import by.bsu.zhukouski.model.entity.Disc;

/**
 * Template Facade
 * Class Manager
 * @author Pavel Zhukouski, 3 course, 12 group
 * @version 1.0
 */

public class Manager {
    /**
     * Template - Facade
     * Function for writing to the console disc data
     * @param disc - disc
     */
    public void printDisc(Disc disc) {
        System.out.println(disc.getDisc().toString() + '\n');
    }

    /**
     * Function for writing to the console sorting abstract compositions by parameters
     */
    public void printSort() {
        SortAbstractComposition sort = new SortAbstractComposition();
        System.out.println("Sorting by name:\n" + sort.sortByName() + '\n');
        System.out.println("Sorting by author's name:\n" + sort.sortByAuthorName() + '\n');
        System.out.println("Sorting by duration:\n" + sort.sortByDuration() + '\n');
    }

    /**
     * Function for writing to the console finding abstract composition
     */
    public void printFind() {
        FindAbstractComposition find = new FindAbstractComposition();
        System.out.println("Finding Pop music:\n" + find.findPop() + '\n');
        System.out.println("Finding Rock music:\n" + find.findRock() + '\n');
        System.out.println("Finding Hip-hop music:\n" + find.findHipHop() + '\n');
    }

    /**
     * Function for writing to the console finding abstract composition by name
     * @param name - name
     */
    public void printFindByName(String name) {
        FindAbstractComposition find = new FindAbstractComposition();
        System.out.println("Finding by name: " + find.findByName(name) + '\n');
    }

    /**
     * Function for writing to the console finding abstract composition by author's name
     * @param authorName - name of the compositor
     */
    public void printFindByAuthorName(String authorName) {
        FindAbstractComposition find = new FindAbstractComposition();
        System.out.println("Finding by author's name: " + find.findByAuthorName(authorName) + '\n');
    }

    /**
     * Function for writing to the console finding abstract composition by duration
     * @param duration - duration
     */
    public void printFindByDuration(double duration) {
        FindAbstractComposition find = new FindAbstractComposition();
        System.out.println("Finding by duration: " + find.findByDuration(duration) + '\n');
    }

    /**
     * Function for writing to the console of finding abstract composition by name range
     * @param start - start of range of the first letter
     * @param end   - end of range of the first letter
     */
    public void printFindByNameRange(char start, char end) {
        FindAbstractComposition find = new FindAbstractComposition();
        System.out.println("Finding by name range: " + find.findByNameRange(start, end) + '\n');
    }

    /**
     * Function for writing to the console of finding abstract composition by author's name range
     * @param start - start of range of the first letter
     * @param end   - end of range of the first letter
     */
    public void printFindByAuthorNameRange(char start, char end) {
        FindAbstractComposition find = new FindAbstractComposition();
        System.out.println("Finding by author's name range: " + find.findByAuthorNameRange(start, end) + '\n');
    }

    /**
     * Function for writing to the console of finding abstract composition by duration range
     * @param min - min value of the duration
     * @param max - max value of the duration
     */
    public void printFindByDurationRange(double min, double max) {
        FindAbstractComposition find = new FindAbstractComposition();
        System.out.println("Finding by duration range: " + find.findByDurationRange(min, max) + '\n');
    }

    /**
     * Function for the writing count the sum duration of the disc items
     * @param disc - disc
     */
    public void printCountSum(Disc disc) {
        System.out.println("Sum = " + disc.countSum() + '\n');
    }
}
