package by.mmkle.bean;

import by.mmkle.entity.Requests;

import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import javax.persistence.Query;
import javax.persistence.TypedQuery;

/**
 * EJB боб для взаимодействия с сущностью Request
 */
@Stateless
public class RequestBean {
    /**
     * Менеджер сущностей
     */
    @PersistenceContext(unitName = "my_factory")
    private EntityManager em;
    /**
     * Найти заявку по id
     */
    public Requests findRequestById(Long requestId) {
        TypedQuery<Requests> namedQuery = em.createNamedQuery("Requests.findRequestById", Requests.class)
                .setParameter("requestId", requestId);
        return namedQuery.getSingleResult();
    }
    /**
     * Удалить заявку по id
     */
    public void deleteRequestById(Long requestId) {
        Query query = em.createNamedQuery("Requests.deleteRequestById")
                .setParameter("requestId", requestId);
        query.executeUpdate();
    }
    /**
     * Сохранить сущность в бд
     */
    public Long save(Requests requests) {
        em.persist(requests);
        return requests.getRequestId();
    }
}
