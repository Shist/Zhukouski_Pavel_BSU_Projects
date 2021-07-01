package DAO;

import DAO.Exceptions.DAOException;
import Library.Reader;
import java.sql.Date;
import java.sql.SQLException;
import java.util.ArrayList;

public class ReadersDAO extends DAO {

    private static final String SELECT_ALL_READERS = "SELECT * FROM readers";

    private static final String SELECT_ALL_READERS_WITH_SPECIAL_NAME = "SELECT * FROM readers WHERE rName=?";

    private static final String SELECT_ALL_READERS_WITH_SPECIAL_DATE = "SELECT * FROM readers WHERE rDate<?";

    private static final String SELECT_ALL_READERS_WITH_SPECIAL_BOOK_ID = "SELECT * FROM readers WHERE bID=?";

    private static final String SELECT_READER_BY_READER_ID = "SELECT * FROM readers WHERE rID=?";

    private static final String ADD_READER_WITH_INFO = "INSERT INTO readers (rName, rDate, bID) VALUES (?, CURDATE(), ?)";

    private static final String DELETE_READER_BY_ID = "DELETE FROM readers WHERE rID=?";

    private static final String CHECK_IF_THERE_IS_BORROWED_BOOK_BY_READER = "SELECT EXISTS(SELECT * FROM readers WHERE rID = ? AND bID = ?)";

    public ArrayList<Reader> getAllReaders()
    {
        // Компилируем запрос (скомпилируется в переменную ps)
        compileStatement(SELECT_ALL_READERS);

        // Выполняем запрос (данные запишутся в переменную rs)
        executeStatement();

        ArrayList<Reader> readers = new ArrayList<Reader>(); // Список читателей

        try {
            while(rs.next())
            {
                Reader next_reader = new Reader(Integer.parseInt(rs.getString("rID")),
                        rs.getString("rName"),
                        rs.getString("rDate"),
                        Integer.parseInt(rs.getString("bID")));
                readers.add(next_reader);
            }
        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't get data from ResultSet!", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }

        return readers;
    }

    public ArrayList<Reader> getReadersWithSpecialName(String reader_name)
    {
        // Компилируем запрос (скомпилируется в переменную ps)
        compileStatement(SELECT_ALL_READERS_WITH_SPECIAL_NAME);
        try { // Добавляем в запрос нужное имя читателя
            ps.setString(1, reader_name);
        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't put reader's name to query.", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }

        // Выполняем запрос (данные запишутся в переменную rs)
        executeStatement();

        ArrayList<Reader> readers = new ArrayList<Reader>(); // Список читателей

        try {
            while(rs.next())
            {
                Reader next_reader = new Reader(Integer.parseInt(rs.getString("rID")),
                        rs.getString("rName"),
                        rs.getString("rDate"),
                        Integer.parseInt(rs.getString("bID")));
                readers.add(next_reader);
            }
        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't get data from ResultSet!", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }

        return readers;
    }

    public ArrayList<Reader> getReadersWithSpecialDate(Date needed_date)
    {
        // Компилируем запрос (скомпилируется в переменную ps)
        compileStatement(SELECT_ALL_READERS_WITH_SPECIAL_DATE);
        try { // Добавляем в запрос нужную дату
            ps.setDate(1, needed_date);
        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't put date to query.", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }

        // Выполняем запрос (данные запишутся в переменную rs)
        executeStatement();

        ArrayList<Reader> readers = new ArrayList<Reader>(); // Список читателей

        try {
            while(rs.next())
            {
                Reader next_reader = new Reader(Integer.parseInt(rs.getString("rID")),
                        rs.getString("rName"),
                        rs.getString("rDate"),
                        Integer.parseInt(rs.getString("bID")));
                readers.add(next_reader);
            }
        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't get data from ResultSet!", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }

        return readers;
    }

    public ArrayList<Reader> getReadersWithSpecialBookID(int book_id)
    {
        // Компилируем запрос (скомпилируется в переменную ps)
        compileStatement(SELECT_ALL_READERS_WITH_SPECIAL_BOOK_ID);
        try { // Добавляем в запрос нужный id книги
            ps.setInt(1, book_id);
        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't put book's id to query.", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }

        // Выполняем запрос (данные запишутся в переменную rs)
        executeStatement();

        ArrayList<Reader> readers = new ArrayList<Reader>(); // Список читателей

        try {
            while(rs.next())
            {
                Reader next_reader = new Reader(Integer.parseInt(rs.getString("rID")),
                        rs.getString("rName"),
                        rs.getString("rDate"),
                        Integer.parseInt(rs.getString("bID")));
                readers.add(next_reader);
            }
        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't get data from ResultSet!", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }

        return readers;
    }

    public Reader getReaderWithSpecialID(int reader_id)
    {
        // Компилируем запрос (скомпилируется в переменную ps)
        compileStatement(SELECT_READER_BY_READER_ID);
        try { // Добавляем в запрос нужный id читателя
            ps.setInt(1, reader_id);
        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't put reader's ID to query.", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }

        // Выполняем запрос (данные запишутся в переменную rs)
        executeStatement();

        Reader reader = null; // Читатель

        try {
            if (rs.next())
            {
                reader = new Reader(Integer.parseInt(rs.getString("rID")),
                        rs.getString("rName"),
                        rs.getString("rDate"),
                        Integer.parseInt(rs.getString("bID")));
            }
        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't get data from ResultSet!", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }

        return reader;
    }

    public void addReaderWithInfo(String reader_name, int book_id)
    {
        // Компилируем запрос (скомпилируется в переменную ps)
        compileStatement(ADD_READER_WITH_INFO);
        try { // Добавляем в запрос нужное имя читателя и id книги
            ps.setString(1, reader_name);
            ps.setInt(2, book_id);
        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't put reader's name or book's id to query.", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }

        // Выполняем запрос (данные запишутся в переменную rs)
        executeUpdateStatement();
    }

    public void deleteReaderByID(int reader_id)
    {
        // Компилируем запрос (скомпилируется в переменную ps)
        compileStatement(DELETE_READER_BY_ID);
        try { // Добавляем в запрос нужный id читателя
            ps.setInt(1, reader_id);
        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't put reader's ID to query.", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }

        // Выполняем запрос (данные запишутся в переменную rs)
        executeUpdateStatement();
    }

    public int checkBorrowedBookByReader(int reader_id, int book_id)
    {
        // Компилируем запрос (скомпилируется в переменную ps)
        compileStatement(CHECK_IF_THERE_IS_BORROWED_BOOK_BY_READER);
        try { // Добавляем в запрос нужный id читателя
            ps.setInt(1, reader_id);
            ps.setInt(2, book_id);
        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't put reader's ID or book's ID to query.", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }

        // Выполняем запрос (данные запишутся в переменную rs)
        executeStatement();

        int check = 0; // 1 - if exists, 0 - if not exists

        try {
            if (rs.next())
            {
                check = Integer.parseInt(rs.getString("EXISTS(SELECT * FROM readers WHERE rID = " + reader_id + " AND bID = " + book_id + ")"));
            }
        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't get data from ResultSet!", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }

        return check;
    }

}
