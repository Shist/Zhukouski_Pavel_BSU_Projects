package model.dao;

import model.entity.Book;
import model.entity.Book_;

import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.EntityTransaction;
import javax.persistence.PersistenceContext;
import javax.persistence.criteria.CriteriaBuilder;
import javax.persistence.criteria.CriteriaQuery;
import javax.persistence.criteria.CriteriaUpdate;
import javax.persistence.criteria.Root;
import java.util.List;

/**
 * DAO class to work with table books
 * @author Pavel Zhukouskiy
 * @version 1.0
 */
@Stateless
public class DAOBook implements IDAOBook {

    /**
     * Entity maneger field
     */
    @PersistenceContext(unitName = "lab4_var5_server")
    private EntityManager entityManager;

    /**
     * Constructor
     */
    public DAOBook(){
        super();
    }

    /**
     * Method returns number of instances of a book
     * @param id book id
     * @return number of instances
     */
    public int getNumberOfInstance(int id) {

        CriteriaBuilder cb = entityManager.getCriteriaBuilder();
        CriteriaQuery<Book> cq = cb.createQuery(Book.class);
        Root<Book> bookRoot = cq.from(Book.class);
        cq.where(cb.equal(bookRoot.get(Book_.id), id));

        return entityManager.createQuery(cq)
                .getSingleResult().getNumber_of_instance();
    }

    /**
     * Method returns information about book by author
     * @param author author name
     */
    public List<Book> getBookByAuthor(String author) {

        CriteriaBuilder cb = entityManager.getCriteriaBuilder();
        CriteriaQuery<Book> cq = cb.createQuery(Book.class);
        Root<Book> bookRoot = cq.from(Book.class);
        cq.where(cb.equal(bookRoot.get(Book_.author), author));

        return entityManager.createQuery(cq)
                .getResultList();
    }

    /**
     * Print all books from table books
     */
    public List<Book> printAllBooks() {

        CriteriaBuilder cb = entityManager.getCriteriaBuilder();
        CriteriaQuery<Book> cq = cb.createQuery(Book.class);
        Root<Book> book = cq.from(Book.class);
        cq.select(book);

        return entityManager.createQuery(cq)
                .getResultList();
    }

    /**
     * To update number of instance of book when reader takes book
     * @param book_id book id
     */
    public void updateNumberOfInstanceGet(int book_id) {

        Book book = entityManager.find(Book.class, book_id);

        CriteriaBuilder cb = entityManager.getCriteriaBuilder();
        CriteriaUpdate<Book> cq = cb.createCriteriaUpdate(Book.class);
        Root<Book> bookRoot = cq.from(Book.class);
        cq.set(Book_.number_of_instance, book.getNumber_of_instance() - 1).where(cb.equal(bookRoot.get(Book_.id), book_id));

        try {
            entityManager.createQuery(cq).executeUpdate();
        } catch (Exception e) {
            e.printStackTrace();
        }

    }

    /**
     * To update number of instance of book when reader returns book
     * @param book_id book id
     */
    public void updateNumberOfInstancePut(int book_id) {

        Book book = entityManager.find(Book.class, book_id);

        CriteriaBuilder cb = entityManager.getCriteriaBuilder();
        CriteriaUpdate<Book> cq = cb.createCriteriaUpdate(Book.class);
        Root<Book> bookRoot = cq.from(Book.class);
        cq.set(Book_.number_of_instance, book.getNumber_of_instance() + 1).where(cb.equal(bookRoot.get(Book_.id), book_id));

        try {
            entityManager.createQuery(cq).executeUpdate();
        } catch (Exception e) {
            e.printStackTrace();
        }

    }
}
