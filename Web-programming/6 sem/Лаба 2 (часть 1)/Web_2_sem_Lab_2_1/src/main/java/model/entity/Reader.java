package model.entity;

import model.exception.DAOException;

import javax.persistence.*;
import java.sql.Date;

import static model.entity.Reader.readerTable;

/**
 * Entity class Reader
 * @author Pavel Zhukouskiy
 * @version 1.0
 */

@Entity
@Table(name = readerTable)
@NamedQueries({
        @NamedQuery(name = "printAllReaders",
                query = "select re from Reader re"),
        @NamedQuery(name = "getReaderInfoByID",
                query = "select re from Reader re where re.id = :id")
})
public class Reader {

    public static final String readerTable = "readers";
    public static final String readerId = "rID";
    public static final String readerName = "rName";
    public static final String readerBirthDate = "rDate";

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
