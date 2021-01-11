// Вариант 6.
// Программа читает из входного потока текст, находит в нём слова, состоящие только из цифр, и выводит их через выходной поток по одному слову в строке.
import java.util.*;

public class Main
{

    public static boolean check(String userNameString)
    {
        for (int i = 0; i < userNameString.length(); i++)
            if (Character.isDigit(userNameString.charAt(i)) == false)
                return false;
        return true;
    }


    public static void main (String args[])
    {

        System.out.println("Введите данные. Для окончания ввода жми Ctrl + D");
        Scanner in = new Scanner(System.in);
        ArrayList<String> List = new ArrayList<String>();


        while (in.hasNextLine())
        {

            String str = in.nextLine();
            StringTokenizer strtok = new StringTokenizer(str);

            while (strtok.hasMoreTokens())
            {
                String word = strtok.nextToken();
                if (check(word) == true) List.add(word);
            }
        }

        if (List.isEmpty() == true) System.out.println("Нет слов, состоящих из цифр!");
        else
            {
            for (String i: List)
                System.out.println(i);
        }


        in.close();
        System.exit(0);

    }

}