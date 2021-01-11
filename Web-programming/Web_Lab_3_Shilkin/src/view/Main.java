package view;

import java.io.FileNotFoundException;

import controller.*;
import model.exception.InvalidParsingException;
/**
 *
 * @author Shilkin Egor
 *
 */
public class Main {

    public static void main(String[] args) throws FileNotFoundException, InvalidParsingException {
        Controller controller = new Controller();
        controller.begin();

    }

}
