package model.entity;

import javax.persistence.*;
import java.io.Serializable;

import static model.entity.User.authorizationTable;

@Entity
@Table(name = authorizationTable)
public class User implements Serializable {

    public static final String authorizationTable = "user";

    public static final String log = "login";

    public static final String pass = "password";

    public  static final String type = "type";

    public static final String name = "name";

    @Id
    @Column(unique = true, name = log)
    private String login;

    @Column(name = pass)
    private String password;

    @Column(name = type)
    private String user_type;

    @Column(name = name)
    private String real_name;


    public User(){}

    public User(String login, String password, String type, String real_name){
        this.login = login;
        this.password = password;
        this.user_type = type;
        this.real_name = real_name;
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
        return "User{" +
                "login='" + login + '\'' +
                ", password='" + password + '\'' +
                ", user_type='" + user_type + '\'' +
                '}';
    }
}


