package model.dao;

import javax.persistence.EntityManagerFactory;
import javax.persistence.Persistence;

/**
 * Parent DAO class
 * @author Pavel Zhukouskiy
 * @version 1.0
 */
public class DAO {

    private static String PERSISTENCE_UNIT_NAME = "lab1_var5";
    private EntityManagerFactory factory;

    /**
     * Constructor
     */
    DAO() {
        factory = Persistence.createEntityManagerFactory(PERSISTENCE_UNIT_NAME);
    }

    protected EntityManagerFactory getEntityManagerFactory() {
        return factory;
    }
}
