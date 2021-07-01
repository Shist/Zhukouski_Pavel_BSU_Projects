package bel.mmkle.bean;

import bel.mmkle.entity.Cars;
import bel.mmkle.entity.Journeys;

import javax.ejb.EJB;
import javax.ejb.Singleton;
import javax.ejb.Stateless;
import javax.faces.bean.SessionScoped;
import javax.inject.Named;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import javax.persistence.Query;
import javax.persistence.TypedQuery;
import javax.transaction.Transactional;
import java.math.BigDecimal;
import java.util.List;

/**
 * EJB боб для взаимодействия с сущностью Journey
 */

@Named("Journey")
@Singleton
@Stateless
@SessionScoped
public class JourneyBean {
    /**
     * Менеджер сущностей
     */
    @PersistenceContext(unitName = "my_factory")
    private EntityManager em;

    @EJB
    private DriverBean driverBean;

    private String regNum;

    public EntityManager getEm() {
        return em;
    }

    public void setEm(EntityManager em) {
        this.em = em;
    }

    public String getRegNum() {
        return regNum;
    }

    public void setRegNum(String regNum) {
        this.regNum = regNum;
    }

    final String SET_JORNEY_IS_FINISH_AND_CAR_STATE = "update Journeys set isFinish = 1, carState = :carState where journeyId = :journeyId";
    final String SET_CAR_FOR_JOURNEY = "update Journeys j set j.carid = :car where j.journeyId = :journeyId";

    /**
     * Поиск поездки по заявкке
     */
    public Long findJourneyIdByRequestId(Long requestId){
        TypedQuery<Long> namedQuery = em.createNamedQuery("Journeys.findJourneyIdByRequestId", Long.class)
                .setParameter("requestId", requestId);
        return namedQuery.getSingleResult();
    }

    /**
     * Закончить поездку и поставить оценку состоянию автомобиля
     */
    public void setJourneyIsFinishAndCarState(Long journeyId, BigDecimal carState){
        Query query = em.createNativeQuery(SET_JORNEY_IS_FINISH_AND_CAR_STATE)
                .setParameter("carState", carState)
                .setParameter("journeyId", journeyId);
        query.executeUpdate();
    }

    /**
     * Поиск всех поездок
     */
    public List<Journeys> findAll(){
        TypedQuery<Journeys> namedQuery = em.createNamedQuery("Journeys.findAll", Journeys.class);
        return namedQuery.getResultList();
    }

    public List<Journeys> getList(){
        return findAll();
    }

    /**
     * Поиск всех поездок заданного водителя(по связке на машину)
     */
    public List<Journeys> findJourneysForDriver(Long carId){
        TypedQuery<Journeys> namedQuery = em.createNamedQuery("Journeys.findJourneysForDriver", Journeys.class)
                .setParameter("carId", carId);
        return namedQuery.getResultList();
    }

    public List<Journeys> getDriverJourneyList(){
        Long driverId = driverBean.findDriverIdByRegNum(regNum);
        Long carId = driverBean.findCarByDriverId(driverId).getCarId();
         return findJourneysForDriver(carId);
    }

    /**
     * Изменить машину для поездки
     */
    public void updateCarForJourney(Cars car, Long journeyId){
        Query query = em.createNativeQuery(SET_CAR_FOR_JOURNEY)
                .setParameter("car", car)
                .setParameter("journeyId", journeyId);
        query.executeUpdate();
    }

    /**
     * Сохранить сущность в бд
     */
    public Long save(Journeys journey) {
        em.persist(journey);
        return journey.getJourneyId();
    }
}
