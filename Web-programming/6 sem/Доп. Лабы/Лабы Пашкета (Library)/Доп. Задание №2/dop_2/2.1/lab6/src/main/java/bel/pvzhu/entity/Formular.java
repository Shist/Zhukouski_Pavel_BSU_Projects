package bel.pvzhu.entity;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;
import org.hibernate.annotations.NotFound;
import org.hibernate.annotations.NotFoundAction;

import javax.persistence.*;
import java.io.Serializable;
import java.math.BigDecimal;

/**
 * Класс для сущности Formular
 *
 * @author mmkle
 */

@Data
@AllArgsConstructor
@NoArgsConstructor
@Builder
@Entity
@Table(name = "Formular")
@NamedQueries({
        @NamedQuery(name = "Formular.findFormularIdByRequestId", query = "select j.formularId from Formular j where j.request.requestId = :requestId"),
        @NamedQuery(name = "Formular.findAll", query = "select j from Formular j"),
        @NamedQuery(name = "Formular.findFormularForReader", query = "select j from Formular j where j.book.bookId = :bookId")
})
public class Formular implements Serializable {
    /**
     * id записи формуляра
     */
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long formularId;

    /**
     * id книги
     */
    @ManyToOne(fetch = FetchType.EAGER)
    @JoinColumn(name = "bookId")
    private Books book;

    /**
     * id запроса для книги
     */
    @ManyToOne(fetch = FetchType.EAGER)
    @NotFound(action= NotFoundAction.IGNORE)
    @JoinColumn(name = "requestId")
    private Requests request;

    /**
     * Книга возвращена (0 - нет, 1 - да)
     */
    @Column
    private Integer isReturned;

    /**
     * Состояние книги после чтения
     */
    @Column
    private BigDecimal bookState;
}
