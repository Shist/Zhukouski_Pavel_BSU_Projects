package bel.mmkle.bean;

import bel.mmkle.entity.Cars;
import bel.mmkle.entity.Drivers;

import javax.ejb.EJB;
import javax.ejb.Singleton;
import javax.ejb.Stateless;
import javax.faces.context.FacesContext;
import javax.inject.Named;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import javax.persistence.TypedQuery;
import java.io.IOException;

/**
 * EJB боб для взаимодействия с сущностью Driver
 */

@Named("Driver")
@Stateless
@Singleton
public class DriverBean {
    /**
     * Менеджер сущностей
     */
    @PersistenceContext(unitName = "my_factory")
    private EntityManager em;

    @EJB
    private CarBean carBean;

    private String name;
    private String regNum;
    private String carRegNum;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getRegNum() {
        return regNum;
    }

    public void setRegNum(String regNum) {
        this.regNum = regNum;
    }

    public String getCarRegNum() {
        return carRegNum;
    }

    public void setCarRegNum(String carRegNum) {
        this.carRegNum = carRegNum;
    }

    /**
     * Поиск водителя по рег номеру
     */
    public Long findDriverIdByRegNum(String regNum){
        TypedQuery<Long> namedQuery = em.createNamedQuery("Drivers.findDriverIdByRegNum", Long.class)
                .setParameter("regNum", regNum);
        return namedQuery.getSingleResult();
    }

    /**
     * Поиск водителя по id
     */
    public Cars findCarByDriverId(Long driverId){
        TypedQuery<Cars> namedQuery = em.createNamedQuery("Drivers.findCarByDriverId", Cars.class)
                .setParameter("driverId", driverId);
        return namedQuery.getSingleResult();
    }

    /**
     * Созхранение сузности в бд
     */
    public void save() throws IOException {
        Drivers driver = new Drivers();
        Long carId = carBean.findCarIdByRegNum(carRegNum);
        Cars car = carBean.findCarById(carId);
        driver.setCar(car);
        driver.setName(name);
        driver.setRegNum(regNum);
        save(driver);
        FacesContext.getCurrentInstance().getExternalContext().redirect("/lab6/menu");
    }

    public Long save(Drivers driver){
        em.persist(driver);
        return driver.getDriverId();
    }
}
