package model.entity;

import java.sql.Date;
import javax.annotation.Generated;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@Generated(value = "org.hibernate.jpamodelgen.JPAMetaModelEntityProcessor")
@StaticMetamodel(Reader.class)
public abstract class Reader_ {

	public static volatile SingularAttribute<Reader, Date> birth_date;
	public static volatile SingularAttribute<Reader, String> name;
	public static volatile SingularAttribute<Reader, Integer> id;

	public static final String BIRTH_DATE = "birth_date";
	public static final String NAME = "name";
	public static final String ID = "id";

}

