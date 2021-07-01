package model.entity;

import javax.annotation.Generated;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@Generated(value = "org.hibernate.jpamodelgen.JPAMetaModelEntityProcessor")
@StaticMetamodel(User.class)
public abstract class User_ {

	public static volatile SingularAttribute<User, String> password;
	public static volatile SingularAttribute<User, String> user_type;
	public static volatile SingularAttribute<User, String> real_name;
	public static volatile SingularAttribute<User, String> login;

	public static final String PASSWORD = "password";
	public static final String USER_TYPE = "user_type";
	public static final String REAL_NAME = "real_name";
	public static final String LOGIN = "login";

}

