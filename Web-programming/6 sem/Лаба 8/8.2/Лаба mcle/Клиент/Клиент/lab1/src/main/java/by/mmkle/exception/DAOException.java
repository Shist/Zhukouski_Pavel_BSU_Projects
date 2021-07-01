package by.mmkle.exception;

/**
 * Класс для ошибок связанных с DAO классами
 *
 * @author mmkle
 */
public class DAOException extends Exception {
    public DAOException(String message) {
        super(message);
    }

    public DAOException(String message, Throwable e) {
        super(message, e);
    }
}
