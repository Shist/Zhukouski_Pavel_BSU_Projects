package Connector.Exceptions;

/**
 * database connector exception
 * @author Zhukouski Pavel
 */
public class JDBCConnectionException extends Exception {
    /**
     * Constructor with specified string
     *
     * @param message string
     */
    public JDBCConnectionException(String message)
    {
        super(message);
    }
    /**
     * Constructor with specified string and exception
     *
     * @param message string
     * @param e       error covered
     */
    public JDBCConnectionException(String message, Throwable e)
    {
        super(message, e);
    }
    @Override
    public String getMessage() {
        return super.getMessage();
    }

    @Override
    public void printStackTrace() {
        super.printStackTrace();
    }
}
