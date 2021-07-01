package controller;

import model.dao.*;
import model.entity.Book;
import model.entity.Formular;
import model.entity.Reader;

import java.util.List;

/**
 * Class that contains all methods to work with program
 * @author Pavel Zhukouskiy
 * @version 1.0
 */
public class Controller {

    /**
     * DAOReader object to work with table reader
     */
    private IDAOReader daoReader;
    /**
     * DAOBook object to work with table reader
     */
    private IDAOBook daoBook;
    /**
     * DAOFormular object to work with table reader
     */
    private IDAOFormular daoFormular;


    public Controller(IDAOReader daoReader, IDAOBook daoBook, IDAOFormular daoFormular) {
        this.daoReader = daoReader;
        this.daoBook = daoBook;
        this.daoFormular = daoFormular;
    }

    /**
     * Print all readers from table reader
     */
    public List<Reader> showAllReaders() {
        return daoReader.printAllReaders();
    }

    /**
     * Print all books from table books
     */
    public List<Book> showAllBooks(){
        return daoBook.printAllBooks();
    }

    /**
     * Return information about book by author
     * @param author_name author name
     */
    public List<Book> getBookByAuthor(String author_name) {
        return daoBook.getBookByAuthor(author_name);
    }

    /**
     * Return number of instances of a book
     * @param book_id book id
     */
    public void getNumberOfInstance(int book_id){
        int number_of_instance;
        number_of_instance = daoBook.getNumberOfInstance(book_id);
        System.out.println("Number of instance = " + number_of_instance);
    }

    public boolean getBook(int book_id, int reader_id) {
        if(daoBook.getNumberOfInstance(book_id) != 0) {
            daoFormular.updateReaderInfo(book_id, reader_id);
            daoBook.updateNumberOfInstanceGet(book_id);
            return true;
        }
        return false;
    }

    public List<Formular> getDebtors() {
        return daoFormular.getDebtors();
    }

    public void returnBook(int reader_id, int book_id) {
        daoFormular.returnBook(reader_id, book_id);
        daoBook.updateNumberOfInstancePut(book_id);
    }

    public void printBook(Book book){
        System.out.printf("Book ID: %d\nName: %s\nAuthor: %s\nNumber of instance: %d \n", book.getId(), book.getName(), book.getAuthor(), book.getNumber_of_instance());
    }

    public void printReader(Reader reader){
        System.out.printf("Reader ID: %d \nName: %s \nBirth date: %s \n", reader.getId(), reader.getName(), reader.getBirth_date());
    }

    public void printFormular(Formular formular){
        System.out.printf("Formular ID: %d \nReader: %s \nBook: %s \n", formular.getId(), formular.getReader().toString(), formular.getBook().toString());
    }
}
