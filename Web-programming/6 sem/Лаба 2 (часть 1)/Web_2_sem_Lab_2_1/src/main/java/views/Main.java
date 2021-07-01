package views;

import controller.Controller;
import model.entity.Book;
import model.entity.Reader;
import model.exception.ControllerException;

import java.util.List;
import java.util.logging.Logger;
import java.util.Scanner;

/**
 * Runner class
 * @author Pavel Zhukouskiy
 * @version 1.0
 */
public class Main {
    /**
     * Main method
     * @param args args
     */
    public static void main(String[] args) {

        Logger logger = Logger.getLogger(Main.class.getName());
        Controller controller = new Controller();
        Scanner sc = new Scanner(System.in);

        List<Book> bookList;
        List<Reader> readerList;

        while(true){
            System.out.println("\nMenu:\n1 - Show all readers\n2 - Show all books\n3 - Get books by author" +
                    "\n4 - Get number of instance of book"
                    /*"\n5 - Get book\n6 - Return book\n7 - Get debtors info"*/);

            switch (sc.nextLine()){
                case "1":
                    try {
                        readerList = controller.showAllReaders();
                        for(Reader reader : readerList){
                            controller.printReader(reader);
                        }
                    } catch (ControllerException e) {
                        logger.info(e.getMessage());
                    }
                    break;
                case "2":
                    bookList = controller.showAllBooks();
                    for(Book book : bookList){
                        controller.printBook(book);
                    }
                    break;
                case "3":
                    System.out.print("Enter authors name: ");
                    try {
                        bookList = controller.getBookByAuthor(sc.nextLine());
                        for(Book book : bookList){
                            controller.printBook(book);
                        }
                    } catch (ControllerException e) {
                        logger.info(e.getMessage());
                    }
                    break;
                case "4":
                    System.out.print("Enter book id: ");
                    controller.getNumberOfInstance(sc.nextInt());
                    break;
                /*case "5":
                    System.out.print("Enter your id: ");
                    int reader_id = sc.nextInt();
                    System.out.print("Enter book id: ");
                    int book_id = sc.nextInt();
                    try {
                        controller.getBook(book_id, reader_id);
                    } catch (ControllerException e) {
                        logger.info(e.getMessage());
                    }
                    break;
                case "6":
                    System.out.print("Enter book id: ");
                    int id = sc.nextInt();
                    try{
                        controller.returnBook(id);
                    } catch (ControllerException e) {
                        logger.info(e.getMessage());
                    }
                    break;
                case "7":
                    readerList = controller.getDebtors();
                    for(Reader reader : readerList){
                        controller.printReader(reader);
                    }
                    break;*/
                default:
                    return;
            }
        }
    }
}
