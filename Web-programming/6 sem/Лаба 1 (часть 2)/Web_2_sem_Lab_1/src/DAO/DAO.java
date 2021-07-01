package DAO;

import Connector.Exceptions.JDBCConnectionException;
import Connector.JdbcConnectionPool;
import DAO.Exceptions.DAOException;
import com.mysql.cj.conf.ConnectionUrlParser;
import java.sql.*;

import static Connector.JdbcConnectionPool.releaseConnection;

abstract public class DAO {

    protected JdbcConnectionPool dbConnectorPool;   // Переменная для хранения пула соединений

    protected DAO() throws JDBCConnectionException {
        dbConnectorPool = JdbcConnectionPool.getInstance();
    }

    protected ConnectionUrlParser.Pair<PreparedStatement, ResultSet> executeStatement(String query, int operation_num, String operation_info) throws DAOException, JDBCConnectionException {
        Connection currConn;
        PreparedStatement currPs;
        try {
            currConn = JdbcConnectionPool.getConnection();
            currPs = currConn.prepareStatement(query);
            switch (operation_num) {
                case 0 -> {
                }
                case 1 -> {
                    try { // Добавляем в запрос нужное название книги
                        currPs.setString(1, operation_info);
                    } catch (SQLException throwables) {
                        throw new DAOException("Error! Can't put book's name to query.", throwables);
                    }
                }
                case 2 -> {
                    try { // Добавляем в запрос нужное название автора книги
                        currPs.setString(1, operation_info);
                    } catch (SQLException throwables) {
                        throw new DAOException("Error! Can't put author's name to query.", throwables);
                    }
                }
                case 3, 4 -> {
                    try { // Добавляем в запрос нужный ID книги
                        currPs.setInt(1, Integer.parseInt(operation_info));
                    } catch (SQLException throwables) {
                        throw new DAOException("Error! Can't put book's ID to query.", throwables);
                    }
                }
                case 7 -> {
                    try { // Добавляем в запрос нужное имя читателя
                        currPs.setString(1, operation_info);
                    } catch (SQLException throwables) {
                        throw new DAOException("Error! Can't put reader's name to query.", throwables);
                    }
                }
                case 8 -> {
                    try { // Добавляем в запрос нужную дату
                        currPs.setDate(1, Date.valueOf(operation_info));
                    } catch (SQLException throwables) {
                        throw new DAOException("Error! Can't put date to query.", throwables);
                    }
                }
                case 9 -> {
                    try { // Добавляем в запрос нужный id книги
                        currPs.setInt(1, Integer.parseInt(operation_info));
                    } catch (SQLException throwables) {
                        throw new DAOException("Error! Can't put book's id to query.", throwables);
                    }
                }
                case 10 -> {
                    try { // Добавляем в запрос нужный id читателя
                        currPs.setInt(1, Integer.parseInt(operation_info));
                    } catch (SQLException throwables) {
                        throw new DAOException("Error! Can't put reader's ID to query.", throwables);
                    }
                }
                case 13 -> {
                    try { // Добавляем в запрос нужное имя читателя и id книги
                        String[] operation_info_parts = operation_info.split("\\|");
                        currPs.setInt(1, Integer.parseInt(operation_info_parts[0]));
                        currPs.setInt(2, Integer.parseInt(operation_info_parts[1]));
                    } catch (SQLException throwables) {
                        throw new DAOException("Error! Can't put reader's ID or book's ID to query.", throwables);
                    }
                }
            }
        } catch (SQLException | JDBCConnectionException throwables) {
            throw new DAOException("Error! Can't compile PreparedStatement!", throwables);
        }
        try {
            ResultSet rs = currPs.executeQuery();
            releaseConnection(currConn);
            return new ConnectionUrlParser.Pair<>(currPs, rs);
        } catch (SQLException throwables) {
            throw new DAOException("Error! Can't execute PreparedStatement!", throwables);
        }
    }

    protected void executeUpdateStatement(String query, int operation_num, String operation_info) throws DAOException, JDBCConnectionException {
        Connection currConn;
        PreparedStatement currPs;
        try {
            currConn = JdbcConnectionPool.getConnection();
            currPs = currConn.prepareStatement(query);
            switch (operation_num) {
                case 5, 6 -> {
                    try { // Добавляем в запрос нужный ID книги
                        currPs.setInt(1, Integer.parseInt(operation_info));
                    } catch (SQLException throwables) {
                        throw new DAOException("Error! Can't put book's ID to query.", throwables);
                    }
                }
                case 11 -> {
                    try { // Добавляем в запрос нужное имя читателя и id книги
                        String[] operation_info_parts = operation_info.split("\\|");
                        currPs.setString(1, operation_info_parts[0]);
                        currPs.setInt(2, Integer.parseInt(operation_info_parts[1]));
                    } catch (SQLException throwables) {
                        throw new DAOException("Error! Can't put reader's name or book's id to query.", throwables);
                    }
                }
                case 12 -> {
                    try { // Добавляем в запрос нужный id читателя
                        currPs.setInt(1, Integer.parseInt(operation_info));
                    } catch (SQLException throwables) {
                        throw new DAOException("Error! Can't put reader's ID to query.", throwables);
                    }
                }
            }
        } catch (SQLException | JDBCConnectionException throwables) {
            throw new DAOException("Error! Can't compile PreparedStatement!", throwables);
        }
        try {
            currPs.executeUpdate();
            releaseConnection(currConn);
            closePreparedStatement(currPs);
        } catch (SQLException throwables) {
            throw new DAOException("Error! Can't execute update-PreparedStatement!", throwables);
        }
    }

    protected void closeResultSet(ResultSet rs) throws DAOException {
        try {
            rs.close();
        } catch (SQLException throwables) {
            throw new DAOException("Error! Can't close ResultSet!", throwables);
        }
    }

    protected void closePreparedStatement(PreparedStatement ps) throws DAOException {
        try {
            ps.close();
        } catch (SQLException throwables) {
            throw new DAOException("Error! Can't close PreparedStatement!", throwables);
        }
    }

}
