package controller;

import model.dao.DAOBook;
import model.dao.DAOReader;
import model.entity.Book;
import model.entity.Reader;
import model.exception.ControllerException;
import model.exception.DAOException;

import java.util.List;

/**
 * Class that contains all methods to work with program
 * @author Pavel Zhukouski
 * @version 1.0
 */
public class Controller {

    /**
     * DAOReader object to work with table reader
     */
    private DAOReader daoReader;
    /**
     * DAOBook object to work with table reader
     */
    private DAOBook daoBook;

    /**
     * Print all readers from table reader
     * @throws ControllerException exceptions
     */
    public List<Reader> showAllReaders() throws ControllerException {
        List<Reader> readerList;
        try {
            daoReader = new DAOReader();
            readerList = daoReader.printAllReaders();
        } catch (DAOException e) {
            throw new ControllerException("Can't print all readers", e);
        }
        return readerList;
    }

    /**
     * Print all books from table books
     * @throws ControllerException exceptions
     */
    public List<Book> showAllBooks(){
        List<Book> bookList;
        daoBook = new DAOBook();
        bookList = daoBook.printAllBooks();
        return bookList;
    }

    /**
     * Return information about book by author
     * @param author_name author name
     * @throws ControllerException exception
     */
    public List<Book> getBookByAuthor(String author_name) throws ControllerException {
        List<Book> bookList;
        daoBook = new DAOBook();
        bookList = daoBook.getBookByAuthor(author_name);
//            for(Book book : bookList){
//                System.out.printf("ID: %d\nName: %s\nAuthor: %s\nNumber of instance: %d \n", book.getId(), book.getName(), book.getAuthor(), book.getNumber_of_instance());
//            }
        return bookList;
    }

    /**
     * Return number of instances of a book
     * @param book_id book id
     * @throws ControllerException exception
     */
    public void getNumberOfInstance(int book_id){
        int number_of_instance;
        daoBook = new DAOBook();
        number_of_instance = daoBook.getNumberOfInstance(book_id);
        System.out.println("Number of instance = " + number_of_instance);
    }

    /*public void getBook(int book_id, int reader_id) throws ControllerException {
        try{
            daoBook = new DAOBook();
            if(daoBook.getNumberOfInstance(book_id) != 0){
                daoFormular = new DAOFormular();
                //daoFormular.updateReaderInfo(book_id, reader_id);
                daoBook.updateNumberOfInstanceGet(book_id);
                System.out.println("You took book!");
            }else {
                System.out.println("No instance of this book");
            }
        } catch (DAOException e) {
            throw new ControllerException("Connector error", e);
        }
    }

    public List<Reader> getDebtors(){
        List<Reader> readerList;
        //List<Formular> formularList;
        daoFormular = new DAOFormular();
        readerList = daoFormular.getDebtors();
        return readerList;
    }

    public void returnBook(int book_id) throws ControllerException {
        try {
            daoFormular = new DAOFormular();
            daoBook = new DAOBook();
            daoFormular.returnBook(book_id);
            daoBook.updateNumberOfInstancePut(book_id);
        } catch (DAOException e) {
            throw new ControllerException(e.getMessage());
        }
    }*/

    public void printBook(Book book){
        System.out.printf("ID: %d\nName: %s\nAuthor: %s\nNumber of instance: %d \n", book.getId(), book.getName(), book.getAuthor(), book.getNumber_of_instance());
    }

    public void printReader(Reader reader){
        System.out.printf("ID: %d \nName: %s \nBirth date: %s \n", reader.getId(), reader.getName(), reader.getBirth_date());
    }
}
