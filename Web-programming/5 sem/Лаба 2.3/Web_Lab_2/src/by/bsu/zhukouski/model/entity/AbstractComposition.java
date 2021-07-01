package by.bsu.zhukouski.model.entity;

import by.bsu.zhukouski.model.exception.InvalidDataException;

/**
 * Class AbstractComposition
 * @author Pavel Zhukouski, 3 course, 12 group
 * @version 1.0
 */

public abstract class AbstractComposition {

    /**
     * Name of the composition
     */
    protected String name;

    /**
     * Name of the compositor
     */
    protected String authorName;

    /**
     * Duration of the composition
     */
    protected double duration;

    /**
     * Getter for name
     * {@link AbstractComposition#name}
     * @return name
     */
    public String getName()
    {
        return name;
    }

    /**
     * Setter for name
     * {@link AbstractComposition#name}
     * @param name - name
     */
    public void setName(String name) throws InvalidDataException
    {
        if (name.equals(""))
        {
            throw new InvalidDataException("Name can't be empty!");
        }
        this.name = name;
    }

    /**
     * Getter for compositor's name
     * {@link AbstractComposition#authorName}
     * @return name
     */
    public String getAuthorName()
    {
        return authorName;
    }

    /**
     * Setter for compositor's name
     * {@link AbstractComposition#authorName}
     * @param authorName - name of the compositor
     */
    public void setAuthorName(String authorName) throws InvalidDataException
    {
        if (authorName.equals(""))
        {
            throw new InvalidDataException("Author's name can't be empty!");
        }
        this.authorName = authorName;
    }

    /**
     * Getter for duration
     * {@link AbstractComposition#duration}
     * @return duration of the abstract composition
     */
    public double getDuration() {
        return duration;
    }

    /**
     * Setter for duration
     * {@link AbstractComposition#duration}
     * @param duration - duration of the composition
     * @throws InvalidDataException if duration is negative
     */
    public void setDuration(double duration) throws InvalidDataException
    {
        if (duration <= 0.0)
        {
            throw new InvalidDataException("Duration of the composition can't be negative or zero!");
        }
        this.duration = duration;
    }

    /**
     * Function for recoding the composition on the disc
     * @param disc - disc which will be used for recording
     * @return operation result
     */
    public abstract String recordOnDisc(Disc disc);
}
