package by.bsu.shilkin.controller;

import by.bsu.shilkin.model.entity.*;

import java.util.List;
import java.util.stream.Collectors;

/**
 * Class FindEmployee for find functions
 * @author Egor Shilkin
 * @version 1.0
 */

public class FindEmployee {

    /**
     * Function for finding developer
     * @return list of developer
     */
    public List<Employee> findDeveloper() {
        return Company.getInstance().getCompany().stream().filter(Developer.class::isInstance).collect(Collectors.toList());
    }

    /**
     * Function for finding designer
     * @return list of designer
     */
    public List<Employee> findDesigner() {
        return Company.getInstance().getCompany().stream().filter(Designer.class::isInstance).collect(Collectors.toList());
    }

    /**
     * Function for finding tester
     * @return list of tester
     */
    public List<Employee> findTester() {
        return Company.getInstance().getCompany().stream().filter(Tester.class::isInstance).collect(Collectors.toList());
    }

    /**
     * Function for finding employee by name
     * @param name - name
     * @return list of employee
     */
    public List<Employee> findByName(String name) {
        return Company.getInstance().getCompany().stream().filter(AbstractMusic -> AbstractMusic.getName().equals(name))
                .collect(Collectors.toList());
    }

    /**
     * Function for finding employee by surname
     * @param surname - name
     * @return list of employee
     */
    public List<Employee> findBySurname(String surname) {
        return Company.getInstance().getCompany().stream().filter(AbstractMusic -> AbstractMusic.getSurname()
                .equals(surname)).collect(Collectors.toList());
    }

    /**
     * Function for finding employee by experience
     * @param experience - experience
     * @return list of employee
     */
    public List<Employee> findByExperience(double experience) {
        return Company.getInstance().getCompany().stream().filter(AbstractMusic -> AbstractMusic.getExperience() == experience)
                .collect(Collectors.toList());
    }

    /**
     * Function for finding employee by name range
     * @param start - start of range of the first letter
     * @param end   - end of range of the first letter
     * @return list of employee
     */
    public List<Employee> findByNameRange(char start, char end) {
        return Company.getInstance().getCompany().stream().filter(AbstractMusic -> Character.toLowerCase(AbstractMusic.getName()
                .charAt(0)) >= Character.toLowerCase(start) && Character.toLowerCase(AbstractMusic.getName().charAt(0))
                <= Character.toLowerCase(end)).collect(Collectors.toList());
    }

    /**
     * Function for finding employee by surname range
     * @param start - start of range of the first letter
     * @param end   - end of range of the first letter
     * @return list of employee
     */
    public List<Employee> findBySurnameRange(char start, char end) {
        return Company.getInstance().getCompany().stream().filter(AbstractMusic -> Character.toLowerCase(AbstractMusic.getSurname()
                .charAt(0)) >= Character.toLowerCase(start) && Character.toLowerCase(AbstractMusic.getSurname().charAt(0))
                <= Character.toLowerCase(end)).collect(Collectors.toList());
    }

    /**
     * Function for finding employee by experience range
     * @param min - min value of the experience
     * @param max - max value of the experience
     * @return list of employee
     */
    public List<Employee> findByExperienceRange(double min, double max) {
        return Company.getInstance().getCompany().stream()
                .filter(AbstractMusic -> AbstractMusic.getExperience() >= min && AbstractMusic.getExperience() <= max)
                .collect(Collectors.toList());
    }
}
