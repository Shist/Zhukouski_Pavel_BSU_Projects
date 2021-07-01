package model.dao;

import model.entity.Reader;
import model.exception.DAOException;
import model.exception.JDBCConnectorException;

import javax.persistence.EntityManager;
import java.sql.*;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.List;

/**
 * DAO class to work with table reader
 * @author Pavel Zhukouskiy
 * @version 1.0
 */
public class DAOReader extends DAO {
    /**
     * Constructor
     * @throws DAOException учсузешщт
     */
    public DAOReader() throws DAOException {
        super();
    }

    /**
     * Returns information about reader by id
     * @param id reader id
     * @throws DAOException exception
     */
    public Reader getReaderInfoById(int id){
        EntityManager entityManager = null;
        Reader reader;
        try{

            entityManager = getEntityManagerFactory().createEntityManager();

            reader = entityManager.createNamedQuery("getReaderInfoByID", Reader.class)
                    .setParameter("id", id).getSingleResult();

        } finally {
            if (entityManager != null && entityManager.isOpen())
            entityManager.close();
        }
        return reader;
    }

    /**
     * Print all reader from table reader
     * @throws DAOException exception
     */
    public List<Reader> printAllReaders(){
        EntityManager entityManager = null;
        List<Reader> readerList;
        try{
            entityManager = getEntityManagerFactory().createEntityManager();

            readerList = entityManager.createNamedQuery("printAllReaders", Reader.class)
                    .getResultList();

        } finally {
            if (entityManager != null && entityManager.isOpen())
                entityManager.close();
        }
        return readerList;
    }

    /*public int getReadeIDByName(String name) throws DAOException {
        int id;
        try {
            connection = connector.getConnection();
            PreparedStatement ps = connection.prepareStatement(GET_READER_ID_BY_NAME);
            ps.setString(1, name);

            ResultSet rs = ps.executeQuery();
            rs.next();
            id = rs.getInt(1);
        } catch (JDBCConnectorException e) {
            throw new DAOException("Connector error", e);
        } catch (SQLException e) {
            throw new DAOException("Data base error", e);
        } finally {
            try {
                connector.releaseConnection(connection);
            } catch (JDBCConnectorException e) {
                throw new DAOException("Can't close data base", e);
            }
        }
        return id;
    }

    public boolean createReader(Reader reader) throws DAOException{

        try {
            connection = connector.getConnection();
            ps = connection.prepareStatement(CREATE_READER);

            ps.setInt(1, reader.getId());
            ps.setString(2, reader.getName());
            ps.setString(3, reader.getBirth_date());

            int affectedRows = ps.executeUpdate();
            if (affectedRows > 0)
                return true;
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
    }

    public  boolean deleteReader(int id) throws DAOException {

        try{
            connection = connector.getConnection();
            ps = connection.prepareStatement(DELETE_READER);

            ps.setInt(1, id);

            int affectedRows = ps.executeUpdate();
            if(affectedRows > 0){
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
    }*/
}
