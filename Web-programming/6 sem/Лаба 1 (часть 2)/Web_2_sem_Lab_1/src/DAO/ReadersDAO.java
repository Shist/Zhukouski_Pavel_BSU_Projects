package DAO;

import Connector.Exceptions.JDBCConnectionException;
import DAO.Exceptions.DAOException;
import Library.Reader;
import com.mysql.cj.conf.ConnectionUrlParser;

import java.sql.Date;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
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

    public ReadersDAO() throws JDBCConnectionException {
    }

    public ArrayList<Reader> getAllReaders() throws JDBCConnectionException, DAOException {

        // Выполняем запрос (данные запишутся в переменную rs)
        ConnectionUrlParser.Pair<PreparedStatement, ResultSet> ps_rs = executeStatement(SELECT_ALL_READERS, 0, "");

        ArrayList<Reader> readers = new ArrayList<>(); // Список читателей

        try {
            while(ps_rs.right.next())
            {
                Reader next_reader = new Reader(Integer.parseInt(ps_rs.right.getString("rID")),
                        ps_rs.right.getString("rName"),
                        ps_rs.right.getString("rDate"),
                        Integer.parseInt(ps_rs.right.getString("bID")));
                readers.add(next_reader);
            }
        } catch (SQLException throwables) {
            throw new DAOException("Error! Can't get data from ResultSet!", throwables);
        }

        closePreparedStatement(ps_rs.left);

        closeResultSet(ps_rs.right);

        return readers;
    }

    public ArrayList<Reader> getReadersWithSpecialName(String reader_name) throws JDBCConnectionException, DAOException {


        // Выполняем запрос (данные запишутся в переменную rs)
        ConnectionUrlParser.Pair<PreparedStatement, ResultSet> ps_rs = executeStatement(SELECT_ALL_READERS_WITH_SPECIAL_NAME, 7, reader_name);

        ArrayList<Reader> readers = new ArrayList<>(); // Список читателей

        try {
            while(ps_rs.right.next())
            {
                Reader next_reader = new Reader(Integer.parseInt(ps_rs.right.getString("rID")),
                        ps_rs.right.getString("rName"),
                        ps_rs.right.getString("rDate"),
                        Integer.parseInt(ps_rs.right.getString("bID")));
                readers.add(next_reader);
            }
        } catch (SQLException throwables) {
            throw new DAOException("Error! Can't get data from ResultSet!", throwables);
        }

        closePreparedStatement(ps_rs.left);

        closeResultSet(ps_rs.right);

        return readers;
    }

    public ArrayList<Reader> getReadersWithSpecialDate(Date needed_date) throws JDBCConnectionException, DAOException {

        // Выполняем запрос (данные запишутся в переменную rs)
        ConnectionUrlParser.Pair<PreparedStatement, ResultSet> ps_rs = executeStatement(SELECT_ALL_READERS_WITH_SPECIAL_DATE, 8, needed_date.toString());

        ArrayList<Reader> readers = new ArrayList<>(); // Список читателей

        try {
            while(ps_rs.right.next())
            {
                Reader next_reader = new Reader(Integer.parseInt(ps_rs.right.getString("rID")),
                        ps_rs.right.getString("rName"),
                        ps_rs.right.getString("rDate"),
                        Integer.parseInt(ps_rs.right.getString("bID")));
                readers.add(next_reader);
            }
        } catch (SQLException throwables) {
            throw new DAOException("Error! Can't get data from ResultSet!", throwables);
        }

        closePreparedStatement(ps_rs.left);

        closeResultSet(ps_rs.right);

        return readers;
    }

    public ArrayList<Reader> getReadersWithSpecialBookID(int book_id) throws JDBCConnectionException, DAOException {

        // Выполняем запрос (данные запишутся в переменную rs)
        ConnectionUrlParser.Pair<PreparedStatement, ResultSet> ps_rs = executeStatement(SELECT_ALL_READERS_WITH_SPECIAL_BOOK_ID, 9, Integer.toString(book_id));

        ArrayList<Reader> readers = new ArrayList<>(); // Список читателей

        try {
            while(ps_rs.right.next())
            {
                Reader next_reader = new Reader(Integer.parseInt(ps_rs.right.getString("rID")),
                        ps_rs.right.getString("rName"),
                        ps_rs.right.getString("rDate"),
                        Integer.parseInt(ps_rs.right.getString("bID")));
                readers.add(next_reader);
            }
        } catch (SQLException throwables) {
            throw new DAOException("Error! Can't get data from ResultSet!", throwables);
        }

        closePreparedStatement(ps_rs.left);

        closeResultSet(ps_rs.right);

        return readers;
    }

    public Reader getReaderWithSpecialID(int reader_id) throws JDBCConnectionException, DAOException {

        // Выполняем запрос (данные запишутся в переменную rs)
        ConnectionUrlParser.Pair<PreparedStatement, ResultSet> ps_rs = executeStatement(SELECT_READER_BY_READER_ID, 10, Integer.toString(reader_id));

        Reader reader = null; // Читатель

        try {
            if (ps_rs.right.next())
            {
                reader = new Reader(Integer.parseInt(ps_rs.right.getString("rID")),
                        ps_rs.right.getString("rName"),
                        ps_rs.right.getString("rDate"),
                        Integer.parseInt(ps_rs.right.getString("bID")));
            }
        } catch (SQLException throwables) {
            throw new DAOException("Error! Can't get data from ResultSet!", throwables);
        }

        closePreparedStatement(ps_rs.left);

        closeResultSet(ps_rs.right);

        return reader;
    }

    public void addReaderWithInfo(String reader_name, int book_id) throws JDBCConnectionException, DAOException {

        // Выполняем запрос (данные запишутся в переменную rs)
        executeUpdateStatement(ADD_READER_WITH_INFO, 11, reader_name + "|" + book_id);
    }

    public void deleteReaderByID(int reader_id) throws JDBCConnectionException, DAOException {

        // Выполняем запрос (данные запишутся в переменную rs)
        executeUpdateStatement(DELETE_READER_BY_ID, 12, Integer.toString(reader_id));
    }

    public int checkBorrowedBookByReader(int reader_id, int book_id) throws JDBCConnectionException, DAOException {

        // Выполняем запрос (данные запишутся в переменную rs)
        ConnectionUrlParser.Pair<PreparedStatement, ResultSet> ps_rs = executeStatement(CHECK_IF_THERE_IS_BORROWED_BOOK_BY_READER, 13, reader_id + "|" + book_id);

        int check = 0; // 1 - if exists, 0 - if not exists

        try {
            if (ps_rs.right.next())
            {
                check = Integer.parseInt(ps_rs.right.getString("EXISTS(SELECT * FROM readers WHERE rID = " + reader_id + " AND bID = " + book_id + ")"));
            }
        } catch (SQLException throwables) {
            throw new DAOException("Error! Can't get data from ResultSet!", throwables);
        }

        closePreparedStatement(ps_rs.left);

        closeResultSet(ps_rs.right);

        return check;
    }

}
