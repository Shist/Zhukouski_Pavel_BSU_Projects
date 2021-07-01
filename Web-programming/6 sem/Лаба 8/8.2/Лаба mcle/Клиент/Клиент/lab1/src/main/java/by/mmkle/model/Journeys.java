package by.mmkle.model;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

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
@SequenceGenerator(name = "PK_journeys", sequenceName = "journeys_seq", allocationSize = 1)
@Table(name = "journeys")
@NamedQueries({
        @NamedQuery(name = "Journeys.findJourneyIdByRequestId", query = "select j.journeyId from Journeys j where j.request.requestId = :requestId"),
        @NamedQuery(name = "Journeys.setJourneyIsFinishAndCarState", query = "update Journeys j set j.isFinish = 1, j.carState = :carState where j.journeyId =:journeyId"),
        @NamedQuery(name = "Journeys.findAll", query = "select j from Journeys j"),
        @NamedQuery(name = "Journeys.updateCarForJourney", query = "update Journeys j set j.car = :car where j.journeyId = :journeyId"),
        @NamedQuery(name = "Journeys.findJourneysForDriver", query = "select j from Journeys j where j.car.carId = :carId")
})
public class Journeys implements Serializable {
    /**
     * id рейса
     */
    @Id
    @GeneratedValue(strategy = GenerationType.SEQUENCE, generator = "PK_journeys")
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
    @ManyToOne(fetch = FetchType.LAZY)
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
