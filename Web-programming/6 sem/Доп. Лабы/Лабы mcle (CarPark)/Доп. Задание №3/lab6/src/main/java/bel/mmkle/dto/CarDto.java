package bel.mmkle.dto;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * DTO для сущности Car
 */

@Data
@Builder
@NoArgsConstructor
@AllArgsConstructor
public class CarDto {
    private String regNum;
}
