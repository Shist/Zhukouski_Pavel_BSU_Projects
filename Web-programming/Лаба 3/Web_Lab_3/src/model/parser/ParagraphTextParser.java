package model.parser;


import model.exception.InvalidParsingException;
import model.text_unit.code.CodeBlock;
import model.text_unit.text.TextUnit;
import model.text_unit.text.part.Paragraph;

import java.util.ArrayList;

/**
 *
 * @author Zhukouski Pavel
 *
 */
public class ParagraphTextParser {

    /**
     * next splitter
     */
    private SentenceTextParser nextSplitter;

    /**
     * constructor for parser
     */
    ParagraphTextParser(){
        nextSplitter = new SentenceTextParser();
    }

    /**
     * split text into paragraph
     * @param text
     * @return array with our text
     * @throws InvalidParsingException
     */
    public ArrayList<TextUnit> split(String text) throws InvalidParsingException {
        ArrayList<TextUnit> result = new ArrayList<>();
        String[] split = text.split(CodeBlock.DIVIDER);
        for (int i = 0; i < split.length; i++){
            if ((i & 1) == 1) {
                split[i] = trim(split[i]);
                if(split[i].length() > 0){
                    result.add(new CodeBlock(split[i]));
                }
            } else {
                String [] paragraphs = split[i].split(Paragraph.DIVIDER_PATTERN);
                for(int j = 0; j < paragraphs.length; j++){
                    paragraphs[j] = trim(paragraphs[j]);
                    if(paragraphs[j].length() > 0){
                        result.add(new Paragraph(paragraphs[j]));
                    }
                }
            }
        }

        if (result.isEmpty())
            throw new InvalidParsingException("There is no paragraphs or code blocks");
        ArrayList<TextUnit> splited;

        try {
            splited = nextSplitter.split(result);
        }
        catch (Exception e) {
            throw e;
        }

        return splited;
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

    /**
     * override toString for paragraph
     */
    @Override
    public String toString() {
        return "TextParser of paragraphs and code blocks";
    }
}

