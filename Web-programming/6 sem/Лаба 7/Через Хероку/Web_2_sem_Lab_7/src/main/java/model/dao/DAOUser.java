package model.dao;

import model.entity.User;
import model.entity.User_;

import javax.persistence.EntityManager;
import javax.persistence.EntityTransaction;
import javax.persistence.NoResultException;
import javax.persistence.TypedQuery;
import javax.persistence.criteria.CriteriaBuilder;
import javax.persistence.criteria.CriteriaQuery;
import javax.persistence.criteria.Root;
import java.util.List;

public class DAOUser extends DAO {

    public DAOUser(){super();}

    public boolean loginHandler(String login){
        EntityManager entityManager = null;
        boolean result;

        try {
            entityManager = getEntityManagerFactory().createEntityManager();
            CriteriaBuilder cb = entityManager.getCriteriaBuilder();
            CriteriaQuery<Long> cq = cb.createQuery(Long.class);
            Root<User> user = cq.from(User.class);

            cq.select(cb.count(user));
            cq.where(cb.equal(user.get(User_.login), login));

            TypedQuery<Long> tq = entityManager.createQuery(cq);
            result = tq.getSingleResult() > 0;

        } finally {
            if (entityManager != null && entityManager.isOpen())
                entityManager.close();
        }

        return result;
    }

    public User login(String login, String password){
        String user_type = null;
        EntityManager entityManager = null;
        User users;
        String pass;
        try{
            entityManager = getEntityManagerFactory().createEntityManager();
            CriteriaBuilder cb = entityManager.getCriteriaBuilder();
            CriteriaQuery<User> cq = cb.createQuery(User.class);
            Root<User> bookRoot = cq.from(User.class);
            cq.where(cb.equal(bookRoot.get(User_.login), login), cb.equal(bookRoot.get(User_.password), password));
            users = entityManager.createQuery(cq)
                    .getSingleResult();
        }finally {
            if (entityManager != null && entityManager.isOpen())
                entityManager.close();
        }
        return users;
    }

    public void createAccount(User user) {
        EntityManager entityManager = null;
        EntityTransaction transaction = null;

        try {
            entityManager = getEntityManagerFactory().createEntityManager();
            transaction = entityManager.getTransaction();

            transaction.begin();
            entityManager.persist(user);
            transaction.commit();
        } catch (Exception e) {
            if (transaction != null && transaction.isActive())
                transaction.rollback();
            System.out.println("Failed while inserting");
            e.printStackTrace();
        } finally {
            if (entityManager != null && entityManager.isOpen())
                entityManager.close();
        }
    }
}
