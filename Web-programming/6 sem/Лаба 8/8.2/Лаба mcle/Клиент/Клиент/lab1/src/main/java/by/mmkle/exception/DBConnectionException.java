package by.mmkle.exception;

/**
 * Класс для ошибок связанных с подключением к БД
 *
 * @author mmkle
 */
public class DBConnectionException extends Exception {
    public DBConnectionException(String message) {
        super(message);
    }

    public DBConnectionException(String message, Throwable e) {
        super(message, e);
    }
}
