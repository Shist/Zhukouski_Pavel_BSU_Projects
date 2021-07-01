package model.dao;

import model.entity.Formular;
import model.entity.Reader;

import javax.ejb.Remote;
import java.util.List;

/**
 * IDAOFormular interface
 * @version 1.0
 * @author Pavel Zhukouskiy
 */
@Remote
public interface IDAOFormular {

    /**
     * Method to return book
     * @param book_id book id
     */
    void returnBook(int reader_id, int book_id);

    /**
     * Method that write reader id, date when reader took book and when he should return book
     * @param book_id book id
     * @param reader_id reader id
     */
    void updateReaderInfo(int book_id, int reader_id);

    /**
     * Method to get debtors info
     * @return List of debtors
     */
    List<Formular> getDebtors();

}
