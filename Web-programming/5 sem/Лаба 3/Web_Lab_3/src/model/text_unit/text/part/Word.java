package model.text_unit.text.part;

import model.text_unit.text.TextUnit;
import model.text_unit.text.TextUnitTypeEnum;
/**
 *
 * @author Zhukouski Pavel
 *
 */
public class Word extends TextUnit implements Comparable<Word>{

    public static final String WORD_NAME = "WORD";
    public static final String DIVIDER = ",:;'\"";
    public static final String PATTERN = "[^ " + Paragraph.DIVIDER + Sentence.DIVIDER + DIVIDER +  "]+";

    /**
     * word value getter
     * @return word
     */
    public String getText() {
        return text;
    }

    /**
     * word value
     */
    private String text;

    /**
     * constructor
     * @param text word value
     *
     */
    public Word(String text) {
        super(text, TextUnitTypeEnum.WORD);
        this.text = text;
    }

    /**
     * method for counting how many symbol contains
     * @param symbol
     * @return number of hiw many symbol contains in word
     */
    public int countOfSymbol( String symbol)
    {
        int count = 0;
        for(int i=0; i<text.length();i++)
        {
            if(text.charAt(i)==symbol.charAt(0))
            {
                count++;
            }
        }

        return count;
    }

    @Override
    public String toString() {
        return text;
    }

    @Override
    public int compareTo(Word w)
    {
        return text.compareToIgnoreCase(w.text);
    }


}
