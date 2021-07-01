package by.mmkle.entity;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

import javax.persistence.*;
import java.math.BigDecimal;

/**
 * Класс для сущности Request
 *
 * @author mmkle
 */

@Data
@AllArgsConstructor
@NoArgsConstructor
@Builder
@Entity
@Table(name = "requests")
@NamedQueries({
        @NamedQuery(name = "Requests.findRequestById", query = "select r from Requests r where r.requestId = :requestId"),
        @NamedQuery(name = "Requests.deleteRequestById", query = "delete from Requests r where r.requestId = :requestId"),
})

public class Requests {
    /**
     * id запроса
     */
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long requestId;

    /**
     * запрашиваемая вместимость
     */
    @Column
    private BigDecimal requiredCapability;

    /**
     * максимальная цена
     */
    @Column
    private BigDecimal maxCost;
}
