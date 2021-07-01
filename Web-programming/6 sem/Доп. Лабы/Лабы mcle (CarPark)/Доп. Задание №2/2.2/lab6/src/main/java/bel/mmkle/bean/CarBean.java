package bel.mmkle.bean;

import bel.mmkle.entity.Cars;
import bel.mmkle.entity.Requests;

import javax.ejb.Singleton;
import javax.ejb.Stateless;
import javax.faces.context.FacesContext;
import javax.inject.Named;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import javax.persistence.Query;
import javax.persistence.TypedQuery;
import java.io.IOException;
import java.math.BigDecimal;
import java.util.List;

/**
 * EJB боб для взаимодействия с сущностью Car
 */

@Named("Car")
@Singleton
@Stateless
public class CarBean {

    /**
     * Менеджер сущностей
     */
    @PersistenceContext(unitName = "my_factory")
    private EntityManager em;

    private String capability;
    private String cost;
    private String regNum;

    public String getCapability() {
        return capability;
    }

    public void setCapability(String capability) {
        this.capability = capability;
    }

    public String getCost() {
        return cost;
    }

    public void setCost(String cost) {
        this.cost = cost;
    }

    public String getRegNum() {
        return regNum;
    }

    public void setRegNum(String regNum) {
        this.regNum = regNum;
    }

    public static final String SET_CAR_ON_REPAIR = "update Cars c set c.onRepair = 1 where c.carId =:carId";

    public static final String FIND_CAR_BY_REQUIREMENTS = "select c.carId from Cars c " +
            "where c.onRepair = 0 and c.capability >= :capability and c.cost <= :cost and " +
            "(select count(1) from Journeys j where j.carId = c.carId and j.isFinish = 0) = 0";

    /**
     * Список всех автомобилей
     */
    public List<Cars> getAll(){
        TypedQuery<Cars> namedQuery = em.createNamedQuery("Cars.getAll", Cars.class);
        return namedQuery.getResultList();
    }

    /**
     * Поиск автомобиля по id
     */
    public Cars findCarById(Long carId){
        TypedQuery<Cars> namedQuery = em.createNamedQuery("Cars.findCarById", Cars.class)
                .setParameter("carId", carId);
        return namedQuery.getSingleResult();
    }

    /**
     * Поиск автомобиля по рег номеру
     */
    public Long findCarIdByRegNum(String regNum) {
        TypedQuery<Long> namedQuery = em.createNamedQuery("Cars.findCarIdByRegNum", Long.class)
                .setParameter("regNum", regNum);
        return namedQuery.getSingleResult();
    }

    /**
     * Список автомобилей на ремонте
     */
    public List<Cars> findCarsOnRepair() {
        TypedQuery<Cars> namedQuery = em.createNamedQuery("Cars.findCarsOnRepair", Cars.class);
        return namedQuery.getResultList();
    }

    public List<Cars> getList(){
        return findCarsOnRepair();
    }

    /**
     * Поставить автомобиль на ремонт по id
     */
    public void setCarOnRepair(Long carId){
        Query query = em.createNativeQuery(SET_CAR_ON_REPAIR)
                .setParameter("carId", carId);
        query.executeUpdate();
    }

    /**
     * Поиск автомобиля по заданным параметтрам (вместительность, стоимость)
     */
    public Long findCarByRequirements(BigDecimal capability, BigDecimal cost){
        Query query = em.createNativeQuery(FIND_CAR_BY_REQUIREMENTS)
                .setParameter("capability", capability)
                .setParameter("cost", cost);
        return Long.valueOf(query.getSingleResult().toString());
    }

    /**
     * Сохранение сущности в бд
     */
    public Long save(Cars car) {
        em.persist(car);
        return car.getCarId();
    }

    public void save() throws IOException {
        Cars car = Cars.builder()
                .regNum(regNum)
                .capability(new BigDecimal(capability))
                .cost(new BigDecimal(cost))
                .onRepair(0)
                .build();

        save(car);
        FacesContext.getCurrentInstance().getExternalContext().redirect("/lab6/menu");
    }
    /**
     * Поиск подходящей машины для заявки
     */
    public Long findCarForRequest(Requests request) {
        return findCarByRequirements(request.getRequiredCapability(), request.getMaxCost());
    }
}
