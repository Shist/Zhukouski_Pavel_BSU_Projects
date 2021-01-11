package model.text_unit;

import model.text_unit.code.CodeBlock;
import model.text_unit.text.TextUnit;
import model.text_unit.text.TextUnitTypeEnum;
import model.text_unit.text.part.Paragraph;
import model.text_unit.text.part.Sentence;
import model.text_unit.text.part.Word;

import java.util.ArrayList;

/**
 *
 * @author Shilkin EGor
 *
 */
public class Text extends TextUnit {

    public static final String TEXT_NAME = "TEXT";

    /**
     * text units
     */
    private ArrayList<TextUnit> text;

    public void setText(ArrayList<TextUnit> text) {
        this.text = text;
    }

    public Text() {
        super("",TextUnitTypeEnum.TEXT);
        text = new ArrayList<>();
    }

    /**
     * add sentence to array
     * @param sentence sentence
     */
    public void addSentence(Sentence sentence) {
        text.add(sentence);
    }

    /**
     * add paragraph to array
     * @param paragraph paragraph
     */
    public void addParagraph(Paragraph paragraph) {
        text.add(paragraph);
    }

    /**
     * add codeBlock to array
     * @param codeBlock code block
     */
    public void addCode(CodeBlock codeBlock) {
        text.add(codeBlock);
    }

    /**
     * get all sentences
     * @return  sentences in text
     */
    public ArrayList<Sentence> getSentences() {
        ArrayList<Sentence> sentences = new ArrayList<>();
        for (TextUnit textUnit : text) {
            if (textUnit.getClass() == Sentence.class)
                sentences.add((Sentence)textUnit);
        }
        return sentences;
    }

    /**
     * get all text words
     * @return words in text
     */
    public ArrayList<Word> getAllTextWords() {
        ArrayList<Sentence> sentences = getSentences();
        ArrayList<Word> words = new ArrayList<>();
        for (Sentence sentence : sentences) {
            words.addAll(sentence.getWords());
        }
        return words;
    }

    /**
     * get all paragraphs
     * @return  paragraphs in text
     */
    public ArrayList<Paragraph> getParagraphs() {
        ArrayList<Paragraph> paragraphs = new ArrayList<>();
        for (TextUnit textUnit : text) {
            if (textUnit.getClass() == Paragraph.class)
                paragraphs.add((Paragraph)textUnit);
        }
        return paragraphs;
    }

    /**
     * get all code blocks
     * @return code blocks in text
     */
    public ArrayList<CodeBlock> getCodeBlocks() {
        ArrayList<CodeBlock> codeBlocks = new ArrayList<>();
        for (TextUnit textUnit : text) {
            if (textUnit.getClass() == CodeBlock.class)
                codeBlocks.add((CodeBlock)textUnit);
        }
        return codeBlocks;
    }

    /**
     * Method toString for object text
     */
    @Override
    public String toString() {
        StringBuilder textToString = new StringBuilder();
        for (TextUnit textUnit : text) {
            textToString.append(textUnit.toString());
            if (textUnit.getClass() == Sentence.class)
                textToString.append(" ");
        }
        return textToString.toString();
    }


}
