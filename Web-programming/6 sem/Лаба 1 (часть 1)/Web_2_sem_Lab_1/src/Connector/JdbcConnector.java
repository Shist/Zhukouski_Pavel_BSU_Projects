package Connector;

import Connector.Exceptions.JDBCConnectionException;
import PropertisManager.ConfigureManager;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class JdbcConnector {

    public Connection cn;

    public JdbcConnector(ConfigureManager cm) {

        // Загрузка класса драйвера для MySQL
        try {
            Class.forName(cm.driver);
        }  catch (ClassNotFoundException e) {
            try {
                throw new JDBCConnectionException ("Error! Can't load driver!", e);
            } catch (JDBCConnectionException jdbcConnectionException) {
                jdbcConnectionException.printStackTrace();
            }
        }

        // Установка соединения
        try {
            cn = DriverManager.getConnection(
                    cm.DB_URL, cm.user, cm.password);
        } catch (SQLException throwables) {
            try {
                throw new JDBCConnectionException ("Error! Can't make connection!", throwables);
            } catch (JDBCConnectionException e) {
                e.printStackTrace();
            }
        }

    }

    // Получить соединение
    public Connection getConn()
    {
        return cn;
    }

    // Установить новое соединение
    public void setConn(String new_DB_URL, String new_user, String new_password)
    {
        try {
            cn = DriverManager.getConnection(new_DB_URL, new_user, new_password);
        } catch (SQLException throwables) {
            try {
                throw new JDBCConnectionException ("Error! Can't make connection!", throwables);
            } catch (JDBCConnectionException e) {
                e.printStackTrace();
            }
        }
    }

    public void closeConn() throws JDBCConnectionException {
        if (cn != null) {
            try {
                cn.close();
            } catch (SQLException e) {
                throw new JDBCConnectionException("Error! Can't close connection", e);
            }
        }
    }

}
