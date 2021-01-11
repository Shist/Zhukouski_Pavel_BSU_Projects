// Вариант 13.
// заменить в строке 8 пробелов стоящих подряд на символ табуляции
import java.util.ArrayList;
import java.util.Scanner;

/* Вариант 13
 * заменить в строке 8 пробелов стоящих подряд на символ табуляции */

public class Main
{
    static ArrayList<String> list = new ArrayList<String>();

    public static void main(String[] args)
    {
        String text;
        Scanner sc = new Scanner(System.in);
        StringBuilder sb = new StringBuilder();
        System.out.println("Input your text");
        while(sc.hasNext())
        {
            String buffer = sc.nextLine();
            if(buffer.equals("exit"))
                break;
            sb.append(buffer).append("\n");
        }
        text = sb.toString();
        sc.close();
        System.out.println(text.replaceAll(" {8}","\t")); //"^ {8}[^\s]$"
    }

}
