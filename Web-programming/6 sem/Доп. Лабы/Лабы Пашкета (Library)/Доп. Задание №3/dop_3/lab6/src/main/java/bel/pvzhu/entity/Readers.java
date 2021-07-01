package bel.pvzhu.entity;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

import javax.persistence.*;
import java.io.Serializable;


/**
 * Класс для сущности Reader
 *
 * @author mmkle
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
@Builder
@Entity
@Table(name = "readers")
@NamedQueries({
        @NamedQuery(name = "Readers.findReaderIdByBAuthor", query = "select d.readerId from Readers d where d.bAuthor = :bAuthor"),
        @NamedQuery(name = "Readers.findBookByReaderId", query = "select d.book from Readers d where d.readerId = :readerId"),
})

public class Readers implements Serializable {
    /**
     * id читателя
     */
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long readerId;

    /**
     * Имя читателя
     */
    @Column
    private String name;

    /**
     * id книги, которую взял почитать читатель
     */
    @OneToOne(fetch = FetchType.EAGER)
    @JoinColumn(name = "bookId")
    private Books book;

    /**
     * Автор книги, которую взял почитать читатель
     */
    @Column
    private String bAuthor;
}
