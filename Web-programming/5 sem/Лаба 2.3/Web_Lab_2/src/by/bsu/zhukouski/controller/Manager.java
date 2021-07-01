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
     * @return disc information
     */
    public String printDisc(Disc disc) {
        return disc.getDisc().toString() + '\n';
    }

    /**
     * Function for writing to the console sorting abstract compositions by parameters
     * @return disc information with sorting songs' names
     */
    public String printSortName() {
        SortAbstractComposition sort = new SortAbstractComposition();
        return sort.sortByName().toString();
    }

    /**
     * Function for writing to the console sorting abstract compositions by parameters
     * @return disc information with sorting songs' authors
     */
    public String printSortAuthor() {
        SortAbstractComposition sort = new SortAbstractComposition();
        return sort.sortByAuthorName().toString();
    }

    /**
     * Function for writing to the console sorting abstract compositions by parameters
     * @return disc information with sorting songs' durations
     */
    public String printSortDuration() {
        SortAbstractComposition sort = new SortAbstractComposition();
        return sort.sortByDuration().toString();
    }

    /**
     * Function for writing to the console finding abstract composition
     * @return disc information with HipHop type
     */
    public String printFindHipHop() {
        FindAbstractComposition find = new FindAbstractComposition();
        return find.findHipHop().toString();
    }

    /**
     * Function for writing to the console finding abstract composition
     * @return disc information with Pop type
     */
    public String printFindPop() {
        FindAbstractComposition find = new FindAbstractComposition();
        return find.findPop().toString();
    }

    /**
     * Function for writing to the console finding abstract composition
     * @return disc information with Rock type
     */
    public String printFindRock() {
        FindAbstractComposition find = new FindAbstractComposition();
        return find.findRock().toString();
    }

    /**
     * Function for writing to the console finding abstract composition by name
     * @param name - name
     * @return song from disc with chosen name
     */
    public String printFindByName(String name) {
        FindAbstractComposition find = new FindAbstractComposition();
        return find.findByName(name).toString();
    }

    /**
     * Function for writing to the console finding abstract composition by author's name
     * @param authorName - name of the compositor
     * @return song from disc with chosen author
     */
    public String printFindByAuthorName(String authorName) {
        FindAbstractComposition find = new FindAbstractComposition();
        return find.findByAuthorName(authorName).toString();
    }

    /**
     * Function for writing to the console finding abstract composition by duration
     * @param duration - duration
     * @return song from disc with chosen duration
     */
    public String printFindByDuration(double duration) {
        FindAbstractComposition find = new FindAbstractComposition();
        return find.findByDuration(duration).toString();
    }

    /**
     * Function for writing to the console of finding abstract composition by name range
     * @param start - start of range of the first letter
     * @param end   - end of range of the first letter
     * @return all songs which names start with "start" and end with "end"
     */
    public String printFindByNameRange(char start, char end) {
        FindAbstractComposition find = new FindAbstractComposition();
        return find.findByNameRange(start, end).toString();
    }

    /**
     * Function for writing to the console of finding abstract composition by author's name range
     * @param start - start of range of the first letter
     * @param end   - end of range of the first letter
     * @return all songs which authors start with "start" and end with "end"
     */
    public String printFindByAuthorNameRange(char start, char end) {
        FindAbstractComposition find = new FindAbstractComposition();
        return find.findByAuthorNameRange(start, end).toString();
    }

    /**
     * Function for writing to the console of finding abstract composition by duration range
     * @param min - min value of the duration
     * @param max - max value of the duration
     * @return all songs which durations start with "start" and end with "end"
     */
    public String printFindByDurationRange(double min, double max) {
        FindAbstractComposition find = new FindAbstractComposition();
        return find.findByDurationRange(min, max).toString();
    }

    /**
     * Function for the writing count the sum duration of the disc items
     * @param disc - disc
     * @return information about whole count of seconds with all songs from disc
     */
    public String printCountSum(Disc disc) {
        return "Sum = " + disc.countSum() + '\n';
    }

    /**
     * Function for full clearing the disc
     */
    public void ClearDisc(Disc disc) {
        disc.clearDisc();
    }
}
