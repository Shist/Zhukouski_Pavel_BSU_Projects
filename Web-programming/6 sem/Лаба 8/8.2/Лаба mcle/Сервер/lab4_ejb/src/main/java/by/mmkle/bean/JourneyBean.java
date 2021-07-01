package by.mmkle.bean;

import by.mmkle.entity.Cars;
import by.mmkle.entity.Drivers;
import by.mmkle.entity.Journeys;
import org.hibernate.Session;

import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import javax.persistence.Query;
import javax.persistence.TypedQuery;
import java.math.BigDecimal;
import java.util.ArrayList;
import java.util.List;
/**
 * EJB боб для взаимодействия с сущностью Journey
 */
@Stateless
public class JourneyBean {
    /**
     * Менеджер сущностей
     */
    @PersistenceContext(unitName = "my_factory")
    private EntityManager em;

    final String SET_JORNEY_IS_FINISH_AND_CAR_STATE = "update Journeys set isFinish = 1, carState = :carState where journeyId = :journeyId";
    final String SET_CAR_FOR_JOURNEY = "update Journeys j set j.carId = :car where j.journeyId = :journeyId";
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
        Query namedQuery = em.createNativeQuery("SELECT * FROM journeys");
        return namedQuery.getResultList();
    }
    /**
     * Поиск всех поездок заданного водителя(по связке на машину)
     */
    public List<Journeys> findJourneysForDriver(Long carId){
        TypedQuery<Journeys> namedQuery = em.createNamedQuery("Journeys.findJourneysForDriver", Journeys.class)
                .setParameter("carId", carId);
        return namedQuery.getResultList();
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
