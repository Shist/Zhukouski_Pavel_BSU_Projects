package bel.pvzhu.bean;

import bel.pvzhu.entity.Books;
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
import java.util.List;

/**
 * EJB боб для взаимодействия с сущностью Book
 */

@Named("Book")
@Singleton
@Stateless
public class BookBean {

    /**
     * Менеджер сущностей
     */
    @PersistenceContext(unitName = "my_factory")
    private EntityManager em;

    private String popularity;
    private String cost;
    private String bAuthor;

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

    public String getBAuthor() {
        return bAuthor;
    }

    public void setBAuthor(String bAuthor) {
        this.bAuthor = bAuthor;
    }

    public static final String SET_BOOK_ON_DISTRIB = "update Books c set c.onDistrib = 1 where c.bookId =:bookId";

    public static final String FIND_BOOK_BY_REQUIREMENTS = "select c.bookId from Books c " +
            "where c.onDistrib = 0 and c.popularity >= :popularity and c.cost <= :cost and " +
            "(select count(1) from Formular j where j.bookId = c.bookId and j.isReturned = 0) = 0";

    /**
     * Список всех книг
     */
    public List<Books> getAll(){
        TypedQuery<Books> namedQuery = em.createNamedQuery("Books.getAll", Books.class);
        return namedQuery.getResultList();
    }

    /**
     * Поиск книги по id
     */
    public Books findBookById(Long bookId){
        TypedQuery<Books> namedQuery = em.createNamedQuery("Books.findBookById", Books.class)
                .setParameter("bookId", bookId);
        return namedQuery.getSingleResult();
    }

    /**
     * Поиск книги по автору
     */
    public Long findBookIdByBAuthor(String bAuthor) {
        TypedQuery<Long> namedQuery = em.createNamedQuery("Books.findBookIdByBAuthor", Long.class)
                .setParameter("bAuthor", bAuthor);
        return namedQuery.getSingleResult();
    }

    /**
     * Список доступных книг
     */
    public List<Books> findBooksOnDistrib() {
        TypedQuery<Books> namedQuery = em.createNamedQuery("Books.findBooksOnDistrib", Books.class);
        return namedQuery.getResultList();
    }

    public List<Books> getList(){
        return findBooksOnDistrib();
    }

    /**
     * Выставить книгу на раздачу по ID
     */
    public void setBookOnDistrib(Long bookId){
        Query query = em.createNativeQuery(SET_BOOK_ON_DISTRIB)
                .setParameter("bookId", bookId);
        query.executeUpdate();
    }

    /**
     * Поиск книги по заданным параметрам (популярность, стоимость)
     */
    public Long findBookByRequirements(BigDecimal popularity, BigDecimal cost){
        Query query = em.createNativeQuery(FIND_BOOK_BY_REQUIREMENTS)
                .setParameter("popularity", popularity)
                .setParameter("cost", cost);
        return Long.valueOf(query.getSingleResult().toString());
    }

    /**
     * Сохранение сущности в бд
     */
    public Long save(Books book) {
        em.persist(book);
        return book.getBookId();
    }

    public void save() throws IOException {
        Books book = Books.builder()
                .bAuthor(bAuthor)
                .popularity(new BigDecimal(popularity))
                .cost(new BigDecimal(cost))
                .onDistrib(0)
                .build();

        save(book);
        FacesContext.getCurrentInstance().getExternalContext().redirect("/lab6/menu");
    }
    /**
     * Поиск подходящей книги для заявки
     */
    public Long findBookForRequest(Requests request) {
        return findBookByRequirements(request.getRequiredPopularity(), request.getMaxCost());
    }
}
