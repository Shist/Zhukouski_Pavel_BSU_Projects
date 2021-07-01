package bel.mmkle.bean;

import javax.ejb.EJB;
import javax.ejb.Singleton;
import javax.faces.bean.SessionScoped;
import javax.faces.context.FacesContext;
import javax.inject.Named;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.math.BigInteger;

@Named("Login")
@Singleton
@SessionScoped
public class LoginBean {
    private String login;
    private String password;
    private String userId;

    public String getUserId() {
        String value = userId;
        userId = null;
        return value;
    }

    public void setUserId(String userId) {
        this.userId = userId;
    }

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

    public String checkLogin() throws IOException {
        BigInteger userId = userBean.login(login, password);
        if (userId != null){
            this.userId = userId.toString();
            FacesContext facesContext = FacesContext.getCurrentInstance();
            HttpSession session = (HttpSession) facesContext.getExternalContext().getSession(true);
            session.setAttribute("userId", userId.longValue());
            facesContext.getExternalContext().redirect("/lab6/menu");
            return null;
        } else {
            return "loginfailed?faces-redirect=true";
        }

    }
}
