package by.bsu.shilkin.model.entity;

import java.util.ArrayList;
import java.util.List;

/**
 * Class Company
 * @author Egor Shilkin
 * @version 1.0
 */

// Singleton template
public class Company {

    /**
     * Instance of company
     */
    private static Company instance = null;

    /**
     * Company
     */
    // Composite template
    private static List<by.bsu.shilkin.model.entity.Employee> company;

    /**
     * Create new object
     */
    private Company() {
    }

    /**
     * Function for getting field value {@link Company#instance}
     * @return instance
     */
    public static Company getInstance() {
        if (instance == null) {
            instance = new Company();
            company = new ArrayList<>();
        }
        return instance;
    }

    /**
     * Function for getting field value {@link Company#company}
     * @return company
     */
    public List<by.bsu.shilkin.model.entity.Employee> getCompany() {
        return company;
    }

    /**
     * Function for adding employee to the company
     * @param emp - employee
     * @return result of adding
     */
    boolean addToCompany(by.bsu.shilkin.model.entity.Employee emp) {
        if (emp == null) {
            return false;
        }
        return company.add(emp);
    }

    /**
     * Function for cleaning company
     */
    public void clearCompany() {
        company.clear();
    }

    /**
     * Function count the whole amount of employee at the company
     * @param emps - employee of the company
     * @return result of whole amount
     */
    public static int countWholeEmployeeAmount(Employee[] emps) {
        return emps.length;
    }
}
