package by.bsu.zhukouski.model.exception;

/**
 * Class exception for invalid data
 * @author Pavel Zhukouski, 3 course, 12 group
 * @version 1.0
 */
public class InvalidDataException extends Exception {
    /**
     * Create new exception
     * @see InvalidDataException#InvalidDataException(String)
     * @see InvalidDataException#InvalidDataException(String, Throwable)
     * @see InvalidDataException#InvalidDataException(Throwable)
     */
    public InvalidDataException() {
        super();
    }

    /**
     * Create new exception with given parameters
     * @param message - exception message
     * @see InvalidDataException#InvalidDataException()
     * @see InvalidDataException#InvalidDataException(String, Throwable)
     * @see InvalidDataException#InvalidDataException(Throwable)
     */
    public InvalidDataException(String message) {
        super(message);
    }

    /**
     * Create new exception with given parameters
     * @param message - exception message
     * @param cause   - exception cause
     * @see InvalidDataException#InvalidDataException()
     * @see InvalidDataException#InvalidDataException(String)
     * @see InvalidDataException#InvalidDataException(Throwable)
     */
    public InvalidDataException(String message, Throwable cause) {
        super(message, cause);
    }

    /**
     * Create new exception with given parameters
     * @param cause - exception cause
     * @see InvalidDataException#InvalidDataException()
     * @see InvalidDataException#InvalidDataException(String)
     * @see InvalidDataException#InvalidDataException(String, Throwable)
     */
    public InvalidDataException(Throwable cause) {
        super(cause);
    }
}
