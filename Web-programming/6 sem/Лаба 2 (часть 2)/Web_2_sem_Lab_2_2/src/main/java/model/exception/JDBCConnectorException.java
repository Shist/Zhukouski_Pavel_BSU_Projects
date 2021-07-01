package model.exception;

public class JDBCConnectorException extends Exception {
    public JDBCConnectorException(String message){
        super(message);
    }

    public JDBCConnectorException(String message, Throwable e){
        super(message, e);
    }

    @Override
    public void printStackTrace() {
        super.printStackTrace();
    }

    @Override
    public String getMessage() {
        return super.getMessage();
    }
}
