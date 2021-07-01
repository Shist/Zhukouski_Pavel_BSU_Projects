package bel.pvzhu.bean;

import bel.pvzhu.entity.Books;
import bel.pvzhu.entity.Formular;

import javax.ejb.EJB;
import javax.ejb.Singleton;
import javax.ejb.Stateless;
import javax.faces.bean.SessionScoped;
import javax.inject.Named;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import javax.persistence.Query;
import javax.persistence.TypedQuery;
import java.math.BigDecimal;
import java.util.List;

/**
 * EJB боб для взаимодействия с сущностью Formular
 */

@Named("Formular")
@Singleton
@Stateless
@SessionScoped
public class FormularBean {
    /**
     * Менеджер сущностей
     */
    @PersistenceContext(unitName = "my_factory")
    private EntityManager em;

    @EJB
    private ReaderBean readerBean;

    private String bAuthor;

    public EntityManager getEm() {
        return em;
    }

    public void setEm(EntityManager em) {
        this.em = em;
    }

    public String getBAuthor() {
        return bAuthor;
    }

    public void setBAuthor(String bAuthor) {
        this.bAuthor = bAuthor;
    }

    final String SET_FORMULAR_IS_RETURNED_AND_BOOK_STATE = "update Formular set isReturned = 1, bookState = :bookState where formularId = :formularId";
    final String SET_BOOK_FOR_FORMULAR = "update Formular j set j.bookid = :book where j.formularId = :formularId";

    /**
     * Поиск записи формуляра по заявкке
     */
    public Long findFormularIdByRequestId(Long requestId){
        TypedQuery<Long> namedQuery = em.createNamedQuery("Formular.findFormularIdByRequestId", Long.class)
                .setParameter("requestId", requestId);
        return namedQuery.getSingleResult();
    }

    /**
     * Завершить чтение и оценить состояние книги
     */
    public void setFormularIsFinishAndBookState(Long formularId, BigDecimal bookState){
        Query query = em.createNativeQuery(SET_FORMULAR_IS_RETURNED_AND_BOOK_STATE)
                .setParameter("bookState", bookState)
                .setParameter("formularId", formularId);
        query.executeUpdate();
    }

    /**
     * Поиск всех записей формуляра
     */
    public List<Formular> findAll(){
        TypedQuery<Formular> namedQuery = em.createNamedQuery("Formular.findAll", Formular.class);
        return namedQuery.getResultList();
    }

    public List<Formular> getList(){
        return findAll();
    }

    /**
     * Поиск всех записей формуляра по ID
     */
    public List<Formular> findFormularForReader(Long bookId){
        TypedQuery<Formular> namedQuery = em.createNamedQuery("Formular.findFormularForReader", Formular.class)
                .setParameter("bookId", bookId);
        return namedQuery.getResultList();
    }

    public List<Formular> getReaderFormularList(){
        Long readerId = readerBean.findReaderIdByBAuthor(bAuthor);
        Long bookId = readerBean.findBookByReaderId(readerId).getBookId();
         return findFormularForReader(bookId);
    }

    /**
     * Изменить книгу для чтения
     */
    public void updateBookForFormular(Books book, Long formularId){
        Query query = em.createNativeQuery(SET_BOOK_FOR_FORMULAR)
                .setParameter("book", book)
                .setParameter("formularId", formularId);
        query.executeUpdate();
    }

    /**
     * Сохранить сущность в бд
     */
    public Long save(Formular formular) {
        em.persist(formular);
        return formular.getFormularId();
    }
}
