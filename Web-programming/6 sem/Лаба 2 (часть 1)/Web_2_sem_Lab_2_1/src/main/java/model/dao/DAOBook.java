package model.dao;

import model.entity.Book;
import model.entity.Reader;
import model.exception.DAOException;
import model.exception.JDBCConnectorException;

import javax.persistence.EntityManager;
import javax.persistence.EntityTransaction;
import javax.persistence.Query;
import java.sql.*;
import java.util.ArrayList;
import java.util.List;

/**
 * DAO class to work with table books
 * @author Pavel Zhukouskiy
 * @version 1.0
 */
public class DAOBook extends DAO {
    /**
     * Constructor
     * @throws DAOException exception
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

            book = entityManager.createNamedQuery("getNumberOfInstance", Book.class)
                    .setParameter("id", id).getSingleResult();
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

            bookList = entityManager.createNamedQuery("getBookByAuthor", Book.class)
                    .setParameter("author", author).getResultList();
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

            bookList = entityManager.createNamedQuery("printAllBooks", Book.class)
                    .getResultList();
        } finally {
            if (entityManager != null && entityManager.isOpen())
                entityManager.close();
        }
        return bookList;
    }

    /**
     * Update number of instances in table books when reader take book
     * @param book_id book id
     * @throws DAOException exception
     */
    public void updateNumberOfInstanceGet(int book_id) throws DAOException {
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

    /**
     * Update number of instances in table books when reader return book
     * @param book_id book id
     * @throws DAOException exception
     */
    public void updateNumberOfInstancePut(int book_id) throws DAOException {
        EntityManager entityManager = null;
        EntityTransaction transaction = null;
        try {
            entityManager = getEntityManagerFactory().createEntityManager();
            entityManager.getTransaction();
            Book book = entityManager.find(Book.class, book_id);

            transaction.begin();
            book.setNumber_of_instance(book.getNumber_of_instance() + 1);
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


    /*public boolean createBook(Book book) throws DAOException {

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
