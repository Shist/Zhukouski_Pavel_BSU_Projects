package by.bsu.shilkin.controller;

import by.bsu.shilkin.model.entity.Employee;
import by.bsu.shilkin.model.entity.Company;

import java.util.Comparator;
import java.util.List;

/**
 * Class SortEmployee for sort functions
 *
 * @author Egor Shilkin
 * @version 1.0
 */

public class SortEmployee {

    /**
     * Function for sorting employee by name
     * @return list of employee
     */
    public List<Employee> sortByName() {
        List<Employee> list = Company.getInstance().getCompany();
        list.sort(Comparator.comparing(Employee::getName));
        return list;
    }

    /**
     * Function for sorting employee by surname
     * @return list of employee
     */
    public List<Employee> sortBySurname() {
        List<Employee> list = Company.getInstance().getCompany();
        list.sort(Comparator.comparing(Employee::getSurname));
        return list;
    }

    /**
     * Function for sorting employee by experience
     * @return list of employee
     */
    public List<Employee> sortByExperience() {
        List<Employee> list = Company.getInstance().getCompany();
        list.sort(Comparator.comparing(Employee::getExperience));
        return list;
    }
}
