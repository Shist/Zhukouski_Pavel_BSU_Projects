package model.entity;

import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;
import java.util.Date;

@StaticMetamodel(Reader.class)
public class Reader_ {

    public static volatile SingularAttribute<Reader, Integer> id;
    public static volatile SingularAttribute<Reader, String> name;
    public static volatile SingularAttribute<Reader, Date> birth_date;
}
