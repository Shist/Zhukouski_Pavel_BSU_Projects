package bel.mmkle.dto;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.math.BigDecimal;

/**
 * DTO для сущности Journey
 */


@AllArgsConstructor
@NoArgsConstructor
@Data
@Builder
public class JourneyDto {
    private String regNum;

    private Long requestId;

    private String isFinish;

    private BigDecimal carState;
}
