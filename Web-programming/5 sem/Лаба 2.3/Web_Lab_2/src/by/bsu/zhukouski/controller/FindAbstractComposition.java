package by.bsu.zhukouski.controller;

import by.bsu.zhukouski.model.entity.*;

import java.util.List;
import java.util.stream.Collectors;

/**
 * Class FindAbstractComposition for find functions
 * @author Pavel Zhukouski, 3 course, 12 group
 * @version 1.0
 */

public class FindAbstractComposition {

    /**
     * Function for finding pop
     * @return list of pop
     */
    public List<AbstractComposition> findPop() {
        return Disc.getInstance().getDisc().stream().filter(Pop.class::isInstance).collect(Collectors.toList());
    }

    /**
     * Function for finding rock
     * @return list of rock
     */
    public List<AbstractComposition> findRock() {
        return Disc.getInstance().getDisc().stream().filter(Rock.class::isInstance).collect(Collectors.toList());
    }

    /**
     * Function for finding hip-hop
     * @return list of hip-hop
     */
    public List<AbstractComposition> findHipHop() {
        return Disc.getInstance().getDisc().stream().filter(HipHop.class::isInstance).collect(Collectors.toList());
    }

    /**
     * Function for finding abstract composition by name
     * @param name - name
     * @return list of abstract compositions
     */
    public List<AbstractComposition> findByName(String name) {
        return Disc.getInstance().getDisc().stream().filter(AbstractMusic -> AbstractMusic.getName().equals(name))
                .collect(Collectors.toList());
    }

    /**
     * Function for finding abstract composition by author's name
     * @param authorName - name
     * @return list of abstract compositions
     */
    public List<AbstractComposition> findByAuthorName(String authorName) {
        return Disc.getInstance().getDisc().stream().filter(AbstractMusic -> AbstractMusic.getAuthorName()
                .equals(authorName)).collect(Collectors.toList());
    }

    /**
     * Function for finding abstract composition by duration
     * @param duration - duration
     * @return list of abstract compositions
     */
    public List<AbstractComposition> findByDuration(double duration) {
        return Disc.getInstance().getDisc().stream().filter(AbstractMusic -> AbstractMusic.getDuration() == duration)
                .collect(Collectors.toList());
    }

    /**
     * Function for finding abstract composition by name range
     * @param start - start of range of the first letter
     * @param end   - end of range of the first letter
     * @return list of abstract compositions
     */
    public List<AbstractComposition> findByNameRange(char start, char end) {
        return Disc.getInstance().getDisc().stream().filter(AbstractMusic -> Character.toLowerCase(AbstractMusic.getName()
                .charAt(0)) >= Character.toLowerCase(start) && Character.toLowerCase(AbstractMusic.getName().charAt(0))
                <= Character.toLowerCase(end)).collect(Collectors.toList());
    }

    /**
     * Function for finding abstract composition by author's name range
     * @param start - start of range of the first letter
     * @param end   - end of range of the first letter
     * @return list of abstract compositions
     */
    public List<AbstractComposition> findByAuthorNameRange(char start, char end) {
        return Disc.getInstance().getDisc().stream().filter(AbstractMusic -> Character.toLowerCase(AbstractMusic.getAuthorName()
                .charAt(0)) >= Character.toLowerCase(start) && Character.toLowerCase(AbstractMusic.getAuthorName().charAt(0))
                <= Character.toLowerCase(end)).collect(Collectors.toList());
    }

    /**
     * Function for finding abstract composition by duration range
     * @param min - min value of the duration
     * @param max - max value of the duration
     * @return list of abstract compositions
     */
    public List<AbstractComposition> findByDurationRange(double min, double max) {
        return Disc.getInstance().getDisc().stream()
                .filter(AbstractMusic -> AbstractMusic.getDuration() >= min && AbstractMusic.getDuration() <= max)
                .collect(Collectors.toList());
    }
}
