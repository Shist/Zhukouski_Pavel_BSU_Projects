// Вариант 2.
// Программа читает текст из стандартного входного потока, находит слова,
// начинающиеся с заглавной буквы и выводит в стандартный выходной поток
// с новой строки
import java.util.*;
public class Main
{
    public static void main(String[] args)
    {
        Scanner in = new Scanner(System.in);
        ArrayList<String> Words = new ArrayList<String>();
        while(in.hasNextLine()){
            String buffer = in.nextLine();
            if(buffer.equals("exit"))
                break;
            StringTokenizer str = new StringTokenizer(buffer," .,!?\n\r", false);
            while(str.hasMoreTokens()) {
                String word = str.nextToken();
                if (Character.isUpperCase(word.charAt(0)))
                    Words.add(word);
            }
        }
        for(String s : Words)
            System.out.println(s);
    }
}
