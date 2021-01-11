// Вариант 8.
// Слова разделены пробелами. Все слова в строке которые состоят только из букв отсортировать и сохранять количество пробелов
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main
{

    public static void main(String[] args)
    {

        Scanner in=new Scanner(System.in);

        ArrayList <String> result= new ArrayList <String>();

        while (in.hasNext()) {

            String stroka = in.nextLine();

            if(stroka.equals("exit"))
                break;

            ArrayList <String> str= new ArrayList <String>();
            String[] arr = stroka.split(" ");

            for (int i = 0; i < arr.length; i++)
                if (isWord(arr[i])) {
                    str.add(arr[i]);
                    arr[i] = null;
                }

            Collections.sort(str,new Comparator <String> () {
                public int compare(String o1, String o2) { return o1.compareTo(o2); }  });

            int j = 0;
            String s = "";

            for (String i : arr) {
                if (i == null)
                    s += str.get(j++);
                else
                    s += i;
                s += " ";
            }
            result.add(s);
        }

        for(String i : result)
            System.out.println(i);
    }


    private static boolean isWord(String word) {
        Pattern p = Pattern.compile("^[A-z,A-y]+");
        Matcher m = p.matcher(word);
        return m.matches();
    }
}
