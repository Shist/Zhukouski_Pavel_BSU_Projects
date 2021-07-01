package model.exception;

public class ControllerException extends Exception{
    public ControllerException(String message){
        super(message);
    }

    public ControllerException (String message, Throwable e){
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
