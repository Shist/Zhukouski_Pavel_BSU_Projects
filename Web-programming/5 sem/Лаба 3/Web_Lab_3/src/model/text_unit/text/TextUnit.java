package model.text_unit.text;

/**
 *
 * @author Zhukouski Pavel
 *
 */
public class TextUnit {

    /**
     * type of text
     */
    protected TextUnitTypeEnum type;

    /**
     * value getter
     * @return string value
     */
    public String getValue() {
        return value;
    }

    /**
     * value
     *
     */
    protected String value;

    /**
     * getter for type of text
     * @return type of text
     */
    public TextUnitTypeEnum getType() {
        return type;
    }

    /**
     * constructor
     * @param value value of text unit
     * @param type type of text unit
     *
     */
    protected TextUnit(String value, TextUnitTypeEnum type){
        if( type == null){
            throw new IllegalArgumentException( "Illegal argument type" );
        }
        this.type = type;
        this.value = value;
    }

}
