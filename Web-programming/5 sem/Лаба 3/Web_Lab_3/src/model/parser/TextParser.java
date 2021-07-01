package model.parser;

import model.Text;
import model.exception.InvalidParsingException;
import model.text_unit.text.TextUnit;


import java.util.ArrayList;

/**
 *
 * @author Zhukouski Pavel
 *
 */
public class TextParser {

    /**
     * next splitter
     */
    private ParagraphTextParser nextSplitter;


    /**
     * constructor for text parser
     */
    public TextParser() {
        nextSplitter = new ParagraphTextParser();
    }

    /**
     * split text codeBlock and paragraph
     * @param textString text
     * @return return Text object
     */
    public Text splitText(String textString) throws InvalidParsingException {
        Text text = new Text();
        ArrayList<TextUnit> result;
        try {
            result = nextSplitter.split(trim(textString));
        } catch (Exception e) {
            throw e;
        }

        text.setText(result);
        return text;
    }

    /**
     * replace tabs
     * @param text text
     * @return replaced text
     */
    protected String trim(String text){
        text = text.trim();
        text = text.replaceAll( "[\t ]+", " ");
        return text;
    }

}
