package by.mmkle.controller;

import by.mmkle.exception.DAOException;
import by.mmkle.model.Cars;
import by.mmkle.model.Drivers;
import by.mmkle.model.Journeys;
import by.mmkle.model.Requests;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.google.gson.Gson;
import javax.ws.rs.client.Client;
import javax.ws.rs.client.ClientBuilder;
import javax.ws.rs.client.Entity;
import javax.ws.rs.client.WebTarget;
import javax.ws.rs.core.GenericType;
import javax.ws.rs.core.Response;

import lombok.extern.slf4j.Slf4j;

import java.io.IOException;
import java.math.BigDecimal;
import java.util.Arrays;
import java.util.List;

/**
 * Контроллер работы Автобазы
 */

@Slf4j
public class CarParkController {
    public CarParkController() {

    }

    private String baseUrl = "http://localhost:8080/lab4/api";

    /**
     * Добавить машину (если машина уже существует, не создает возвращает существующий id)
     *
     * @param capability вместительность
     * @param cost       стоимость
     * @param onRepair   на ремонте?
     * @param regNum     рег номер
     * @return id машины
     */

    public Long addCar(BigDecimal capability, BigDecimal cost, int onRepair, String regNum) throws DAOException {
        Cars car = Cars.builder()
                    .regNum(regNum)
                    .capability(capability)
                    .onRepair(onRepair)
                    .cost(cost)
                    .build();

        Client client = ClientBuilder.newClient();
        WebTarget target = client.target(baseUrl + "/car");
        String response = target.request("application/json")
                .accept("application/json")
                .put(Entity.json(car), String.class);

        return null;
    }

    /**
     * Создает водителя, если существует возвращает существующий id
     *
     * @param name   имя
     * @param carId  id машины
     * @param regNum рег номер
     * @return id водителя
     */
    public Long addDriver(String name, Long carId, String regNum) throws DAOException {
        Cars car = readCar(carId);
        Drivers driver = Drivers.builder()
                    .car(car)
                    .name(name)
                    .regNum(regNum)
                    .build();

        Client client = ClientBuilder.newClient();
        WebTarget target = client.target(baseUrl + "/driver");
        String response = target.request("application/json")
                .accept("application/json")
                .put(Entity.json(driver), String.class);

       return null;
    }

    /**
     * Создает заявку, если существует возвращает сушествующий id
     *
     * @param requiredCapability запращиваемая вместительность
     * @param maxCost            максимальная цена
     * @return id заявки
     */
    public Long addRequest(BigDecimal requiredCapability, BigDecimal maxCost) throws DAOException {
        Requests request = Requests.builder()
                    .requiredCapability(requiredCapability)
                    .maxCost(maxCost)
                    .build();

        Client client = ClientBuilder.newClient();
        WebTarget target = client.target(baseUrl + "/request");
        String response = target.request("application/json")
                .accept("application/json")
                .put(Entity.json(request), String.class);

        return null;
    }

    /**
     * Добавить рейс, если существует возвращает созданный id
     *
     * @param carId         машина для рейса
     * @param requestId     id заявки
     * @param isFinish      закончился ли рейс
     * @param carState      состояние машины
     * @return id рейса
     */
    public Long addJourney(Long carId, Long requestId, int isFinish, BigDecimal carState) {
        Cars car = readCar(carId);
        Requests request = readRequest(requestId);
        Journeys journey = Journeys.builder()
                .request(request)
                .car(car)
                .carState(carState)
                .isFinish(isFinish)
                .build();

        Client client = ClientBuilder.newClient();
        WebTarget target = client.target(baseUrl + "/journey");
        String response = target.request("application/json")
                .accept("application/json")
                .put(Entity.json(journey), String.class);
        return null;
    }

    private Requests readRequest(Long requestId) {
        Client client = ClientBuilder.newClient();
        WebTarget target = client.target(baseUrl + "/request/" + requestId);
        Response response = target.request("application/json")
                .accept("application/json")
                .get();
        return response.readEntity(Requests.class);

    }

    private Cars readCar(Long carId) {
        Client client = ClientBuilder.newClient();
        WebTarget target = client.target(baseUrl + "/car/" + carId);
        Response response = target.request("application/json")
                .accept("application/json")
                .get();
        return response.readEntity(Cars.class);
    }

    /**
     * Закончить рейс и поставить оценку машине
     *
     * @param journeyId id рейса
     * @param carState  состояние машины
     */
    public void finishJourneyAndRateCar(Long journeyId, BigDecimal carState) {
        Client client = ClientBuilder.newClient();
        WebTarget target = client.target(baseUrl + "/journey/finish/" + journeyId + "/" + carState);
        String response = target.request("application/json")
                .accept("application/json")
                .put(null, String.class);
    }

    /**
     * Список рейсов
     * @return
     */
    public List<Journeys> journeysList() {
        Client client = ClientBuilder.newClient();
        WebTarget target = client.target(baseUrl + "/journey/list");
        Response response = target.request("application/json")
                .accept("application/json")
                .get();
        return response.readEntity(new GenericType<List<Journeys>>() {});
    }

    /**
     * Списое рейсов водителя
     *
     * @param driverId id водителя
     * @return
     */
    public List<Journeys> journeysListForDriver(Long driverId) throws DAOException {
        Long carId = findCarByDriverId(driverId).getCarId();

        Client client = ClientBuilder.newClient();
        WebTarget target = client.target(baseUrl + "/journey/list/" + carId);
        Response response = target.request("application/json")
                .accept("application/json")
                .get();
        return response.readEntity(new GenericType<List<Journeys>>() {});
    }

    private Cars findCarByDriverId(Long driverId) {
        Client client = ClientBuilder.newClient();
        WebTarget target = client.target(baseUrl + "/driver/car/" + driverId);
        Response response = target.request("application/json")
                .accept("application/json")
                .get();
        return response.readEntity(Cars.class);
    }

    /**
     * Список машины которые на ремонте
     * @return
     */
    public List<Cars> carsOnRepair() {
        Client client = ClientBuilder.newClient();
        WebTarget target = client.target(baseUrl + "/car/repair/list");
        Response response = target.request("application/json")
                .accept("application/json")
                .get();
        return response.readEntity(new GenericType<List<Cars>>() {});
    }

    /**
     * Поставить машину на ремонт
     *
     * @param carId id машины
     */
    public void setCarOnRepair(Long carId) {
        Client client = ClientBuilder.newClient();
        WebTarget target = client.target(baseUrl + "/car/repair/" + carId);
        String response = target.request("application/json")
                .accept("application/json")
                .put(null, String.class);
    }
}
