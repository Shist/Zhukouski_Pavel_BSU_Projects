package PropertisManager;

import Connector.Exceptions.JDBCConnectionException;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Properties;

public class ConfigureManager {

    // Имя property файла
    private static final String DB_PROPERTIES = "database.properties";
    public String driver;
    public String DB_URL;
    public String user;
    public String password;

    public ConfigureManager() throws JDBCConnectionException {
        Properties prop = new Properties();

        try { // Пробуем получить досупт к property файлу
            prop.load(new FileInputStream(DB_PROPERTIES));
        } catch (IOException e) {
            throw new JDBCConnectionException("Error! Couldn't load properties file.");
        }

        // Получаем неободимую информацию для подключения из property-файла
        driver = prop.getProperty("driver");
        DB_URL = prop.getProperty("url");
        user = prop.getProperty("user");
        password = prop.getProperty("password");
    }

}
