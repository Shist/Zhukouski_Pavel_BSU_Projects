package by.bsu.shilkin.model.entity;

import by.bsu.shilkin.model.exception.InvalidDataException;

import java.util.Objects;

/**
 * Class Tester
 * @author Egor Shilkin
 * @version 1.0
 */

public class Tester extends by.bsu.shilkin.model.entity.Employee {

    /**
     * Enum type for the tester species
     */
    public enum TesterSpecies {
        AdministrativeTester,
        TechnicalTester,
        AnalyticalTester
    }

    /**
     * Tester species
     */
    private TesterSpecies species;

    /**
     * Create new object
     * @see Tester#Tester(String, String, int, TesterSpecies)
     */
    public Tester() {
    }

    /**
     * Tester constructor
     * Create new object with given values
     * @param name - name
     * @param surname - surname
     * @param exp - experience
     * @param species - species
     * @throws InvalidDataException if experience is negative
     * @see Tester#Tester()
     */
    public Tester(String name, String surname, int exp, TesterSpecies species) throws InvalidDataException {
        setName(name);
        setSurname(surname);
        setDuration(exp);
        setSpecies(species);
    }

    /**
     * Function for getting field value {@link Tester#species}
     * Getter for species
     * @return species
     */
    public TesterSpecies getSpecies() {
        return species;
    }

    /**
     * Function for setting the value of the field {@link Tester#species}
     * Setter for species
     * @param species - species
     */
    public void setSpecies(TesterSpecies species) {
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
        Tester dev = (Tester) o;
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
     * Function to write an tester to a string
     * @return string
     */
    @Override
    public String toString() {
        return "Tester: " + ", name = " + name + ", surname = " + surname +
                ", experience = " + exp + ", species = " + species + "\n";
    }

    /**
     * Function for adding employee to the company
     * @param comp - company
     * @return operation result
     */
    @Override
    public String addToCompany(by.bsu.shilkin.model.entity.Company comp) {
        String result = "Tester was added to the company...";
        if (!comp.addToCompany(this)) {
            result = "Tester was not added to the company...";
        }
        return result;
    }
}
