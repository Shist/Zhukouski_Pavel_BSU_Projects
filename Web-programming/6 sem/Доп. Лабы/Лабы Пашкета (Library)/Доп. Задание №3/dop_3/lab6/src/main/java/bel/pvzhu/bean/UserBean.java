package bel.pvzhu.bean;

import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import javax.persistence.Query;
import java.math.BigInteger;

/**
 * EJB боб для взаимодействия с сущностью User
 */

@Stateless
public class UserBean {
    @PersistenceContext(unitName = "my_factory")
    private EntityManager em;

    /**
     * Сохранение пользователя
     * @param login логин пользователя
     * @param pass пароль пользователя
     * @param roleId роль
     */
    public void save(String login, String pass, Long roleId){
        Query query = em.createNativeQuery("insert into users (login, pass, roleId) VALUES (?, ?, ?)")
                .setParameter(1, login)
                .setParameter(2, pass)
                .setParameter(3, roleId);
        query.executeUpdate();
    }

    /**
     * Вход пользователя по логину и паролю
     * @param login логин пользователя
     * @param pass пароль пользователя
     */
    public BigInteger login(String login, String pass){
        Query query = em.createNativeQuery("select userId from users where login = :login and pass = :pass")
                .setParameter("login", login)
                .setParameter("pass", pass);
        BigInteger userId = null;
        try{
            userId = ((BigInteger) query.getSingleResult());
        } catch (Exception ex){
            ex.printStackTrace();
        }
        return userId;
    }

    /**
     * Получаем роль пользователя
     */
    public Long getRole(Long userId) {
        Query query = em.createNativeQuery("select roleId from users where userId = :userId")
                .setParameter("userId", userId);

        BigInteger roleId = null;
        try{
            roleId = ((BigInteger) query.getSingleResult());
        } catch (Exception ex){
            ex.printStackTrace();
        }
        return roleId.longValue();
    }

    /**
     * Проверка есть ли пользователь с таким логином
     */
    public boolean check(String login) {
        Query query = em.createNativeQuery("select * from users where login = :login")
                .setParameter("login", login);

        return query.getResultList() == null;
    }
}
