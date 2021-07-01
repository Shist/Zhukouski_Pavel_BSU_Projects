package model.dao;

import model.entity.Reader;
import model.entity.Reader_;

import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import javax.persistence.criteria.CriteriaBuilder;
import javax.persistence.criteria.CriteriaQuery;
import javax.persistence.criteria.Root;
import java.util.List;

/**
 * DAO class to work with table reader
 * @author Pavel Zhukouskiy
 * @version 1.0
 */
@Stateless
public class DAOReader implements IDAOReader {

    /**
     * Entity manager field
     */
    @PersistenceContext(unitName = "lab4_var5_server")
    private EntityManager entityManager;

    /**
     * Constructor
     */
    public DAOReader() {
        super();
    }

    /**
     * Print all reader from table reader
     */
    public List<Reader> printAllReaders() {

        CriteriaBuilder cb = entityManager.getCriteriaBuilder();
        CriteriaQuery<Reader> cq = cb.createQuery(Reader.class);
        Root<Reader> student = cq.from(Reader.class);
        cq.select(student);

        return entityManager.createQuery(cq)
                .getResultList();
    }

    /**
     * Method to get reader info by reader id
     * @param id reader id
     * @return Reader object
     */
    public Reader getReaderInfoById(int id) {

        CriteriaBuilder cb = entityManager.getCriteriaBuilder();
        CriteriaQuery<Reader> readerCriteriaQuery = cb.createQuery(Reader.class);
        Root<Reader> readerRoot = readerCriteriaQuery.from(Reader.class);
        readerCriteriaQuery.where(cb.equal(readerRoot.get(Reader_.id), id));

        return entityManager.createQuery(readerCriteriaQuery).getSingleResult();
    }
}
