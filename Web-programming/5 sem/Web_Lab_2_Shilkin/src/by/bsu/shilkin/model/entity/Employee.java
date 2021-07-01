package by.bsu.shilkin.model.entity;

import by.bsu.shilkin.model.exception.InvalidDataException;

/**
 * Class Employee
 * @author Egor Shilkin
 * @version 1.0
 */

public abstract class Employee {

    /**
     * Name of employee
     */
    protected String name;

    /**
     * Surname of employee
     */
    protected String surname;

    /**
     * Experience of employee
     */
    protected int exp;

    /**
     * Getter for name
     * {@link Employee#name}
     * @return name
     */
    public String getName()
    {
        return name;
    }

    /**
     * Setter for name
     * {@link Employee#name}
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
     * Getter for surname
     * {@link Employee#surname}
     * @return name
     */
    public String getSurname()
    {
        return surname;
    }

    /**
     * Setter for surname
     * {@link Employee#surname}
     * @param surname - surname of employee
     */
    public void setSurname(String surname) throws InvalidDataException
    {
        if (surname.equals(""))
        {
            throw new InvalidDataException("Surname can't be empty!");
        }
        this.surname = surname;
    }

    /**
     * Getter for experience
     * {@link Employee#exp}
     * @return experience of the employee
     */
    public int getExperience() {
        return exp;
    }

    /**
     * Setter for experience
     * {@link Employee#exp}
     * @param exp - experience of the employee
     * @throws InvalidDataException if duration is negative
     */
    public void setDuration(int exp) throws InvalidDataException
    {
        if (exp < 0.0)
        {
            throw new InvalidDataException("Experience of the employee can't be negative!");
        }
        this.exp = exp;
    }

    /**
     * Function for adding the employee to the company
     * @param comp - company in which the employee will be added
     * @return operation result
     */
    public abstract String addToCompany(Company comp);
}
