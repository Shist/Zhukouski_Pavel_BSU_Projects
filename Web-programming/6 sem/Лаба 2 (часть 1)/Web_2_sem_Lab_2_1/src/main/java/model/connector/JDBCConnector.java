package model.connector;

import model.exception.JDBCConnectorException;

import java.sql.*;
import java.sql.DriverManager;
import java.util.ResourceBundle;

/**
 * DataBase connector
 * @author Pavel Zhukouskiy
 * @version 1.0
 */
public class JDBCConnector {

    private static Connection connection;
    private static JDBCConnector instance;

    /**
     * Method returns instance of connector
     * @return JDBCConnector object
     * @throws JDBCConnectorException
     */
    public static JDBCConnector getInstance() throws JDBCConnectorException {
        if(instance == null){
            instance = new JDBCConnector();
        }
        return instance;
    }

    /**
     * Connect to database
     * @return connection object
     * @throws JDBCConnectorException exception
     */
    public static Connection dataBaseConnection() throws JDBCConnectorException {
        try{
            Class.forName("com.mysql.jdbc.Driver");
            connection = getDBProperties();
        }  catch (ClassNotFoundException e) {
            throw new JDBCConnectorException("Can't load database driver.", e);
        } catch (SQLException e) {
            throw new JDBCConnectorException("Can't connect to database.", e);
        }

        return connection;
    }

    /**
     * Get database properties
     * @return connection object
     * @throws SQLException exception
     */
    private static Connection getDBProperties()  throws SQLException{
        ResourceBundle resource = ResourceBundle.getBundle("database");
        String url = resource.getString("url");
        String user = resource.getString("user");
        String pass = resource.getString("password");
        return DriverManager.getConnection(url,user,pass);
    }

    /**
     * Close connection to database
     * @throws JDBCConnectorException exception
     */
    public void closeDBConnection() throws JDBCConnectorException {
        if(connection != null){
            try{
                connection.close();
            } catch (SQLException e) {
                throw new JDBCConnectorException("Can't close connection", e);
            }
        }
    }
}


