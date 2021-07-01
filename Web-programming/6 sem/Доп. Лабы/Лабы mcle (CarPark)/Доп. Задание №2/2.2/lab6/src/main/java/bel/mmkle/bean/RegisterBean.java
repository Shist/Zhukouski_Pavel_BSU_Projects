package bel.mmkle.bean;

import javax.ejb.EJB;
import javax.ejb.Singleton;
import javax.faces.bean.SessionScoped;
import javax.inject.Named;

@Named("Register")
@Singleton
@SessionScoped
public class RegisterBean {
    private String login;
    private String password;
    private String role;

    @EJB
    private UserBean userBean;

    public String getLogin() {
        return login;
    }

    public void setLogin(String login) {
        this.login = login;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getRole() {
        return role;
    }

    public void setRole(String role) {
        this.role = role;
    }

    public String regUser() {
        userBean.save(login, password, Long.valueOf(role));
        return "login?faces-redirect=true";
    }
}
