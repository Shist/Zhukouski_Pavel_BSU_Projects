package controller;

import model.text_unit.Text;
import model.exception.InvalidParsingException;
import model.parser.TextParser;
import model.text_unit.text.part.Word;


import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

import static java.util.stream.Collectors.toMap;

/**
 *
 * @author Shilkin Egor
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
     * @return sort words with symbol
     */
    public ArrayList<Word> sortWords(Text text)
    {

        ArrayList<Word> wordList = text.getAllTextWords();
        Collections.sort(wordList);
        for(int i=0;i<wordList.size()-1;i++)
            for(int j=0;j<wordList.size()-i-1;j++)
            {
                Word tmp = wordList.get(j);
                wordList.set(j, wordList.get(j+1));
                wordList.set(j+1, tmp);
            }

        Collections.reverse(wordList);

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
        System.out.println("\nПечать текста в его оригинальном виде:\n" + parsedText);
        ArrayList<Word> t=parsedText.getAllTextWords();


        ArrayList<Word> wordList = sortWords(parsedText);

        System.out.println("\nСортировка слов текста в алфавитном порядке по первой букве:");

        System.out.print("\t");
        for (int i=0; i<wordList.size();i++)
        {
            if (i > 0 && wordList.get(i).toString().charAt(0) != wordList.get(i - 1).toString().charAt(0))
            {
                System.out.print("\n\t");
            }
            System.out.print(wordList.get(i) + " ");
        }

        String textStr = parsedText.toString();
        String max_str = "";
        String curr_str = "";
        System.out.println("\n\nПервая подстрока максимальной длины в тексте, не содержащая букв:");
        for (int i=0; i < textStr.length(); i++)
        {
            if (Character.isLetter(textStr.charAt(i)))
            {
                curr_str = "";
            }
            else
            {
                curr_str += textStr.charAt(i);
                if (curr_str.length() > max_str.length())
                {
                    max_str = curr_str;
                }
            }
        }
        System.out.println(max_str);

        String upperText = "";
        upperText = upperText + textStr.substring(0, 1).toUpperCase();
        for (int i = 1; i < textStr.length(); i++) {
            // смотрим, был ли слева пробел:
            if (" ".equals(textStr.substring(i-1, i)))
                upperText = upperText + textStr.substring(i, i+1).toUpperCase();
            else
                upperText = upperText + textStr.substring(i, i+1);
        }

        System.out.println("\nИсходный текст, но теперь каждое его слово с заглавной буквы:");
        System.out.println(upperText);

    }

}

