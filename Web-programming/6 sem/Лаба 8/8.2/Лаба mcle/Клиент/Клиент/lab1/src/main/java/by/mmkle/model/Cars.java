package by.mmkle.model;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

import javax.persistence.*;
import java.io.Serializable;
import java.math.BigDecimal;

/**
 * Класс для сущности Car
 *
 * @author mmkle
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
@Builder
@Entity
@SequenceGenerator(name = "PK_cars", sequenceName = "cars_seq", allocationSize = 1)
@Table(name = "cars")
@NamedQueries({
        @NamedQuery(name = "Cars.findCarById", query = "select c from Cars c where c.carId = :carId"),
        @NamedQuery(name = "Cars.findCarIdByRegNum", query = "select c.carId from Cars c where c.regNum = :regNum"),
        @NamedQuery(name = "Cars.findCarsOnRepair", query = "select c from Cars c where c.onRepair = 1"),
        @NamedQuery(name = "Cars.setCarOnRepair", query = "update Cars c set c.onRepair = 1 where c.carId = :carId"),
        @NamedQuery(name = "Cars.findCarIdByRequirements", query = "select c.carId from Journeys j " +
                "join j.car c " +
                "where c.onRepair = 0 and c.capability >= :capability and c.cost <= :cost and j.isFinish = 1"),
})

public class Cars implements Serializable {
    /**
     * id машины
     */
    @Id
    @GeneratedValue(strategy = GenerationType.SEQUENCE, generator = "PK_cars")
    private Long carId;

    /**
     * Вместительность
     */
    @Column
    private BigDecimal capability;

    /**
     * Цена
     */
    @Column
    private BigDecimal cost;

    /**
     * На ремонте (0 - нет, 1 - да)
     */
    @Column
    private Integer onRepair;

    /**
     * Регистрационный номер машины
     */
    private String regNum;
}
