package view;

import controller.Controller;
import model.dao.IDAOBook;
import model.dao.IDAOFormular;
import model.dao.IDAOReader;
import model.entity.Book;
import model.entity.Formular;
import model.entity.Reader;

import javax.ejb.EJB;
import java.util.List;
import java.util.Scanner;
import java.util.logging.Logger;

/**
 * Runner class
 * @author Pavel Zhukouskiy
 * @version 1.0
 */
public class Main {

    @EJB
    private static IDAOBook idaoBook;

    @EJB
    private static IDAOFormular idaoFormular;

    @EJB
    private static IDAOReader idaoReader;

    /**
     * Main method
     * @param args args
     */
    public static void main(String[] args) {

        Logger logger = Logger.getLogger(Main.class.getName());
        Controller controller = new Controller(idaoReader, idaoBook, idaoFormular);
        Scanner sc = new Scanner(System.in);

        List<Book> bookList;
        List<Reader> readerList;
        List<Formular> formularList;

        while(true){
            System.out.println("\n\n\nMenu:\n1 - Show all readers\n2 - Show all books\n3 - Get books by author" +
                    "\n4 - Get number of instance of book" +
                    "\n5 - Get book\n6 - Return book\nPrint \"q\" for exit");

            switch (sc.nextLine()){
                case "1":
                    readerList = controller.showAllReaders();
                    for(Reader reader : readerList){
                        controller.printReader(reader);
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
                    bookList = controller.getBookByAuthor(sc.nextLine());
                    for(Book book : bookList){
                        controller.printBook(book);
                    }
                    break;
                case "4":
                    System.out.print("Enter book id: ");
                    controller.getNumberOfInstance(Integer.parseInt(sc.nextLine()));
                    break;
                case "5":
                    System.out.print("Enter your id: ");
                    int reader_id = Integer.parseInt(sc.nextLine());
                    System.out.print("Enter book id: ");
                    int book_id = Integer.parseInt(sc.nextLine());
                    if (controller.getBook(book_id, reader_id)) {
                        System.out.println("You took book!");
                    } else {
                        System.out.println("No instance of this book");
                    }
                    break;
                case "6":
                    System.out.print("Enter your id: ");
                    int return_reader_id = Integer.parseInt(sc.nextLine());
                    System.out.print("Enter book id: ");
                    int return_book_id = Integer.parseInt(sc.nextLine());

                    controller.returnBook(return_reader_id, return_book_id);
                    break;
                /*case "7":
                    formularList = controller.getDebtors();
                    for(Formular formular : formularList){
                        controller.printFormular(formular);
                    }
                    break;*/
                default:
                    return;
            }
        }
    }
}
