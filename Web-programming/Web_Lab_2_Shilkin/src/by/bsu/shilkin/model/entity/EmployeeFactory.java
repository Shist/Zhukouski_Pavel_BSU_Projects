package by.bsu.shilkin.model.entity;

/**
 * Class EmployeeFactory
 * @author Egor Shilkin
 * @version 1.0
 */

// Template - Factory with the parent's create method
public class EmployeeFactory {
    /**
     * Function for creating employee by type
     * @param typeOfEmp - type of employee
     * @return employee
     */
    public Employee create(String typeOfEmp) {
        Employee emp;
        switch (typeOfEmp.toLowerCase()) {
            case "designer":
                emp = new Designer();
                break;
            case "tester":
                emp = new Tester();
                break;
            case "developer":
                emp = new Developer();
                break;
            default:
                throw new IllegalArgumentException("Wrong type!");
        }
        return emp;
    }
}
