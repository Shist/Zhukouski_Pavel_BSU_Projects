package Connector;

import Connector.Exceptions.JDBCConnectionException;
import PropertisManager.ConfigureManager;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;

public class JdbcConnectionPool implements AutoCloseable {

    public static BlockingQueue<Connection> cn;
    public int initConnectionsCount = 10;

    private static JdbcConnectionPool instance;
    private static ConfigureManager cm;

    public JdbcConnectionPool() throws JDBCConnectionException {

        if (instance != null) {
            return;
        }

        cm = new ConfigureManager();

        // Загрузка класса драйвера для MySQL
        try {
            Class.forName(cm.driver);
        }  catch (ClassNotFoundException e) {
            throw new JDBCConnectionException ("Error! Can't load driver!", e);
        }

        cn = new ArrayBlockingQueue<>(initConnectionsCount);

        // Установка соединений
        try {
            for (int i = 0; i < initConnectionsCount; i++) {
                Connection connection = DriverManager.getConnection(cm.DB_URL, cm.user, cm.password);
                cn.add(connection);
            }
        } catch (SQLException throwables) {
            throw new JDBCConnectionException ("Error! Can't make connection!", throwables);
        }

    }

    /**
     * return instance DBConnectorPool or create it
     * @return instance of Singleton
     */
    public static synchronized JdbcConnectionPool getInstance() throws JDBCConnectionException {
        if (instance == null) {
            instance = new JdbcConnectionPool();
        }
        return instance;
    }

    public static synchronized Connection getConnection() throws JDBCConnectionException {
        try {
            return cn.take();
        } catch (InterruptedException e) {
            throw new JDBCConnectionException("Failed to get connection from pool", e);
        }
    }

    /**
     * return the connection to pool
     * @param connection to add back to pool
     */
    public static synchronized void releaseConnection(Connection connection) throws JDBCConnectionException {
        try {
            if (connection.isClosed()) {
                Connection newConnection = DriverManager.getConnection(cm.DB_URL, cm.user, cm.password);
                cn.add(newConnection);
            } else {
                cn.add(connection);
            }
        } catch (SQLException e) {
            throw new JDBCConnectionException("Failed to establish connection", e);
        }

    }

    public synchronized void closeConn() throws JDBCConnectionException {
        try {
            while (cn.size() > 0) {
                cn.take().close();
            }
        } catch (SQLException | InterruptedException e) {
            throw new JDBCConnectionException("Error! Can't close connection", e);
        }
    }

    @Override
    public void close() throws JDBCConnectionException {
        closeConn();
    }
}
