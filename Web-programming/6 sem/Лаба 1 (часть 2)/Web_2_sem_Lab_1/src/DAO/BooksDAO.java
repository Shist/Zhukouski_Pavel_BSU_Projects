package DAO;

import Connector.Exceptions.JDBCConnectionException;
import DAO.Exceptions.DAOException;
import Library.Book;
import com.mysql.cj.conf.ConnectionUrlParser;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

public class BooksDAO extends DAO {

    private static final String SELECT_ALL_BOOKS = "SELECT * FROM books";

    private static final String SELECT_ALL_BOOKS_WITH_SOME_NAME = "SELECT * FROM books WHERE bName=?";

    private static final String SELECT_ALL_BOOKS_WITH_SOME_AUTHOR = "SELECT * FROM books WHERE bAuthor=?";

    private static final String SELECT_BOOK_BY_BOOK_ID = "SELECT * FROM books WHERE bID=?";

    private static final String GET_AMOUNT_OF_BOOKS_OF_SPECIAL_ID = "SELECT bAmount FROM books WHERE bID=?";

    private static final String BORROW_ONE_BOOK_WITH_SPECIAL_ID = "UPDATE books SET bAmount=bAmount-1 WHERE bID=?";

    private static final String RETURN_ONE_BOOK_WITH_SPECIAL_ID = "UPDATE books SET bAmount=bAmount+1 WHERE bID=?";

    public BooksDAO() throws JDBCConnectionException {
    }

    public ArrayList<Book> getAllBooks() throws DAOException, JDBCConnectionException {

        // Выполняем запрос (данные запишутся в переменную rs)
        ConnectionUrlParser.Pair<PreparedStatement, ResultSet> ps_rs = executeStatement(SELECT_ALL_BOOKS, 0, "");

        ArrayList<Book> books = new ArrayList<>(); // Список книг

        try {
            while(ps_rs.right.next())
            {
                Book next_book = new Book(Integer.parseInt(ps_rs.right.getString("bID")),
                        ps_rs.right.getString("bName"),
                        ps_rs.right.getString("bAuthor"),
                        Integer.parseInt(ps_rs.right.getString("bAmount")));
                books.add(next_book);
            }
        } catch (SQLException throwables) {
            throw new DAOException("Error! Can't get data from ResultSet!", throwables);
        }

        closePreparedStatement(ps_rs.left);

        closeResultSet(ps_rs.right);

        return books;
    }

    public ArrayList<Book> getBooksWithSpecialName(String book_name) throws JDBCConnectionException, DAOException {

        // Выполняем запрос (данные запишутся в переменную rs)
        ConnectionUrlParser.Pair<PreparedStatement, ResultSet> ps_rs = executeStatement(SELECT_ALL_BOOKS_WITH_SOME_NAME, 1, book_name);

        ArrayList<Book> books = new ArrayList<>(); // Список книг

        try {
            while(ps_rs.right.next())
            {
                Book next_book = new Book(Integer.parseInt(ps_rs.right.getString("bID")),
                        ps_rs.right.getString("bName"),
                        ps_rs.right.getString("bAuthor"),
                        Integer.parseInt(ps_rs.right.getString("bAmount")));
                books.add(next_book);
            }
        } catch (SQLException throwables) {
            throw new DAOException("Error! Can't get data from ResultSet!", throwables);
        }

        closePreparedStatement(ps_rs.left);

        closeResultSet(ps_rs.right);

        return books;
    }

    public ArrayList<Book> getBooksWithSpecialAuthor(String author_name) throws JDBCConnectionException, DAOException {

        // Выполняем запрос (данные запишутся в переменную rs)
        ConnectionUrlParser.Pair<PreparedStatement, ResultSet> ps_rs = executeStatement(SELECT_ALL_BOOKS_WITH_SOME_AUTHOR, 2, author_name);

        ArrayList<Book> books = new ArrayList<>(); // Список книг

        try {
            while(ps_rs.right.next())
            {
                Book next_book = new Book(Integer.parseInt(ps_rs.right.getString("bID")),
                        ps_rs.right.getString("bName"),
                        ps_rs.right.getString("bAuthor"),
                        Integer.parseInt(ps_rs.right.getString("bAmount")));
                books.add(next_book);
            }
        } catch (SQLException throwables) {
            throw new DAOException("Error! Can't get data from ResultSet!", throwables);
        }

        closePreparedStatement(ps_rs.left);

        closeResultSet(ps_rs.right);

        return books;
    }

    public Book getBookWithSpecialID(int book_id) throws JDBCConnectionException, DAOException {

        // Выполняем запрос (данные запишутся в переменную rs)
        ConnectionUrlParser.Pair<PreparedStatement, ResultSet> ps_rs = executeStatement(SELECT_BOOK_BY_BOOK_ID, 3, Integer.toString(book_id));

        Book book = null; // Книга

        try {
            if (ps_rs.right.next())
            {
                book = new Book(Integer.parseInt(ps_rs.right.getString("bID")),
                        ps_rs.right.getString("bName"),
                        ps_rs.right.getString("bAuthor"),
                        Integer.parseInt(ps_rs.right.getString("bAmount")));
            }
        } catch (SQLException throwables) {
            throw new DAOException("Error! Can't get data from ResultSet!", throwables);
        }

        closePreparedStatement(ps_rs.left);

        closeResultSet(ps_rs.right);

        return book;
    }

    public int getAmountOfBooksWithSpecialID(int book_id) throws JDBCConnectionException, DAOException {

        // Выполняем запрос (данные запишутся в переменную rs)
        ConnectionUrlParser.Pair<PreparedStatement, ResultSet> ps_rs = executeStatement(GET_AMOUNT_OF_BOOKS_OF_SPECIAL_ID, 4, Integer.toString(book_id));

        int amount = 0; // Количество экземпляров книги

        try {
            if (ps_rs.right.next())
            {
                amount = Integer.parseInt(ps_rs.right.getString("bAmount"));
            }
        } catch (SQLException throwables) {
            throw new DAOException("Error! Can't get data from ResultSet!", throwables);
        }

        closePreparedStatement(ps_rs.left);

        closeResultSet(ps_rs.right);

        return amount;
    }

    public void borrowBookWithSpecialID(int book_id) throws JDBCConnectionException, DAOException {

        // Выполняем запрос (данные запишутся в переменную rs)
        executeUpdateStatement(BORROW_ONE_BOOK_WITH_SPECIAL_ID, 5, Integer.toString(book_id));
    }

    public void returnBookWithSpecialID(int book_id) throws JDBCConnectionException, DAOException {

        // Выполняем запрос (данные запишутся в переменную rs)
        executeUpdateStatement(RETURN_ONE_BOOK_WITH_SPECIAL_ID, 6, Integer.toString(book_id));
    }
}
