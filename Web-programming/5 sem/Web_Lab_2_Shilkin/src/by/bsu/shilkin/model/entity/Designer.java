package by.bsu.shilkin.model.entity;

import by.bsu.shilkin.model.exception.InvalidDataException;

import java.util.Objects;

/**
 * Class Designer
 * @author Egor Shilkin
 * @version 1.0
 */

public class Designer extends by.bsu.shilkin.model.entity.Employee {

    /**
     * Enum type for the designer species
     */
    public enum DesignerSpecies {
        GraphicDesigner,
        WebDesigner,
        GameDesigner
    }

    /**
     * Designer species
     */
    private DesignerSpecies species;

    /**
     * Create new object
     * @see Designer#Designer(String, String, int, DesignerSpecies)
     */
    public Designer() {
    }

    /**
     * Designer constructor
     * Create new object with given values
     * @param name - name
     * @param surname - surname
     * @param exp - experience
     * @param species - species
     * @throws InvalidDataException if experience is negative
     * @see Designer#Designer()
     */
    public Designer(String name, String surname, int exp, DesignerSpecies species) throws InvalidDataException {
        setName(name);
        setSurname(surname);
        setDuration(exp);
        setSpecies(species);
    }

    /**
     * Function for getting field value {@link Designer#species}
     * Getter for species
     * @return species
     */
    public DesignerSpecies getSpecies() {
        return species;
    }

    /**
     * Function for setting the value of the field {@link Designer#species}
     * Setter for species
     * @param species - species
     */
    public void setSpecies(DesignerSpecies species) {
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
        Designer dev = (Designer) o;
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
     * Function to write an designer to a string
     * @return string
     */
    @Override
    public String toString() {
        return "Designer: " + ", name = " + name + ", surname = " + surname +
                ", experience = " + exp + ", species = " + species + "\n";
    }

    /**
     * Function for adding employee to the company
     * @param comp - company
     * @return operation result
     */
    @Override
    public String addToCompany(by.bsu.shilkin.model.entity.Company comp) {
        String result = "Designer was added to the company...";
        if (!comp.addToCompany(this)) {
            result = "Designer was not added to the company...";
        }
        return result;
    }
}
