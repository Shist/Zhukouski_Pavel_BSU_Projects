package controller;

import model.Text;
import model.exception.InvalidParsingException;
import model.parser.TextParser;
import model.text_unit.text.part.Word;


import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

import static java.util.stream.Collectors.toMap;

/**
 *
 * @author Zhukouski Pavel
 *
 */


public class Controller {


    /**
     * locale
     */
    private static Locale locale;
    /**
     * messages for locale
     */
    public static ResourceBundle messages;

    /**
     *
     * @param text
     * @param symbol
     * @return sort words with symbol
     */
    public ArrayList<Word> sortWordsWithSymbol(Text text, String symbol)
    {

        ArrayList<Word> wordList = text.getAllTextWords();
        Collections.sort(wordList);
        for(int i=0;i<wordList.size()-1;i++)
            for(int j=0;j<wordList.size()-i-1;j++)
            {
                if(wordList.get(j).countOfSymbol(symbol)>wordList.get(j+1).countOfSymbol(symbol))
                {
                    Word tmp = wordList.get(j);
                    wordList.set(j, wordList.get(j+1));
                    wordList.set(j+1, tmp);

                }
            }

        return wordList;
    }
    /**
     * for find word usages in the text
     * @param text
     * @return myWordsCount
     */
    public Map<String, Integer> findUnicalWord(ArrayList<Word> text)
    {
        String[] words=new String[text.size()];
        for(int i=0; i<text.size(); i++){
            words[i]=text.get(i).toString();
        }
        HashMap<String, Integer> myWordsCount = new HashMap<>();
        for (String s : words){
            if (myWordsCount.containsKey(s)) myWordsCount.replace(s, myWordsCount.get(s) + 1);
            else myWordsCount.put(s, 1);
        }

        Map<String, Integer> newWordsCount = myWordsCount
                .entrySet()
                .stream()
                .sorted(Collections.reverseOrder(Map.Entry.comparingByValue()))
                .collect(
                        toMap(Map.Entry::getKey, Map.Entry::getValue, (e1, e2) -> e2,
                                LinkedHashMap::new));

        return newWordsCount;

    }

    /**
     * This method begin work with text
     * @throws FileNotFoundException
     * @throws InvalidParsingException
     */
    public void begin() throws FileNotFoundException, InvalidParsingException
    {
        String language = "ru";
        locale = new Locale(language);
        messages = ResourceBundle.getBundle("property/locale", locale);



        String s = "";
        Scanner in = new Scanner(new File("input.txt"));
        while(in.hasNext())
            s += in.nextLine() + "\r\n";
        in.close();
        TextParser textParser = new TextParser();
        Text parsedText = textParser.splitText(s);
        System.out.println("Текст:" + parsedText);
        ArrayList<Word> t=parsedText.getAllTextWords();


        String a = "а";
        ArrayList<Word> wordList = sortWordsWithSymbol(parsedText, a);

        System.out.println("\nСортировка слов по возростанию по количеству букв \"" + a + "\"");

        for (int i=0; i<wordList.size();i++)
            System.out.println(wordList.get(i));


        System.out.println("\nСписок заданных слов в тексте и количество их вхождений по убыванию:");
        Map<String, Integer> wordsList = findUnicalWord(t);

        for(Map.Entry<String, Integer> entry : wordsList.entrySet())
            System.out.println("\"" + entry.getKey() + "\" - " + entry.getValue() + " вхождений");

    }

}

