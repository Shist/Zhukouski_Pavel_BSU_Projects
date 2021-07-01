package model.dao;

import model.entity.Authorization;
import model.entity.Authorization_;

import javax.persistence.EntityManager;
import javax.persistence.criteria.CriteriaBuilder;
import javax.persistence.criteria.CriteriaQuery;
import javax.persistence.criteria.Root;
import java.util.List;

public class DAOAuthorization extends DAO {

    public DAOAuthorization(){super();}

    public String login(String login, String password){
        String user_type = null;
        EntityManager entityManager = null;
        List<Authorization> users;
        String pass;
        try{
            entityManager = getEntityManagerFactory().createEntityManager();
            CriteriaBuilder cb = entityManager.getCriteriaBuilder();
            CriteriaQuery<Authorization> cq = cb.createQuery(Authorization.class);
            Root<Authorization> bookRoot = cq.from(Authorization.class);
            cq.where(cb.equal(bookRoot.get(Authorization_.login), login));
            users = entityManager.createQuery(cq)
                    .getResultList();
            if(!users.isEmpty() && users.size() == 1){
                pass = users.get(0).getPassword();
                if(pass.equals(password)){
                    user_type = users.get(0).getUser_type();
                }else {
                    System.out.println("incorrect password!!");
                }
            }else {
                System.out.println("more than one user with the same passwords.");
            }
        }finally {
            if (entityManager != null && entityManager.isOpen())
                entityManager.close();
        }
        return user_type;
    }
}
