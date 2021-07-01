package DAO;

import Connector.Exceptions.JDBCConnectionException;
import Connector.JdbcConnector;
import DAO.Exceptions.DAOException;
import PropertisManager.ConfigureManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

abstract public class DAO implements AutoCloseable {

    protected ConfigureManager cm;      // Переменная для работы с properties

    protected JdbcConnector jdbc_cn;    // Переменная, в которой мы храним соединение к БД

    protected PreparedStatement ps;     // Переменная, в которой мы будем хранить PreparedStatement-ы

    protected ResultSet rs;             // Перемення, в которой мы будем хранить полученнуюв выборку данных

    protected DAO()
    {
        cm = new ConfigureManager();
        jdbc_cn = new JdbcConnector(cm);
    }

    protected void compileStatement(String query)
    {
        try {
            ps = jdbc_cn.cn.prepareStatement(query);
        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't compile PreparedStatement!", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }
    }

    protected void executeStatement()
    {
        try {
            rs = ps.executeQuery();
        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't execute PreparedStatement!", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }
    }

    protected void executeUpdateStatement()
    {
        try {
            ps.executeUpdate();
        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't execute update-PreparedStatement!", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }
    }

    protected void closeResultSet()
    {
        try {
            rs.close();
        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't close ResultSet!", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }
    }

    protected void closePreparedStatement()
    {
        try {
            ps.close();
        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't close PreparedStatement!", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }
    }

    protected void closeConnection()
    {
        try {
            jdbc_cn.closeConn();
        } catch (JDBCConnectionException e) {
            try {
                throw new JDBCConnectionException("Error! Can't close Connection!", e);
            } catch (JDBCConnectionException jdbcConnectionException) {
                jdbcConnectionException.printStackTrace();
            }
        }
    }

    @Override
    public void close() {
        // Закрыть ResultSet
        closeResultSet();
        // Закрыть PreparedStatement
        closePreparedStatement();
        // Закрыть Соединение
        closeConnection();
    }

}
