package bel.pvzhu.bean;

import bel.pvzhu.entity.Books;
import bel.pvzhu.entity.Readers;

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
 * EJB боб для взаимодействия с сущностью Reader
 */

@Named("Reader")
@Stateless
@Singleton
public class ReaderBean {
    /**
     * Менеджер сущностей
     */
    @PersistenceContext(unitName = "my_factory")
    private EntityManager em;

    @EJB
    private BookBean bookBean;

    private String name;
    private String bAuthor;
    private String bookID;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getBAuthor() {
        return bAuthor;
    }

    public void setBAuthor(String bAuthor) {
        this.bAuthor = bAuthor;
    }

    public String getBookID() {
        return bookID;
    }

    public void setBookID(String bookID) {
        this.bookID = bookID;
    }

    /**
     * Поиск читателя по автору книги, которую он взял
     */
    public Long findReaderIdByBAuthor(String bAuthor){
        TypedQuery<Long> namedQuery = em.createNamedQuery("Readers.findReaderIdByBAuthor", Long.class)
                .setParameter("bAuthor", bAuthor);
        return namedQuery.getSingleResult();
    }

    /**
     * Поиск читателя по ID
     */
    public Books findBookByReaderId(Long readerId){
        TypedQuery<Books> namedQuery = em.createNamedQuery("Readers.findBookByReaderId", Books.class)
                .setParameter("readerId", readerId);
        return namedQuery.getSingleResult();
    }

    /**
     * Сохранение сущности в бд
     */
    public void save() throws IOException {
        Readers reader = new Readers();
        Long bookId = bookBean.findBookIdByBAuthor(bookID);
        Books book = bookBean.findBookById(bookId);
        reader.setBook(book);
        reader.setName(name);
        reader.setBAuthor(bAuthor);
        save(reader);
        FacesContext.getCurrentInstance().getExternalContext().redirect("/lab6/menu");
    }

    public Long save(Readers reader){
        em.persist(reader);
        return reader.getReaderId();
    }
}
