package model.entity;

import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@StaticMetamodel(Book.class)
public class Book_ {

    public static volatile SingularAttribute<Book, Integer> id;
    public static volatile SingularAttribute<Book, String> name;
    public static volatile SingularAttribute<Book, String> author;
    public static volatile SingularAttribute<Book, Integer> number_of_instance;

}
