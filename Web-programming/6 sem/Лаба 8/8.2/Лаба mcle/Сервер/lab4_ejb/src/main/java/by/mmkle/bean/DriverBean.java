package by.mmkle.bean;

import by.mmkle.entity.Cars;
import by.mmkle.entity.Drivers;

import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import javax.persistence.TypedQuery;
/**
 * EJB боб для взаимодействия с сущностью Driver
 */
@Stateless
public class DriverBean {
    /**
     * Менеджер сущностей
     */
    @PersistenceContext(unitName = "my_factory")
    private EntityManager em;
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
    public Long save(Drivers driver) {
        em.persist(driver);
        return driver.getDriverId();
    }
}
