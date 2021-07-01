package exception;

/**
 * Class representing parsing exception
 *
 * @author Zhukouski Pavel
 */
public class ParserException extends Exception {

    /**
     * Constructor with specified string
     *
     * @param message string
     */
    public ParserException(String message) {
        super(message);
    }

    /**
     * Constructor with specified string and exception
     *
     * @param message string
     * @param e       error covered
     */
    public ParserException(String message, Throwable e) {
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