package DAO;

import DAO.Exceptions.DAOException;
import Library.Book;
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

    public ArrayList<Book> getAllBooks()
    {
        // Компилируем запрос (скомпилируется в переменную ps)
        compileStatement(SELECT_ALL_BOOKS);

        // Выполняем запрос (данные запишутся в переменную rs)
        executeStatement();

        ArrayList<Book> books = new ArrayList<Book>(); // Список книг

        try {
            while(rs.next())
            {
                Book next_book = new Book(Integer.parseInt(rs.getString("bID")),
                        rs.getString("bName"),
                        rs.getString("bAuthor"),
                        Integer.parseInt(rs.getString("bAmount")));
                books.add(next_book);
            }
        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't get data from ResultSet!", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }

        return books;
    }

    public ArrayList<Book> getBooksWithSpecialName(String book_name)
    {
        // Компилируем запрос (скомпилируется в переменную ps)
        compileStatement(SELECT_ALL_BOOKS_WITH_SOME_NAME);
        try { // Добавляем в запрос нужное название книги
            ps.setString(1, book_name);
        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't put book's name to query.", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }

        // Выполняем запрос (данные запишутся в переменную rs)
        executeStatement();

        ArrayList<Book> books = new ArrayList<Book>(); // Список книг

        try {
            while(rs.next())
            {
                Book next_book = new Book(Integer.parseInt(rs.getString("bID")),
                        rs.getString("bName"),
                        rs.getString("bAuthor"),
                        Integer.parseInt(rs.getString("bAmount")));
                books.add(next_book);
            }
        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't get data from ResultSet!", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }

        return books;
    }

    public ArrayList<Book> getBooksWithSpecialAuthor(String author_name)
    {
        // Компилируем запрос (скомпилируется в переменную ps)
        compileStatement(SELECT_ALL_BOOKS_WITH_SOME_AUTHOR);
        try { // Добавляем в запрос нужное название автора книги
            ps.setString(1, author_name);
        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't put author's name to query.", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }

        // Выполняем запрос (данные запишутся в переменную rs)
        executeStatement();

        ArrayList<Book> books = new ArrayList<Book>(); // Список книг

        try {
            while(rs.next())
            {
                Book next_book = new Book(Integer.parseInt(rs.getString("bID")),
                        rs.getString("bName"),
                        rs.getString("bAuthor"),
                        Integer.parseInt(rs.getString("bAmount")));
                books.add(next_book);
            }
        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't get data from ResultSet!", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }

        return books;
    }

    public Book getBookWithSpecialID(int book_id)
    {
        // Компилируем запрос (скомпилируется в переменную ps)
        compileStatement(SELECT_BOOK_BY_BOOK_ID);
        try { // Добавляем в запрос нужный ID книги
            ps.setInt(1, book_id);
        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't put book's ID to query.", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }

        // Выполняем запрос (данные запишутся в переменную rs)
        executeStatement();

        Book book = null; // Книга

        try {
            if (rs.next())
            {
                book = new Book(Integer.parseInt(rs.getString("bID")),
                        rs.getString("bName"),
                        rs.getString("bAuthor"),
                        Integer.parseInt(rs.getString("bAmount")));
            }
        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't get data from ResultSet!", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }

        return book;
    }

    public int getAmountOfBooksWithSpecialID(int book_id)
    {
        // Компилируем запрос (скомпилируется в переменную ps)
        compileStatement(GET_AMOUNT_OF_BOOKS_OF_SPECIAL_ID);
        try { // Добавляем в запрос нужный ID книги
            ps.setInt(1, book_id);
        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't put book's ID to query.", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }

        // Выполняем запрос (данные запишутся в переменную rs)
        executeStatement();

        int amount = 0; // Количество экземпляров книги

        try {
            if (rs.next())
            {
                amount = Integer.parseInt(rs.getString("bAmount"));
            }
        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't get data from ResultSet!", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }



        return amount;
    }

    public void borrowBookWithSpecialID(int book_id)
    {
        // Компилируем запрос (скомпилируется в переменную ps)
        compileStatement(BORROW_ONE_BOOK_WITH_SPECIAL_ID);
        try { // Добавляем в запрос нужный ID книги
            ps.setInt(1, book_id);
        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't put book's ID to query.", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }

        // Выполняем запрос (данные запишутся в переменную rs)
        executeUpdateStatement();
    }

    public void returnBookWithSpecialID(int book_id)
    {
        // Компилируем запрос (скомпилируется в переменную ps)
        compileStatement(RETURN_ONE_BOOK_WITH_SPECIAL_ID);
        try { // Добавляем в запрос нужный ID книги
            ps.setInt(1, book_id);
        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't put book's ID to query.", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }

        // Выполняем запрос (данные запишутся в переменную rs)
        executeUpdateStatement();
    }

}
