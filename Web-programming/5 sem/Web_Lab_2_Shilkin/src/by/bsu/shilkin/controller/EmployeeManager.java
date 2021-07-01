package by.bsu.shilkin.controller;

import by.bsu.shilkin.model.entity.Company;
import by.bsu.shilkin.model.entity.Employee;

/**
 * Class EmployeeManager
 * @author Egor Shilkin
 * @version 1.0
 */

// Template - Facade
public class EmployeeManager {
    /**
     * Function for writing to the console company data
     * @param company - company
     */
    public void printCompany(Company company) {
        System.out.println(company.getCompany().toString() + '\n');
    }

    /**
     * Function for writing to the console sorting employee by parameters
     */
    public void printSort() {
        SortEmployee sort = new SortEmployee();
        System.out.println("Sorting by name:\n" + sort.sortByName() + '\n');
        System.out.println("Sorting by surname:\n" + sort.sortBySurname() + '\n');
        System.out.println("Sorting by experience:\n" + sort.sortByExperience() + '\n');
    }

    /**
     * Function for writing to the console finding employee
     */
    public void printFind() {
        FindEmployee find = new FindEmployee();
        System.out.println("Finding Developers:\n" + find.findDeveloper() + '\n');
        System.out.println("Finding Designers:\n" + find.findDesigner() + '\n');
        System.out.println("Finding Testers:\n" + find.findTester() + '\n');
    }

    /**
     * Function for writing to the console finding employee by name
     * @param name - name
     */
    public void printFindByName(String name) {
        FindEmployee find = new FindEmployee();
        System.out.println("Finding by name: " + find.findByName(name) + '\n');
    }

    /**
     * Function for writing to the console finding employee by surname
     * @param surname - surname of employee
     */
    public void printFindBySurname(String surname) {
        FindEmployee find = new FindEmployee();
        System.out.println("Finding by surname: " + find.findBySurname(surname) + '\n');
    }

    /**
     * Function for writing to the console finding employee by experience
     * @param experience - experience
     */
    public void printFindByExperience(double experience) {
        FindEmployee find = new FindEmployee();
        System.out.println("Finding by experience: " + find.findByExperience(experience) + '\n');
    }

    /**
     * Function for writing to the console of finding employee by name range
     * @param start - start of range of the first letter
     * @param end   - end of range of the first letter
     */
    public void printFindByNameRange(char start, char end) {
        FindEmployee find = new FindEmployee();
        System.out.println("Finding by name range: " + find.findByNameRange(start, end) + '\n');
    }

    /**
     * Function for writing to the console of finding employee by surname range
     * @param start - start of range of the first letter
     * @param end   - end of range of the first letter
     */
    public void printFindBySurnameRange(char start, char end) {
        FindEmployee find = new FindEmployee();
        System.out.println("Finding by surname range: " + find.findBySurnameRange(start, end) + '\n');
    }

    /**
     * Function for writing to the console of finding employee by experience range
     * @param min - min value of the experience
     * @param max - max value of the experience
     */
    public void printFindByExperienceRange(double min, double max) {
        FindEmployee find = new FindEmployee();
        System.out.println("Finding by experience range: " + find.findByExperienceRange(min, max) + '\n');
    }

    /**
     * Function that counts the whole amount of employee at the company
     * @param emps - employee of the company
     */
    public void printWholeEmployeeAmount(Employee[] emps) {
        System.out.println("Employee amount = " + Company.countWholeEmployeeAmount(emps) + '\n');
    }
}
