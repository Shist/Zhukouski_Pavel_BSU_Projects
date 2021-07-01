package bel.pvzhu.dto;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * DTO для сущности Book
 */

@Data
@Builder
@NoArgsConstructor
@AllArgsConstructor
public class BookDto {
    private String bAuthor;
}
