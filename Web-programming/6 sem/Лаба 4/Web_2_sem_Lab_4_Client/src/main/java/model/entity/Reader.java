package model.entity;


import javax.persistence.*;
import java.io.Serializable;
import java.sql.Date;

import static model.entity.Reader.readerTable;

@Entity
@Table(name = readerTable)
public class Reader implements Serializable {

    public static final String readerTable = "reader";
    private static final String readerId = "id_reader";
    private static final String readerName = "name";
    private static final String readerBirthDate = "birth_date";

    @Id
    @GeneratedValue
    @Column(name = readerId)
    private int id;

    @Column(name = readerName)
    private String name;

    @Column(name = readerBirthDate)
    private Date birth_date;

    public Reader() {}

    public Reader(int id, String name, Date birth_date) {
        this.id = id;
        this.name = name;
        this.birth_date = birth_date;
    }

    public int getId() { return id; }

    public String getName() { return name; }

    public Date getBirth_date() { return birth_date; }

    public void setId(int id) { this.id = id; }

    public void setName(String name) { this.name = name; }

    public void setBirth_date(Date birth_date) { this.birth_date = birth_date; }

    @Override
    public String toString() {

        return String.format("ID: %s\nName: %.2f\nBirth date: %s\n",
                id, name, birth_date);
    }
}
