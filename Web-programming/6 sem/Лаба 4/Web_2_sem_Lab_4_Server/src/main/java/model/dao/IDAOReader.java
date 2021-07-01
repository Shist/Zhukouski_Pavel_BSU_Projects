package model.dao;

import model.entity.Reader;

import javax.ejb.Remote;
import java.util.List;

/**
 * IDAOReader interface
 * @version 1.0
 * @author Pavel Zhukouskiy
 */
@Remote
public interface IDAOReader {

    /**
     * Print all reader from table reader
     */
    List<Reader> printAllReaders();

    /**
     * Method to get reader info by reader id
     * @param id reader id
     * @return Reader object
     */
    Reader getReaderInfoById(int id);
}
