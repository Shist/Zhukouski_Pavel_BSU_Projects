package model.text_unit.text.part;

/**
 *
 * @author Zhukouski Pavel
 *
 */
public enum PunctuationMarkTypeEnum {
    DOT("."),
    COMMA(","),
    EXCLAMATION("!"),
    QUESTION("?"),
    COLON(":"),
    SEMICOLON(";"),
    SINGLE_QUOTES("'"),
    QUOTES("\"");

    private final String text;

    PunctuationMarkTypeEnum(final String text) {
        this.text = text;
    }

    @Override
    public String toString() {
        return text;
    }
}
