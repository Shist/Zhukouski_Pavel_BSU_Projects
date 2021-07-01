package model.entity;

import javax.persistence.*;
import java.io.Serializable;
import java.sql.Date;

import static model.entity.Formular.formularTable;

@Entity
@Table(name = formularTable)
public class Formular implements Serializable {

    public static final String formularTable = "formular";
    private static final String formularId = "id_formular";
    private static final String book_id = "books_id_books";
    private static final String reader_id = "reader_id_reader";
    private static final String start_date = "start_date";
    private static final String end_date = "end_date";
    private static final String return_date = "return_date";

    @Id
    @GeneratedValue
    @Column(name = formularId)
    private int id;

    @ManyToOne
    @JoinColumn(name = reader_id)
    private Reader reader;

    @OneToOne
    @JoinColumn(name = book_id)
    private Book book;

    @Column(name = start_date)
    private Date start_day;

    @Column(name = end_date)
    private Date end_day;

    @Column(name = return_date)
    private Date return_day;


    public Formular(){}

    public Formular(int id){
        this.id = id;
    }

    public int getId() { return id; }
    public void setId(int id) { this.id = id; }

    public Date getStart_day() { return start_day; }

    public Date getEnd_day() { return end_day; }

    public Date getReturn_day() { return return_day; }

    public Reader getReader() {
        return reader;
    }

    public void setReader(Reader reader) {
        this.reader = reader;
    }

    public Book getBook() {
        return book;
    }

    public void setBook(Book book) {
        this.book = book;
    }

    public void setStart_day(Date start_day) { this.start_day = start_day; }

    public void setEnd_day(Date end_day) { this.end_day = end_day; }

    public void setReturn_day(Date return_day) { this.return_day = return_day; }
}
