package by.bsu.zhukouski.controller;

import by.bsu.zhukouski.model.entity.AbstractComposition;
import by.bsu.zhukouski.model.entity.Disc;

import java.util.Comparator;
import java.util.List;

/**
 * Class SortAbstractComposition for sort functions
 *
 * @author Pavel Zhukouski, 3 course, 12 group
 * @version 1.0
 */

public class SortAbstractComposition {

    /**
     * Function for sorting abstract compositions by name
     * @return list of abstract compositions
     */
    public List<AbstractComposition> sortByName() {
        List<AbstractComposition> list = Disc.getInstance().getDisc();
        list.sort(Comparator.comparing(AbstractComposition::getName));
        return list;
    }

    /**
     * Function for sorting abstract compositions by author's name
     * @return list of abstract compositions
     */
    public List<AbstractComposition> sortByAuthorName() {
        List<AbstractComposition> list = Disc.getInstance().getDisc();
        list.sort(Comparator.comparing(AbstractComposition::getAuthorName));
        return list;
    }

    /**
     * Function for sorting abstract compositions by duration
     * @return list of abstract compositions
     */
    public List<AbstractComposition> sortByDuration() {
        List<AbstractComposition> list = Disc.getInstance().getDisc();
        list.sort(Comparator.comparing(AbstractComposition::getDuration));
        return list;
    }
}
