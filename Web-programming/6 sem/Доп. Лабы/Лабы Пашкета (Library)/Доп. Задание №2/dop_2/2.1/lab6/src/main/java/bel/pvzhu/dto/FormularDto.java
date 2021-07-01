package bel.pvzhu.dto;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.math.BigDecimal;

/**
 * DTO для сущности Formular
 */


@AllArgsConstructor
@NoArgsConstructor
@Data
@Builder
public class FormularDto {
    private String bAuthor;

    private Long requestId;

    private String isReturned;

    private BigDecimal bookState;
}
