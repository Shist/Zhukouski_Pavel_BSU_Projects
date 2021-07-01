package model.entity;

import javax.annotation.Generated;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@Generated(value = "org.hibernate.jpamodelgen.JPAMetaModelEntityProcessor")
@StaticMetamodel(Authorization.class)
public abstract class Authorization_ {

	public static volatile SingularAttribute<Authorization, String> password;
	public static volatile SingularAttribute<Authorization, String> user_type;
	public static volatile SingularAttribute<Authorization, String> login;

	public static final String PASSWORD = "password";
	public static final String USER_TYPE = "user_type";
	public static final String LOGIN = "login";

}

