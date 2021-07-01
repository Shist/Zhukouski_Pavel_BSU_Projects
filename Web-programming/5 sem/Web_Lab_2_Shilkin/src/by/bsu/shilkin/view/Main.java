package by.bsu.shilkin.view;

import by.bsu.shilkin.controller.EmployeeManager;
import by.bsu.shilkin.model.entity.*;
import by.bsu.shilkin.model.exception.InvalidDataException;

/**
 * Class Main
 * @author Egor Shilkin
 * @version 1.0
 *
 * 21. Human Resources Department. Define a hierarchy of employees in a small company. Create a company with multiple
 * departments. Determine the total number of employees in the company. Make a selection of employees in accordance
 * with the specified range of parameters. Sort employees in accordance with their length of service in the company.
 */
public class Main {

    /**
     * Program entry point
     * @param args - arguments
     */
    public static void main(String[] args) {

        EmployeeManager wr = new EmployeeManager();

        by.bsu.shilkin.model.entity.Employee[] emps = new by.bsu.shilkin.model.entity.Employee[9];

        try {
            emps[0] = new by.bsu.shilkin.model.entity.Developer(
                    "Mozhdeh",
                    "Betje",
                    2,
                    Developer.DeveloperSpecies.JuniorDeveloper
            );
            emps[1] = new by.bsu.shilkin.model.entity.Developer(
                    "Panther",
                    "Joo-Won",
                    5,
                    Developer.DeveloperSpecies.UsualDeveloper
            );
            emps[2] = new by.bsu.shilkin.model.entity.Developer(
                    "Bate",
                    "Marlena",
                    14,
                    Developer.DeveloperSpecies.SeniorDeveloper
            );
            emps[3] = new by.bsu.shilkin.model.entity.Designer(
                    "Murtaz",
                    "Briseis",
                    11,
                    Designer.DesignerSpecies.GameDesigner
            );
            emps[4] = new by.bsu.shilkin.model.entity.Designer(
                    "Cyrano",
                    "Mnason",
                    4,
                    Designer.DesignerSpecies.WebDesigner
            );
            emps[5] = new by.bsu.shilkin.model.entity.Designer(
                    "Steephan",
                    "Leo",
                    7,
                    Designer.DesignerSpecies.GraphicDesigner
            );
            emps[6] = new by.bsu.shilkin.model.entity.Tester(
                    "Layla",
                    "Zainuddin",
                    17,
                    Tester.TesterSpecies.AdministrativeTester
            );
            emps[7] = new by.bsu.shilkin.model.entity.Tester(
                    "Ciara",
                    "Pranav",
                    13,
                    Tester.TesterSpecies.AnalyticalTester
            );
            emps[8] = new by.bsu.shilkin.model.entity.Tester(
                    "Bronislav",
                    "Murad",
                    14,
                    Tester.TesterSpecies.TechnicalTester
            );
        } catch (InvalidDataException e) {
            e.printStackTrace();
        }

        /*
         * Adding all employee to the company
         * */

        emps[0].addToCompany(by.bsu.shilkin.model.entity.Company.getInstance());
        emps[1].addToCompany(by.bsu.shilkin.model.entity.Company.getInstance());
        emps[2].addToCompany(by.bsu.shilkin.model.entity.Company.getInstance());
        emps[3].addToCompany(by.bsu.shilkin.model.entity.Company.getInstance());
        emps[4].addToCompany(by.bsu.shilkin.model.entity.Company.getInstance());
        emps[5].addToCompany(by.bsu.shilkin.model.entity.Company.getInstance());
        emps[6].addToCompany(by.bsu.shilkin.model.entity.Company.getInstance());
        emps[7].addToCompany(by.bsu.shilkin.model.entity.Company.getInstance());
        emps[8].addToCompany(by.bsu.shilkin.model.entity.Company.getInstance());

        System.out.println("Printing all information about employee in company:");
        wr.printCompany(by.bsu.shilkin.model.entity.Company.getInstance());
        System.out.println("The whole amount of employee in the company:");
        wr.printWholeEmployeeAmount(emps);
        System.out.println("Now, we will look for employee with name Steephan:");
        wr.printFindByName("Steephan");
        System.out.println("Now, we will look for employee with surname Murad:");
        wr.printFindBySurname("Murad");
        System.out.println("Now, we will look for employee with experience 13:");
        wr.printFindByExperience(13);
        System.out.println("Now, we will look for employee with name from B to N:");
        wr.printFindByNameRange('B', 'N');
        System.out.println("Now, we will look for employee with name from L to X:");
        wr.printFindBySurnameRange('L', 'X');
        System.out.println("Now, we will look for employee with experience from 7 to 14 years:");
        wr.printFindByExperienceRange(7, 14);
        System.out.println("Departments of the company and their employees separately:");
        wr.printFind();
        System.out.println("Sorting all information:");
        wr.printSort();
        System.out.println("Clearing company...");
        by.bsu.shilkin.model.entity.Company.getInstance().clearCompany();
        System.out.println("Company after the clearing...");
        wr.printCompany(by.bsu.shilkin.model.entity.Company.getInstance());
    }
}
