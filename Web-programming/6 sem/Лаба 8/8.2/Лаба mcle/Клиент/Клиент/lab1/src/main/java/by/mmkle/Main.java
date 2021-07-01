package by.mmkle;

import by.mmkle.controller.MenuController;
import by.mmkle.exception.DAOException;
import lombok.extern.slf4j.Slf4j;

/**
 * Демонстрационный класс
 *
 * @author mmkle
 */

@Slf4j
public class Main {

    public static void main(String[] args) throws DAOException {
        MenuController menuController = new MenuController();
        while (true) {
            menuController.showMenu();
            int choise = menuController.userChoise();
            switch (choise) {
                case 1:
                    menuController.addDriverMenu();
                    break;
                case 2:
                    menuController.addCarMenu();
                    break;
                case 3:
                    menuController.addRequestMenu();
                    break;
                case 4:
                    menuController.requestListMenu();
                    break;
                case 5:
                    menuController.driverJourneysListMenu();
                    break;
                case 6:
                    menuController.carOnRepairList();
                    break;
                case 7:
                    return;
                default:
                    System.out.println("Error menu number. Try again");
                    break;
            }
        }
    }
}
