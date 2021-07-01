package model.dao;

import model.entity.Reader;
import model.entity.Reader_;

import javax.persistence.EntityManager;
import javax.persistence.criteria.CriteriaBuilder;
import javax.persistence.criteria.CriteriaQuery;
import javax.persistence.criteria.Root;
import java.util.List;

/**
 * DAO class to work with table reader
 * @author Pavel Zhukouskiy
 * @version 1.0
 */
public class DAOReader extends DAO {

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
        EntityManager entityManager = null;
        List<Reader> readerList;

        try{
            entityManager = getEntityManagerFactory().createEntityManager();
            CriteriaBuilder cb = entityManager.getCriteriaBuilder();
            CriteriaQuery<Reader> cq = cb.createQuery(Reader.class);
            Root<Reader> student = cq.from(Reader.class);
            cq.select(student);
            readerList = entityManager.createQuery(cq)
                    .getResultList();
        }finally {
            if (entityManager != null && entityManager.isOpen())
                entityManager.close();
        }

        return readerList;
    }

    /**
     * Method to get reader info by reader id
     * @param id reader id
     * @return Reader object
     */
    public Reader getReaderInfoById(int id) {
        EntityManager entityManager = null;
        Reader reader;

        try{
            entityManager = getEntityManagerFactory().createEntityManager();
            CriteriaBuilder cb = entityManager.getCriteriaBuilder();
            CriteriaQuery<Reader> readerCriteriaQuery = cb.createQuery(Reader.class);
            Root<Reader> readerRoot = readerCriteriaQuery.from(Reader.class);
            readerCriteriaQuery.where(cb.equal(readerRoot.get(Reader_.id), id));
            reader = entityManager.createQuery(readerCriteriaQuery).getSingleResult();
        }finally {
            if (entityManager != null && entityManager.isOpen())
                entityManager.close();
        }

        return reader;
    }
}
