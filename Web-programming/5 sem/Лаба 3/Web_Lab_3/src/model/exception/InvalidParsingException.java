package model.exception;


/**
 *
 * @author Zhukouski Pavel
 *
 */
public class InvalidParsingException extends Exception {

    /**
     * Constructor with specified string
     * @param message string
     */
    public InvalidParsingException(String message) {
        super(message);
    }

    /**
     * Constructor with specified string and exception
     * @param message string
     * @param e error covered
     */
    public InvalidParsingException(String message, Throwable e) {
        super(message, e);
    }

    /**
     * get message
     */
    @Override
    public String getMessage() {
        return super.getMessage();
    }

    /**
     * print trace
     */
    @Override
    public void printStackTrace() {
        super.printStackTrace();
    }

}
