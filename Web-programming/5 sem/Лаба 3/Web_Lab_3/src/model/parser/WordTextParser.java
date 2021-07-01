package model.parser;

import model.exception.InvalidParsingException;
import model.text_unit.text.TextUnit;
import model.text_unit.text.part.PunctuationMark;
import model.text_unit.text.part.PunctuationMarkTypeEnum;
import model.text_unit.text.part.Sentence;
import model.text_unit.text.part.Word;

import java.util.ArrayList;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 *
 * @author Zhukouski Pavel
 *
 */
public class WordTextParser {

    /**
     * split text into words
     * @param textUnits some textUnits
     * @return parsed text units
     */
    public ArrayList<TextUnit> split(ArrayList<TextUnit> textUnits) throws InvalidParsingException {
        ArrayList<TextUnit> result = new ArrayList<>();
        for (TextUnit textUnit: textUnits) {
            if (textUnit.getClass() == Sentence.class){
                Matcher matcher = Pattern.compile("(" + Word.PATTERN + "|" +
                        PunctuationMark.PATTERN + ")").matcher(textUnit.getValue());
                Sentence sentence = new Sentence(textUnit.getValue());
                while (matcher.find()) {
                    if (Pattern.compile(PunctuationMark.PATTERN).matcher(matcher.group()).matches()) {
                        for (PunctuationMarkTypeEnum type:
                                PunctuationMarkTypeEnum.values()) {
                            if (type.toString().equals(matcher.group())) {
                                PunctuationMark punctuationMark = new PunctuationMark(type);
                                sentence.addPunctuationMark(punctuationMark);
                                break;
                            }
                        }

                    } else {
                        Word word = new Word(matcher.group());
                        sentence.addWord(word);
                    }
                }
                result.add(sentence);
            } else {
                result.add(textUnit);
            }
        }
        if (result.isEmpty())
            throw new InvalidParsingException("There is no words and punctuation marks");

        return result;
    }

    /**
     * override toString for word
     */
    @Override
    public String toString() {
        return "Splitting into words";
    }
}
