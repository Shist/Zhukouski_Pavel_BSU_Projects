package model.entity;

import javax.persistence.*;

import java.io.Serializable;

import static model.entity.Book.bookTable;

/**
 * Book entity class
 * @version 1.0
 * @author Pavel Zhukovskiy
 */
@Entity
@Table(name = bookTable)
public class Book implements Serializable {

    /**
     * Table name
     */
    public static final String bookTable = "books";
    /**
     * Names of column id_book in DB
     */
    private static final String bookId = "id_books";
    /**
     * Names of column book name in DB
     */
    private static final String bookName = "name";
    /**
     * Names of column book author in DB
     */
    private static final String bookAuthor = "author";
    /**
     * Names of column number of instance in DB
     */
    private static final String bookNumberOfInstance = "number_of_instances";

    /**
     * Book id field
     */
    @Id
    @GeneratedValue
    @Column(name = bookId)
    private int id;

    /**
     * Book name field
     */
    @Column(name = bookName)
    private String name;
    /**
     * Book author field
     */
    @Column(name = bookAuthor)
    private String author;
    /**
     * Book number of instances field
     */
    @Column(name = bookNumberOfInstance)
    private int number_of_instance;

    /**
     * Constructor without params
     */
    public Book(){}

    /**
     * Constructor with params
     * @param id_books book id
     * @param name book name
     * @param author book author
     * @param number_of_instance books' number of instance
     */
    public Book(int id_books, String name, String author, int number_of_instance) {
        this.id = id_books;
        this.name = name;
        this.author = author;
        this.number_of_instance = number_of_instance;
    }

    /**
     * Get book id
     * @return book id
     */
    public int getId() {
        return id;
    }

    /**
     * Get book name
     * @return book name
     */
    public String getName() {
        return name;
    }

    /**
     * Get book author
     * @return book author
     */
    public String getAuthor() {
        return author;
    }

    /**
     * Get book number of instances
     * @return book number of instances
     */
    public int getNumber_of_instance() {
        return number_of_instance;
    }

    /**
     * Set book id
     * @param id book id
     */
    public void setId(int id) { this.id = id; }

    /**
     * Set book name
     * @param name book name
     */
    public void setName(String name) { this.name = name; }

    /**
     * Set book author
     * @param author book author
     */
    public void setAuthor(String author) { this.author = author; }

    /**
     * Set book number of instance
     * @param number_of_instance book number of instance
     */
    public void setNumber_of_instance(int number_of_instance) { this.number_of_instance = number_of_instance; }

    /**
     * To string method
     * @return string
     */
    @Override
    public String toString() {
        return "Book{" +
                "id=" + id +
                ", name='" + name + '\'' +
                ", author='" + author + '\'' +
                ", number_of_instance=" + number_of_instance +
                '}';
    }
}
