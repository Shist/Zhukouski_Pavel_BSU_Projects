package model.entity;

import model.exception.DAOException;

import javax.persistence.*;
import java.sql.Date;

import static model.entity.Reader.readerTable;

@Entity
@Table(name = readerTable)
public class Reader {

    public static final String readerTable = "readers";
    private static final String readerId = "rID";
    private static final String readerName = "rName";
    private static final String readerBirthDate = "rDate";

    @Id
    @GeneratedValue
    @Column(name = readerId)
    private int id;

    @Column(name = readerName)
    private String name;

    @Column(name = readerBirthDate)
    private Date birth_date;

    public Reader() {}

    public Reader(int id, String name, Date birth_date) throws DAOException {
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
