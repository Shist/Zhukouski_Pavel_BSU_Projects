package model.entity;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.Table;
import java.io.Serializable;

import static model.entity.Authorization.authorizationTable;

@Entity
@Table(name = authorizationTable)
public class Authorization implements Serializable {

    public static final String authorizationTable = "authorization";

    public static final String log = "login";

    public static final String pass = "password";

    public  static final String type = "type";

    @Id
    @Column(unique = true, name = log)
    private String login;

    @Column(name = pass)
    private String password;

    @Column(name = type)
    private String user_type;

    Authorization(){}

    Authorization(String login, String password, String type){
        this.login = login;
        this.password = password;
        this.user_type = type;
    }

    public String getLogin() {
        return login;
    }

    public String getPassword() {
        return password;
    }

    public String getUser_type() {
        return user_type;
    }

    public void setLogin(String login) {
        this.login = login;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public void setUser_type(String user_type) {
        this.user_type = user_type;
    }

    @Override
    public String toString() {
        return "Authorization{" +
                "login='" + login + '\'' +
                ", password='" + password + '\'' +
                ", user_type='" + user_type + '\'' +
                '}';
    }
}


