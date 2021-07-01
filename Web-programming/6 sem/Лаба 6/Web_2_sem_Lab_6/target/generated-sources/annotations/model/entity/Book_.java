package model.entity;

import javax.annotation.Generated;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@Generated(value = "org.hibernate.jpamodelgen.JPAMetaModelEntityProcessor")
@StaticMetamodel(Book.class)
public abstract class Book_ {

	public static volatile SingularAttribute<Book, String> author;
	public static volatile SingularAttribute<Book, String> name;
	public static volatile SingularAttribute<Book, Integer> id;
	public static volatile SingularAttribute<Book, Integer> number_of_instance;

	public static final String AUTHOR = "author";
	public static final String NAME = "name";
	public static final String ID = "id";
	public static final String NUMBER_OF_INSTANCE = "number_of_instance";

}

