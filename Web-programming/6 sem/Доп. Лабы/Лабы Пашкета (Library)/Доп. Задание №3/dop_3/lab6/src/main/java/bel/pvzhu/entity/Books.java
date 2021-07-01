package bel.pvzhu.entity;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

import javax.persistence.*;
import java.io.Serializable;
import java.math.BigDecimal;

/**
 * Класс для сущности Book
 *
 * @author mmkle
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
@Builder
@Entity
@Table(name = "books")
@NamedQueries({
        @NamedQuery(name = "Books.findBookById", query = "select c from Books c where c.bookId = :bookId"),
        @NamedQuery(name = "Books.getAll", query = "SELECT c from Books c"),
        @NamedQuery(name = "Books.findBookIdByBAuthor", query = "select c.bookId from Books c where c.bAuthor = :bAuthor"),
        @NamedQuery(name = "Books.findBooksOnDistrib", query = "select c from Books c where c.onDistrib = 1"),
        @NamedQuery(name = "Books.findBookIdByRequirements", query = "select c.bookId from Formular j join j.book c where c.onDistrib = 0 and c.popularity >= :popularity and c.cost <= :cost and j.isReturned = 1"),
})
public class Books implements Serializable {
    /**
     * id книги
     */
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long bookId;

    /**
     * Популярность
     */
    @Column
    private BigDecimal popularity;

    /**
     * Цена
     */
    @Column
    private BigDecimal cost;

    /**
     * На раздаче (0 - нет, 1 - да)
     */
    @Column
    private Integer onDistrib;

    /**
     * Автор
     */
    private String bAuthor;
}
