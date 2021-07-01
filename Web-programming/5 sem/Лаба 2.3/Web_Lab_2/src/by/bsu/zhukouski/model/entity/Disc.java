package by.bsu.zhukouski.model.entity;

import java.util.ArrayList;
import java.util.List;

// TODO
// 1) Добавить кнопку Print Disc Info
// 2) Добавить кнопку сортировки на диске по выбранному параметру (из комбобокса)
// 3) Добавить кнопку поиска какого-то элемента по введеённому (в текстбоксе) параметру (из комбобокса)

/**
 * Singleton template
 * Class Disc
 * @author Pavel Zhukouski, 3 course, 12 group
 * @version 1.0
 */

public class Disc {

    /**
     * Instance of disc
     */
    private static Disc instance = null;

    /**
     * Template - Composite (Linker)
     * Disc
     */
    private static List<AbstractComposition> disc;

    /**
     * Create new object
     */
    public Disc() {
    }

    /**
     * Function for getting field value {@link Disc#instance}
     * @return instance
     */
    public static Disc getInstance() {
        if (instance == null) {
            instance = new Disc();
            disc = new ArrayList<>();
        }
        return instance;
    }

    /**
     * Function for getting field value {@link Disc#disc}
     * @return disc
     */
    public List<AbstractComposition> getDisc() { return disc; }

    /**
     * Function for adding abstract composition to the disc
     * @param abstractComposition - abstract composition
     * @return result of adding
     */
    public boolean addToDisc(AbstractComposition abstractComposition) {
        if (abstractComposition == null) {
            return false;
        }
        return disc.add(abstractComposition);
    }

    /**
     * Function for cleaning disc
     */
    public void clearDisc() {
        disc.clear();
    }

    /**
     * Function count the sum duration of the disc items
     * @return result of sum
     */
    public double countSum() {
        return disc.stream().mapToDouble(AbstractComposition::getDuration).sum();
    }
}
