package model.dao;

import model.entity.Book;

import javax.ejb.Remote;
import java.util.List;

/**
 * IDAOBook interface
 * @version 1.0
 * @author Pavel Zhukouskiy
 */
@Remote
public interface IDAOBook {

    /**
     * Method returns number of instances of a book
     * @param id book id
     * @return number of instances
     */
    int getNumberOfInstance(int id);

    /**
     * Method returns information about book by author
     * @param author author name
     */
    List<Book> getBookByAuthor(String author);

    /**
     * Print all books from table books
     */
    List<Book> printAllBooks();

    /**
     * To update number of instance of book when reader takes book
     * @param book_id book id
     */
    void updateNumberOfInstanceGet(int book_id);

    /**
     * To update number of instance of book when reader returns book
     * @param book_id book id
     */
    void updateNumberOfInstancePut(int book_id);
}
