package model.connector;

import model.exception.JDBCConnectorException;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.ResourceBundle;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;

/**
 * DataBase connector
 * @author Pavel Zhukouskiy
 * @version 1.0
 */
public class JDBCConnectorPool {

    private static JDBCConnectorPool instance;
    private final int initConnectionsCount = 5;
    private BlockingQueue<Connection> connections;

    /**
     * Method returns instance of connector
     * @return JDBCConnector object
     * @throws JDBCConnectorException
     */
    public static synchronized JDBCConnectorPool getInstance() throws JDBCConnectorException {
        if(instance == null){
            instance = new JDBCConnectorPool();
        }
        return instance;
    }

    /**
     * Constructor
     * @throws JDBCConnectorException exception
     */
    private JDBCConnectorPool() throws JDBCConnectorException {
        if (instance != null) {
            return;
        }

        try{
            Class.forName("com.mysql.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            throw new JDBCConnectorException("Can't load database driver.", e);
        }

        connections = new ArrayBlockingQueue<>(initConnectionsCount);
        try {
            for (int i = 0; i < initConnectionsCount; ++i) {
                Connection connection = getDBProperties();
                connections.add(connection);
            }
        } catch (SQLException e) {
            throw new JDBCConnectorException("Can't connect to database.", e);
        }
    }

    /**
     * Take connection from pool
     * @return connection object
     * @throws JDBCConnectorException exception
     */
    public synchronized Connection getConnection() throws JDBCConnectorException {
        try {
            return connections.take();
        } catch (InterruptedException e) {
            throw new JDBCConnectorException("Failed to get connection from pool", e);
        }
    }

    /**
     * Close connection to database
     * @throws JDBCConnectorException exception
     */
    public synchronized void releaseConnection(Connection connection) throws JDBCConnectorException {
        try {
            if (connection.isClosed()) {
                Connection newConnection = getDBProperties();
                connections.add(newConnection);
            } else {
                connections.add(connection);
            }
        } catch (SQLException e) {
            throw new JDBCConnectorException("Failed to establish connection", e);
        }

    }

    /**
     * Get database properties
     * @return connection object
     * @throws SQLException exception
     */
    private static Connection getDBProperties()  throws SQLException {
        ResourceBundle resource = ResourceBundle.getBundle("database");
        String url = resource.getString("url");
        String user = resource.getString("user");
        String pass = resource.getString("password");
        return DriverManager.getConnection(url,user,pass);
    }
}
