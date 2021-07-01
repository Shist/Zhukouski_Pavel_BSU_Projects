package by.mmkle.controller;

import by.mmkle.exception.DAOException;
import by.mmkle.model.Cars;
import by.mmkle.model.Journeys;

import java.math.BigDecimal;
import java.util.List;
import java.util.Scanner;

/**
 * Контроллер для отображения меню
 */

public class MenuController {
    CarParkController carParkController = new CarParkController();
    Scanner scanner = new Scanner(System.in);

    /**
     * Показ меню
     */
    public void showMenu() {
        System.out.println("Меню:");
        System.out.println("1. Добавить водителя");
        System.out.println("2. Добавить автомобиль");
        System.out.println("3. Заказать поездку");
        System.out.println("4. Список рейсов");
        System.out.println("5. Информация по водителю(список рейсов)");
        System.out.println("6. Автомобили в ремонте");
        System.out.println("7. Выход");
    }

    /**
     * Выбор пользователя
     */
    public Integer userChoise() {
        System.out.print("Выбор: ");
        return scanner.nextInt();
    }

    /**
     * Пункты меню
     */
    public void addDriverMenu() {
        System.out.println("Введите данные водителя");

        System.out.println("Имя: ");
        scanner.nextLine();
        String name = scanner.nextLine();

        System.out.println("Id машины: ");
        Long carId = scanner.nextLong();

        System.out.println("Рег номер водителя: ");
        scanner.nextLine();
        String carRegNum = scanner.nextLine();
        try {
            carParkController.addDriver(name, carId, carRegNum);
            System.out.println("Водитель добавлен");
        } catch (DAOException e) {
            System.out.println("Водитель не добавлен");
        }
    }

    public void addCarMenu() {
        System.out.println("Введите данные автомобиля");

        System.out.println("Вместительность: ");
        BigDecimal capability = scanner.nextBigDecimal();

        System.out.println("Стоимость поездки: ");
        BigDecimal cost = scanner.nextBigDecimal();

        System.out.println("Рег номер машины: ");
        scanner.nextLine();
        String carRegNum = scanner.nextLine();
        try {
            carParkController.addCar(capability, cost, 0, carRegNum);
            System.out.println("Машина добавлена");
        } catch (DAOException e) {
            System.out.println("Машина не добавлена");
        }
    }

    public void addRequestMenu() {
        System.out.println("Введите данные заявки");

        System.out.println("Мин. вместительность: ");
        BigDecimal capability = scanner.nextBigDecimal();

        System.out.println("Макс. стоимость: ");
        BigDecimal cost = scanner.nextBigDecimal();

        try {
            carParkController.addRequest(capability, cost);
            System.out.println("Заявка добавлена");
        } catch (DAOException e) {
            System.out.println("Заявка не добавлена");
        }
    }

    private void showJourneyList(List<Journeys> list) {
        for (Journeys journey : list) {
            System.out.println("Рег. номер машины: " + journey.getCar().getRegNum());
            //System.out.println("Номер заявки: " + journey.getRequest().getRequestId());
            System.out.println("Статус поездки: " + journey.getIsFinish());
            System.out.println("Состояние машины: " + journey.getCarState());
            System.out.println("-----------------------------------------------------");
        }
    }

    public void requestListMenu() {
        System.out.println("Список рейсов: ");
        List<Journeys> list = carParkController.journeysList();
        showJourneyList(list);
    }

    public void driverJourneysListMenu() throws DAOException {
        System.out.println("Введите id водителя");

        System.out.println("Id водителя: ");

        Long driverId = scanner.nextLong();

        List<Journeys> list = carParkController.journeysListForDriver(driverId);
        showJourneyList(list);
    }

    public void carOnRepairList() {
        List<Cars> list = carParkController.carsOnRepair();
        for (Cars car : list) {
            System.out.println("Рег. номер машины: " + car.getRegNum());
            System.out.println("-----------------------------------------------------");
        }
    }
}
