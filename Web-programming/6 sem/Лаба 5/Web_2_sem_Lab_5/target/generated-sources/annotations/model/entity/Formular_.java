package model.entity;

import java.sql.Date;
import javax.annotation.Generated;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@Generated(value = "org.hibernate.jpamodelgen.JPAMetaModelEntityProcessor")
@StaticMetamodel(Formular.class)
public abstract class Formular_ {

	public static volatile SingularAttribute<Formular, Date> end_day;
	public static volatile SingularAttribute<Formular, Date> start_day;
	public static volatile SingularAttribute<Formular, Date> return_day;
	public static volatile SingularAttribute<Formular, Reader> reader;
	public static volatile SingularAttribute<Formular, Book> book;
	public static volatile SingularAttribute<Formular, Integer> id;

	public static final String END_DAY = "end_day";
	public static final String START_DAY = "start_day";
	public static final String RETURN_DAY = "return_day";
	public static final String READER = "reader";
	public static final String BOOK = "book";
	public static final String ID = "id";

}

