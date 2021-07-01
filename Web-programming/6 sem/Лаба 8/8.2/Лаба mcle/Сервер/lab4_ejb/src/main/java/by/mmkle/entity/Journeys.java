package by.mmkle.entity;

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
 * Класс для сущности Journeys
 *
 * @author mmkle
 */

@Data
@AllArgsConstructor
@NoArgsConstructor
@Builder
@Entity
@Table(name = "journeys")
@NamedQueries({
        @NamedQuery(name = "Journeys.findJourneyIdByRequestId", query = "select j.journeyId from Journeys j where j.request.requestId = :requestId"),
        @NamedQuery(name = "Journeys.findAll", query = "select j from Journeys j"),
        @NamedQuery(name = "Journeys.findJourneysForDriver", query = "select j from Journeys j where j.car.carId = :carId")
})
public class Journeys implements Serializable {
    /**
     * id рейса
     */
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long journeyId;

    /**
     * id машины исполняющей рейс
     */
    @ManyToOne(fetch = FetchType.EAGER)
    @JoinColumn(name = "carId")
    private Cars car;

    /**
     * id запроса для рейса
     */
    @ManyToOne(fetch = FetchType.EAGER)
    @NotFound(action= NotFoundAction.IGNORE)
    @JoinColumn(name = "requestId")
    private Requests request;

    /**
     * Рейс завершился (0 - нет, 1 - да)
     */
    @Column
    private Integer isFinish;

    /**
     * Состояние машины после рейса
     */
    @Column
    private BigDecimal carState;
}
