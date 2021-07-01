package by.mmkle.model;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

import javax.persistence.*;
import java.io.Serializable;


/**
 * Класс для сущности Driver
 *
 * @author mmkle
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
@Builder
@Entity
@SequenceGenerator(name = "PK_drivers", sequenceName = "drivers_seq", allocationSize = 1)
@Table(name = "drivers")
@NamedQueries({
        @NamedQuery(name = "Drivers.findDriverIdByRegNum", query = "select d.driverId from Drivers d where d.regNum = :regNum"),
        @NamedQuery(name = "Drivers.findCarIdByDriverId", query = "select d.car from Drivers d where d.driverId = :driverId"),
})

public class Drivers implements Serializable {
    /**
     * id водителя
     */
    @Id
    @GeneratedValue(strategy = GenerationType.SEQUENCE, generator = "PK_drivers")
    private Long driverId;

    /**
     * Имя
     */
    @Column
    private String name;

    /**
     * id машины закрепленной за водителем
     */
    @OneToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "carId")
    private Cars car;

    /**
     * Регистрационный номер водителя
     */
    @Column
    private String regNum;
}
