package bel.pvzhu.bean;

import bel.pvzhu.entity.Requests;

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

/**
 * EJB боб для взаимодействия с сущностью Request
 */

@Named("Request")
@Singleton
@Stateless
public class RequestBean {
    /**
     * Менеджер сущностей
     */
    @PersistenceContext(unitName = "my_factory")
    private EntityManager em;


    private String popularity;
    private String cost;

    public String getPopularity() {
        return popularity;
    }

    public void setPopularity(String popularity) {
        this.popularity = popularity;
    }

    public String getCost() {
        return cost;
    }

    public void setCost(String cost) {
        this.cost = cost;
    }

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

    public void save() throws IOException {
        Requests requests = Requests.builder()
                .maxCost(new BigDecimal(cost))
                .requiredPopularity(new BigDecimal(popularity))
                .build();

        save(requests);

        FacesContext.getCurrentInstance().getExternalContext().redirect("/lab6/menu");
    }
}
