package model.exception;

public class DAOException extends Exception{
    public DAOException(String message){
        super(message);
    }

    public DAOException(String message, Throwable e){
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
