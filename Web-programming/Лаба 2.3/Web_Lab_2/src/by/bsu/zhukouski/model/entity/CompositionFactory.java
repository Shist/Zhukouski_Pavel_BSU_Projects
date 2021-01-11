package by.bsu.zhukouski.model.entity;

/**
 * Template - Factory (with the parent create method)
 * Class CompositionFactory
 * @author Pavel Zhukouski, 3 course, 12 group
 * @version 1.0
 */

public class CompositionFactory {
    /**
     * Function for creating abstract composition by type
     * @param typeOfComp - type of abstract composition
     * @return abstract composition
     */
    public AbstractComposition create(String typeOfComp) {
        AbstractComposition abstractComposition;
        switch (typeOfComp.toLowerCase()) {
            case "pop":
                abstractComposition = new Pop();
                break;
            case "rock":
                abstractComposition = new Rock();
                break;
            case "hip-hop":
                abstractComposition = new HipHop();
                break;
            default:
                throw new IllegalArgumentException("Wrong type!");
        }
        return abstractComposition;
    }
}
