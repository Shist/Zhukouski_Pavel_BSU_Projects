package by.bsu.shilkin.model.entity;

import by.bsu.shilkin.model.exception.InvalidDataException;

import java.util.Objects;

/**
 * Class Developer
 * @author Egor Shilkin
 * @version 1.0
 */

public class Developer extends by.bsu.shilkin.model.entity.Employee {

    /**
     * Enum type for the developer species
     */
    public enum DeveloperSpecies {
        JuniorDeveloper,
        UsualDeveloper,
        SeniorDeveloper
    }

    /**
     * Developer species
     */
    private DeveloperSpecies species;

    /**
     * Create new object
     * @see Developer#Developer(String, String, int, DeveloperSpecies)
     */
    public Developer() {
    }

    /**
     * Developer constructor
     * Create new object with given values
     * @param name - name
     * @param surname - surname
     * @param exp - experience
     * @param species - species
     * @throws InvalidDataException if experience is negative
     * @see Developer#Developer()
     */
    public Developer(String name, String surname, int exp, DeveloperSpecies species) throws InvalidDataException {
        setName(name);
        setSurname(surname);
        setDuration(exp);
        setSpecies(species);
    }

    /**
     * Function for getting field value {@link Developer#species}
     * Getter for species
     * @return species
     */
    public DeveloperSpecies getSpecies() {
        return species;
    }

    /**
     * Function for setting the value of the field {@link Developer#species}
     * Setter for species
     * @param species - species
     */
    public void setSpecies(DeveloperSpecies species) {
        this.species = species;
    }

    /**
     * Function for comparing objects
     * @param o - object to compare
     * @return Returns true - objects are equal, false - objects are not equal
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Developer dev = (Developer) o;
        return name.equals(dev.name) && surname.equals(dev.surname) &&
                exp == dev.exp && species == dev.species;
    }

    /**
     * Function for finding hashCode
     * @return hashCode
     */
    @Override
    public int hashCode() {
        return Objects.hash(name, surname, exp, species);
    }

    /**
     * Function to write an developer to a string
     * @return string
     */
    @Override
    public String toString() {
        return "Developer: " + ", name = " + name + ", surname = " + surname +
                ", experience = " + exp + ", species = " + species + "\n";
    }

    /**
     * Function for adding employee to the company
     * @param comp - company
     * @return operation result
     */
    @Override
    public String addToCompany(by.bsu.shilkin.model.entity.Company comp) {
        String result = "Developer was added to the company...";
        if (!comp.addToCompany(this)) {
            result = "Developer was not added to the company...";
        }
        return result;
    }
}
