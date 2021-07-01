package model.dao;

import controller.Controller;
import model.entity.*;
import model.exception.DAOException;
import model.exception.JDBCConnectorException;

import javax.persistence.EntityManager;
import javax.persistence.EntityTransaction;
import javax.persistence.Query;
import javax.persistence.criteria.CriteriaBuilder;
import javax.persistence.criteria.CriteriaQuery;
import javax.persistence.criteria.CriteriaUpdate;
import javax.persistence.criteria.Root;
import javax.persistence.metamodel.EntityType;
import java.sql.*;
import java.util.ArrayList;
import java.util.List;

/**
 * DAO class to work with table books
 * @author Pavel Zhukouski
 * @version 1.0
 */
public class DAOBook extends DAO {

    /**
     * Constructor
     * @throws DAOException учсузешщт
     */
    public DAOBook(){
        super();
    }

    /**
     * Method returns number of instances of a book
     * @param id book id
     * @return number of instances
     * @throws DAOException exception
     */
    public int getNumberOfInstance(int id) {
        EntityManager entityManager = null;
        Book book;
        int number_of_instance;
        try{

            entityManager = getEntityManagerFactory().createEntityManager();
            CriteriaBuilder cb = entityManager.getCriteriaBuilder();
            CriteriaQuery<Book> cq = cb.createQuery(Book.class);
            Root<Book> bookRoot = cq.from(Book.class);
            cq.where(cb.equal(bookRoot.get(Book_.id), id));
            book = entityManager.createQuery(cq)
                    .getSingleResult();
            number_of_instance = book.getNumber_of_instance();

        } finally {
            if (entityManager != null && entityManager.isOpen())
            entityManager.close();
        }
        return number_of_instance;
    }

    /**
     * Method returns information about book by author
     * @param author author name
     * @throws DAOException exception
     */
    public List<Book> getBookByAuthor(String author){
        EntityManager entityManager = null;
        List<Book> bookList;
        try {

            entityManager = getEntityManagerFactory().createEntityManager();
            CriteriaBuilder cb = entityManager.getCriteriaBuilder();
            CriteriaQuery<Book> cq = cb.createQuery(Book.class);
            Root<Book> bookRoot = cq.from(Book.class);
            cq.where(cb.equal(bookRoot.get(Book_.author), author));
            bookList = entityManager.createQuery(cq)
                    .getResultList();
        } finally {
            if (entityManager != null && entityManager.isOpen())
                entityManager.close();
        }
        return bookList;
    }

    /**
     * Print all books from table books
     * @throws DAOException exception
     */
    public List<Book> printAllBooks(){
        EntityManager entityManager = null;
        List<Book> bookList;

        try{

            entityManager = getEntityManagerFactory().createEntityManager();
            CriteriaBuilder cb = entityManager.getCriteriaBuilder();
            CriteriaQuery<Book> cq = cb.createQuery(Book.class);
            Root<Book> book = cq.from(Book.class);
            cq.select(book);
            bookList = entityManager.createQuery(cq)
                    .getResultList();
        } finally {
            if (entityManager != null && entityManager.isOpen())
                entityManager.close();
        }
        return bookList;
    }

    /*public void updateNumberOfInstanceGet(int book_id) throws DAOException {
        EntityManager entityManager = null;
        EntityTransaction transaction = null;
        try {
            entityManager = getEntityManagerFactory().createEntityManager();
            entityManager.getTransaction();
            Book book = entityManager.find(Book.class, book_id);

            transaction.begin();
            book.setNumber_of_instance(book.getNumber_of_instance() - 1);
            transaction.commit();

        }catch (Exception e) {
            if (transaction != null && transaction.isActive())
                transaction.rollback();
            throw new DAOException("failed to set car status", e);
        }finally {
            if (entityManager != null && entityManager.isOpen())
                entityManager.close();
        }
    }

    public void updateNumberOfInstancePut(int book_id) throws DAOException {
        EntityManager entityManager = null;
        EntityTransaction transaction = null;
        try {
            entityManager = getEntityManagerFactory().createEntityManager();
            transaction = entityManager.getTransaction();
            CriteriaBuilder cb = entityManager.getCriteriaBuilder();
            CriteriaUpdate<Book> cq = cb.createCriteriaUpdate(Book.class);
            Root<Book> bookRoot = cq.from(Book.class);
            cq.set(Book_.number_of_instance, 15 ).where(cb.equal(bookRoot.get(Book_.id), book_id));

            transaction.begin();
            entityManager.createQuery(cq).executeUpdate();
            transaction.commit();

        }finally {
            if (entityManager != null && entityManager.isOpen())
                entityManager.close();
        }
    }


    public boolean createBook(Book book) throws DAOException {

        try {
            connection = connector.getConnection();
            PreparedStatement ps = connection.prepareStatement(CREATE_BOOK);

            ps.setInt(1, book.getId());
            ps.setString(2, book.getName());
            ps.setString(3, book.getAuthor());
            ps.setInt(4, book.getNumber_of_instance());

            int affectedRows = ps.executeUpdate();
            if (affectedRows > 0) {
                return true;
            }
        } catch (SQLException e) {
            throw new DAOException("Data base error", e);
        } catch (JDBCConnectorException e) {
            throw new DAOException("Connector error", e);
        } finally {
            try {
                connector.releaseConnection(connection);
            } catch (JDBCConnectorException e) {
                throw new DAOException("Can't close connection to DB", e);
            }
        }
        return false;
    }

    public boolean deleteBook(int id) throws DAOException {

        try{
            connection = connector.getConnection();
            PreparedStatement ps = connection.prepareStatement(DELETE_BOOK);

            ps.setInt(1, id);

            int affectedRows = ps.executeUpdate();
            if(affectedRows > 0){
                return true;
            }
        } catch (SQLException e) {
            e.printStackTrace();
        } catch (JDBCConnectorException e) {
            throw new DAOException("Connector error", e);
        }finally {
            try {
                connector.releaseConnection(connection);
            } catch (JDBCConnectorException e) {
                throw new DAOException("Can't close connection to DB", e);
            }
        }
        return false;
    }*/

}
