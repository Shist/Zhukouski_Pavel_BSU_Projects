package bel.mmkle.entity;

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
@Table(name = "drivers")
@NamedQueries({
        @NamedQuery(name = "Drivers.findDriverIdByRegNum", query = "select d.driverId from Drivers d where d.regNum = :regNum"),
        @NamedQuery(name = "Drivers.findCarByDriverId", query = "select d.car from Drivers d where d.driverId = :driverId"),
})

public class Drivers implements Serializable {
    /**
     * id водителя
     */
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long driverId;

    /**
     * Имя
     */
    @Column
    private String name;

    /**
     * id машины закрепленной за водителем
     */
    @OneToOne(fetch = FetchType.EAGER)
    @JoinColumn(name = "carId")
    private Cars car;

    /**
     * Регистрационный номер водителя
     */
    @Column
    private String regNum;
}
